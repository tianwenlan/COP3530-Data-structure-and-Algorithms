#ifndef _SDAL_H_
#define _SDAL_H_

// SDAL.H
// 
// Simple Dynamic Array-based List (SDAL)
//
// Author: Wenlan Tian
// Project 1 for COP 3530
// Date: 09/18/2014
// Version 1

#include <iostream>
#include <stdexcept>

namespace cop3530 {

	template <typename T>
	class SDAL {
	private:
		int mySize;
		int myCapacity;
		T *arr;

		void grow(){
			T *tempArr = new T[myCapacity + myCapacity/2];
			for(int i =0; i<mySize; i++){
				tempArr[i]=arr[i];
			}
			arr = tempArr;
			myCapacity = myCapacity + myCapacity/2;
	//		delete []tempArr;
		}

		void shrink(){
			T *tempArr = new T[myCapacity/2];
			for(int i =0; i<mySize; i++){
				tempArr[i]=arr[i];
			}
			arr = tempArr;
			myCapacity = myCapacity/2;	
	//		delete []tempArr;
		}

	public:

		class SDAL_Iter //: public std::iterator<std::forward_iterator_tag, T>
		{
		public:
		// inheriting from std::iterator<std::forward_iterator_tag, T>
		// automagically sets up these typedefs...
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
      
		// but not these typedefs...
		typedef SDAL_Iter self_type;
		typedef SDAL_Iter& self_reference;

		private:
		T* here;
      
		public:
		explicit SDAL_Iter( T* start = NULL ) : here( start ) {
		}
		SDAL_Iter( const SDAL_Iter& src ) : here( src.here ) {
		}
       
		reference operator*() const {
			return *here;
		}
		pointer operator->() const {
			return &(operator*());
		}
      
		self_reference operator=( const SDAL_Iter& src ) {
			here = src.here;
			return *this;
		}

		self_reference operator++() {
			++here;
			return *this;
		} // preincrement

		self_type operator++(int) {
			self_type result (*this);
			++here;
			return result;
		} // postincrement

		bool operator==(const SDAL_Iter& rhs) const {
			return here == rhs.here;
		}
		bool operator!=(const SDAL_Iter& rhs) const {
			return here != rhs.here;
		}
     }; // end SDAL_Iter

    class SDAL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
	{
		public:
		// inheriting from std::iterator<std::forward_iterator_tag, T>
		// automagically sets up these typedefs...
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef std::forward_iterator_tag iterator_category;
      
		// but not these typedefs...
		typedef SDAL_Const_Iter self_type;
		typedef SDAL_Const_Iter& self_reference;
      
     private:
		const T* here;
      
     public:
		explicit SDAL_Const_Iter( T* start = NULL ) : here( start ) {
		}

		SDAL_Const_Iter( const SDAL_Const_Iter& src ) : here( src.here ) {
		}
       
		reference operator*() const {
			return *here;
		}
		pointer operator->() const {
			return &(operator*());
		}
      
		self_reference operator=( const SDAL_Const_Iter& src ) {
			here = src.here;
			return *this;			
		}

		self_reference operator++() {
			++here;
			return *this;
		}

		self_type operator++(int) {
			self_type result (*this);
			++here;
			return result;
		} // postincrement

		bool operator==(const SDAL_Const_Iter& rhs) const {
			return here == rhs.here;
		}

		bool operator!=(const SDAL_Const_Iter& rhs) const {
			return here != rhs.here;
		}
     }; // end SDAL_Const_Iter

	//--------------------------------------------------
	// types
    //--------------------------------------------------
	typedef std::size_t size_t;
	typedef T value_type;
	typedef SDAL_Iter iterator;
	typedef SDAL_Const_Iter const_iterator;	

	iterator begin() {
		return SDAL_Iter( arr ); 
	}

    iterator end() {
		return SDAL_Iter( arr+mySize ); 
	}
     
    const_iterator begin() const { 
		return SDAL_Const_Iter( arr ); 
	}
    const_iterator end() const {
		return SDAL_Const_Iter( arr+mySize ); 
	} 

    
    //--------------------------------------------------
    // Constructors/destructor/assignment operator
    //--------------------------------------------------

	SDAL() {
		mySize = 0;
		myCapacity = 50;

		arr = new T[myCapacity];
	//	for (int i =0; i < myCapacity; ++i){
	//		arr[i] = NULL;
	//	}
	}
    
    //--------------------------------------------------
	SDAL(int capacity) {
		mySize = 0;
		myCapacity = capacity;
		arr = new T[myCapacity];
		for (int i =0; i< myCapacity; ++i){
			arr[i] = "";
		}
	}
    
    //--------------------------------------------------
    ~SDAL() {
      // safely dispose of this SDAL's contents
	  clear();
    }
    
    //--------------------------------------------------
    SDAL& operator=( const SDAL& src ) {
		if (src.mySize == 0){
			throw std::out_of_range("Try to copy an empty list!");
		}

		if ( &src == this ) // check for self-assignment
			return *this;     // do nothing

		// safely dispose of this SSLL's contents
		if(src.mySize != 0){
			clear();
		}

		// populate this SSLL with copies of the other SSLL's contents
		for(int i =0; i<src.mySize; i++){
			push_back(src.arr[i]);
		}

		return *this;
    }
    
    //--------------------------------------------------
    // member functions
    //--------------------------------------------------

    T replace( const T& element, int position ) {
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (position < 0 || position >= size()){
			throw std::domain_error("Invalid position!");
		}

		T result = arr[position];
		arr[position] = element;
		return result;
	}

    //--------------------------------------------------
    void insert( const T& element, int position ) {		
		if (position < 0 || position > size()){
			throw std::domain_error("Invalid position!");
		}
		if (mySize >= myCapacity){
			grow();
		}

		if (position == size()){
			push_back(element);
		}else{
		
			for(int i = mySize; i > position; --i){
				arr[i] = arr[i-1];
			}
			arr[position] = element;
			mySize ++;
		}
	}
    
    //--------------------------------------------------
    void push_front( const T& element ) {

		if(mySize == myCapacity){
			grow();
		}

		if(!is_empty()){
			for(int i = mySize; i > 0; i--){
				arr[i] = arr[i-1];
			}
		}

		arr[0] = element;
		mySize ++;
	}
    
    //--------------------------------------------------
    void push_back( const T& element ) {

		if(mySize == myCapacity){
			grow();
		}

		arr[mySize] = element;
		mySize ++;
	}
    
    //--------------------------------------------------
    T pop_front() {
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}

		T result = arr[0];
		for(int i = 0; i < mySize-1; ++i){
			arr[i] = arr[i+1];
		}
		mySize--;
		return result;
	}

    //--------------------------------------------------
    T pop_back() {
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		mySize--;
		return arr[mySize];
	}

    //--------------------------------------------------
    T remove( int position ) {

		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (position < 0 || position >= size()){
			throw std::domain_error("Invalid position!");
		}	
			
		if (position == mySize-1){
			mySize--;
			return arr[position];
		}else{
			for(int i = position; i < mySize - 1; ++i){
				arr[i] = arr[i+1];
			}
			mySize--;

			if(myCapacity >=100 && mySize < myCapacity/2){
				shrink();
			}
			return arr[position];
		}
	}

    //--------------------------------------------------
    T item_at( int position ) const {
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (position < 0 || position >= size()){
			throw std::domain_error("Invalid position!");
		}

		return arr[position];
	}

    //--------------------------------------------------
    bool is_empty() const {
		return (mySize == 0) ? true : false;
	}

    //--------------------------------------------------
    size_t size() const {
		return mySize;
	}

    //--------------------------------------------------
    void clear() {
//		delete []arr;
		mySize = 0;
		myCapacity = 50;
	}

    //--------------------------------------------------
    bool contains( const T& element, bool equals( const T& a, const T& b  ) ) const {
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		int match = 0;
		for (int i =0; i< mySize; ++i){
			if (arr[i] == element){
				match++;
			}
		}

		return (match == 1) ? true : false;
	}

    //--------------------------------------------------
    std::ostream& print( std::ostream& out ) const {
		if(is_empty()){
			std::cout << "<empty list>" << std::endl;
		}else{
			std::cout << "[" << arr[0] << std::flush;
			for (int i = 1; i < mySize; ++i){
				std::cout << "," << arr[i] << std::flush;
			}
			std::cout << "]" << std::endl;
		}
	}

	T& operator[](int i){
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (i < 0 || i >= size()){
			throw std::domain_error("Invalid index!");
		}

		return arr[i];
	}

	T const& operator[](int i) const{
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (i < 0 || i >= size()){
			throw std::domain_error("Invalid index!");
		}
			return arr[i];
	}


  }; //end class SDAL
} // end namespace cop3530

#endif // _SDAL_H_
