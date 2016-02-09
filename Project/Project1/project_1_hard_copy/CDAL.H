#ifndef _CDAL_H_
#define _CDAL_H_

// CDAL.H
// 
// Chained Dynamic Array-based List (CDAL)
//
// Author: Wenlan Tian
// Project 1 for COP 3530
// Date: 09/17/2014
// Version 1

#include <iostream>
#include <stdexcept>

namespace cop3530 {

	template <typename T>
	class CDAL {
	private:
		struct Node {
			Node* next;
			T* arr;

			Node():next(NULL){
			arr = new T[50];
		}
    }; // end struct Node
  
	int mySize;
	Node* head;
	T* tail;

	void shrink(){
		Node* current = head;
		for (int i = 0; i < (mySize-mySize%50)/50 ;++i){
			current = current -> next;
		}

		Node* temp = current->next;
		current -> next = NULL;
		
		while(temp->next!=NULL){
			pop_back();
		}
	}


	public:

	    class CDAL_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
		typedef CDAL_Iter self_type;
		typedef CDAL_Iter& self_reference;

      
		private:
		T* here;
      
		public:
		explicit CDAL_Iter( T* start = NULL ) : here( start ) {
		}
		CDAL_Iter( const CDAL_Iter& src ) : here( src.here ) {
		}
       
		reference operator*() const {
			return *here;
		}
		pointer operator->() const {
			return &(operator*());
		}
      
		self_reference operator=( const CDAL_Iter& src ) {
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

		bool operator==(const CDAL_Iter& rhs) const {
			return here == rhs.here;
		}
		bool operator!=(const CDAL_Iter& rhs) const {
			return here != rhs.here;
		}
     }; // end CDAL_Iter

    class CDAL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
		typedef CDAL_Const_Iter self_type;
		typedef CDAL_Const_Iter& self_reference;
      
     private:
		const T* here;
      
     public:
		explicit CDAL_Const_Iter( T* start = NULL ) : here( start ) {
		}
		CDAL_Const_Iter( const CDAL_Const_Iter& src ) : here( src.here ) {
		}
       
		reference operator*() const {
			return *here;
		}
		pointer operator->() const {
			return &(operator*());
		}
      
		self_reference operator=( const CDAL_Const_Iter& src ) {
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

		bool operator==(const CDAL_Const_Iter& rhs) const {
			return here == rhs.here;
		}

		bool operator!=(const CDAL_Const_Iter& rhs) const {
			return here != rhs.here;
		}
     }; // end CDAL_Const_Iter

	//--------------------------------------------------
	// types
    //--------------------------------------------------
	typedef std::size_t size_t;
	typedef T value_type;
	typedef CDAL_Iter iterator;
	typedef CDAL_Const_Iter const_iterator;	

	iterator begin() {
		return CDAL_Iter( head->arr ); 
	}

    iterator end() {
		return CDAL_Iter( tail ); 
	}
     
    const_iterator begin() const { 
		return CDAL_Const_Iter( head->arr ); 
	}
    const_iterator end() const {
		return CDAL_Const_Iter(tail ); 
	} 



    //--------------------------------------------------
    // Constructors/destructor/assignment operator
    //--------------------------------------------------

    CDAL() {
		mySize = 0;
		head = new Node();
		tail = &head->arr[0];
	}
    
    //--------------------------------------------------
    CDAL( const CDAL& src ) {
	}
    
    //--------------------------------------------------
    ~CDAL() {
      // safely dispose of this CDAL's contents
    }
    
    //--------------------------------------------------
    CDAL& operator=( const CDAL& src ) {
		if (src.size() == 0){
			throw std::out_of_range("Try to copy an empty list!");
		}

		if ( &src == this ) // check for self-assignment
			return *this;     // do nothing

		// safely dispose of this SSLL's contents
		if(size()!=0){
			clear();
		}

		// populate this SSLL with copies of the other SSLL's contents
		Node* current = src.head;
		
		while(current->next!=NULL){
			for(int i =0; i<50; i++){
				push_back(current->arr[i]);
			}
			current = current -> next;
		}

		if(src.size()%50==0){
			for(int i =0; i<50; i++){
				push_back(current->arr[i]);
			}
		}else{
			for(int i =0; i<src.size()%50; i++){
				push_back(current->arr[i]);
			}
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

		T result;
		
		if(position < 50){
			Node* current = head;
			result = current->arr[position];
			current->arr[position] = element;
			return result;
		}else{
			Node* current = head;

			for (int i = 0; i < (position -(position%50))/50; ++i){
				 current=  current-> next;
			}

			result = current->arr[position%50];

			current->arr[position%50] = element;
			return result;
		}
	}

    //--------------------------------------------------
    void insert( const T& element, int position ) {
		
		if (position < 0 || position > size()){
			throw std::domain_error("Invalid position!");
		}
		
		if (position == 0){
			push_front(element);
		}else if(position == size()){
			push_back(element);
		}else if (size()<50){
			Node* current = head;
			for(int i = size(); i > position; --i){
				
				current->arr[i] = current->arr[i-1];
			}
			current->arr[position]=element;
			mySize++;
			tail = &current->arr[size()];
		}else if (size()==50){
			Node* current = head;
			Node* tempNode = new Node();

			tempNode->arr[0]=current->arr[49];
			tail = &tempNode->arr[0];

			for (int i = 49; i > position; --i){
				current->arr[i] = current->arr[i-1];
			}
			current->arr[position] = element;
			mySize++;
		}else{
			Node* current = head;

			int position_node= (position -position%50)/50+1;
			int total_node = (size()-size()%50)/50;

			//move to the node with position to be inserted
			for (int i =1; i< position_node; ++i){
				current = current -> next;
			}

			T temp, temp1;

			if (position_node < total_node){

				for(int i = position_node; i< total_node; i++){

					if (i== position_node){
						temp = current->arr[49];
                 
						for(int j = 49; j > position%50; --j){
							current->arr[j] = current->arr[j-1];
						}
						current->arr[position%50] = element;
					}else{
						temp1 = current->arr[49];

						for (int j =49; j> 0; --j){
							current->arr[j] = current->arr[j-1];
						}
						current->arr[0] = temp;
						temp = temp1;
					}

					current = current -> next;
				}
			

				if (size()%50==0){
					Node* tempNode = new Node();
					tempNode->arr[0] = current->arr[49];
					tail = &tempNode->arr[0];

					for (int i =49; i> 0; --i){
						current->arr[i] = current->arr[i-1];
					}
					current->arr[0]=temp;

					current -> next = tempNode;

				}else{
				
					for (int i = size()%50; i> 0; --i){
						current->arr[i] = current->arr[i-1];
					}
					current->arr[0]=temp;
					tail = &current->arr[size()%50];

				}

			}else{
				if(size()%50==0){
					for (int i = 49; i> position%50; --i){
						current->arr[i] = current->arr[i-1];
					}

				}else{
					for (int i = size()%50; i> position%50; --i){
						current->arr[i] = current->arr[i-1];
					}
				}
					current->arr[position%50]=element;
					tail = &current->arr[size()%50];

			}

			mySize++;

		}
	}
    
    //--------------------------------------------------
    void push_front( const T& element ) {

		Node* current = head;

		if(size()<50){
			for(int i = size(); i > 0; --i){
				current->arr[i] = current->arr[i-1];
			}

			current->arr[0]=element;
		}else{
			T temp;

			while(current -> next != NULL){

				temp = current->arr[49];
				for (int i =49; i> 0; --i){
					current->arr[i] = current->arr[i-1];
				}

				if(current==head){
					current->arr[0]=element;
				}else{
					current->arr[0] = temp;
				}

				current = current -> next;
			}

			if (size()%50==0){

				temp = current->arr[49];
				for (int i =49; i> 0; --i){
					current->arr[i] = current->arr[i-1];
				}

				Node* tempNode = new Node();
				tempNode->arr[0]= temp; 

				current -> next = tempNode;

			}else{
				
				for (int i = size()%50; i> 0; --i){
					current->arr[i] = current->arr[i-1];
				}
				current->arr[0]=temp;
			}
		}

		mySize++;
	}
    
    //--------------------------------------------------
    void push_back( const T& element ) {
				
		Node* current = head;
		while (current -> next != NULL){
			current = current -> next;
		}

		if(size()<50){
			current->arr[size()]=element;
		}else 
			if(size()%50==0){
			Node* temp = new Node();
			temp->arr[0]=element;
			current -> next = temp;
		}else{
			current->arr[size()%50] = element;
		}
		mySize++;
	}
    
    //--------------------------------------------------
    T pop_front() {
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}

		Node* current = head;
		T result = current->arr[0];

		if (size() <= 50){

			for (int i = 0; i< 49; ++i){
				current->arr[i] = current->arr[i+1];
			}
			mySize--;
		}else{

		//	T empty;

			while(current -> next -> next != NULL){
   
				for (int i = 0; i< 49; ++i){
					current->arr[i] = current->arr[i+1];
				}
				current->arr[49] = current->next->arr[0];

				current = current -> next;
			}

			for (int i = 0; i< 49; ++i){
				current->arr[i] = current->arr[i+1];
			}
				current->arr[49] = current->next->arr[0];


			if (size()%50==1){

		//		current->next->arr[0] = NULL;
				Node* temp = current -> next;
				current->next=NULL;
				delete temp;
			}else if (size()%50==0){
				for (int i = 0; i< 49; ++i){
					current->next->arr[i] = current->next->arr[i+1];
				}
				current->next->arr[49] = T();
			}else{
				for (int i = 0; i< size()%50 -1; ++i){
					current->next->arr[i] = current->next->arr[i+1];
				}
				current->next->arr[size()%50-1] = T();
			}

			mySize--;

		}
		return result;
		
	}

    //--------------------------------------------------
    T pop_back() {
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		T result, empty;
		Node* current = head;

		if(size()<=50){
			result = current->arr[size()-1];
			current->arr[size()-1]=empty;
			mySize --;
			return result;
		}

		while(current -> next -> next != NULL){
			current = current -> next;
		}

		if(size()%50==1){
			Node* temp = current-> next;
			result = temp->arr[0];
			current -> next = NULL;
			delete temp;
		}else if(size()%50==0){
			result = current -> next->arr[49];
		}else{
			result = current->next->arr[size()%50-1];
			current->next->arr[size()%50-1]=empty;
		}

		mySize--;
		return result;	
	}

    //--------------------------------------------------
    T remove( int position ) {

		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (position < 0 || position >= size()){
			throw std::domain_error("Invalid position!");
		}
			
		if (position == 0){
			return pop_front();
		}else if(position == size()-1){
			return pop_back();
		}else if (size() <= 50){
			Node* current = head;
			for (int i = position; i< 49; ++i){
				current->arr[i] = current->arr[i+1];
			}
			mySize--;
			return current->arr[position];
		}else{

			int position_node= (position -position%50)/50+1;
			int total_node = (size()-size()%50)/50;

			Node* current = head;

			for (int i =1; i< position_node; ++i){
				current = current -> next;
			}

			T result = current->arr[position%50];
			T empty;

			if (position_node < total_node){

				for(int i = position_node; i< total_node; i++){

					if (i== position_node){
                 
						for (int i = position%50; i< 49; ++i){
							current->arr[i] = current->arr[i+1];
						}
					}else{

						for (int i = 0; i< 49; ++i){
							current->arr[i] = current->arr[i+1];
						}
					}
					current->arr[49] = current->next->arr[0];
					current = current -> next;
				}

				if (size()%50==1){
					current->arr[0] = empty;
				}else if(size()%50==0){
					for (int i = 0; i< 49; ++i){
						current->arr[i] = current->arr[i+1];
					}
					current->arr[49] = empty;
				}else{
					for (int i = 0; i< size()%50 -1; ++i){
						current->arr[i] = current->arr[i+1];
					}
					current->arr[size()%50-1] = empty;
				}

			}else{
				if(size()%50==0){
					for (int i = 49; i> position%50; --i){
						current->arr[i] = current->arr[i-1];
					}

				}else{
					for (int i = size()%50; i> position%50; --i){
						current->arr[i] = current->arr[i-1];
					}
				}
					tail = &current->arr[size()%50];
			}

			mySize--;
			return result;
		}
	}

    //--------------------------------------------------
    T item_at( int position ) const {
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (position < 0 || position >= size()){
			throw std::domain_error("Invalid index!");
		}		
		
		if(position < 50){ 
			Node* current = head;
			return (current->arr[position]);
		}else{
			Node* current = head;

			for (int i = 0; i < (position -(position%50))/50; ++i){
				 current =  current -> next;
			}
			return ( current->arr[position%50]);
		}
	}

    //--------------------------------------------------
    bool is_empty() const {
		return (mySize == 0) ? true:false;
	}

    //--------------------------------------------------
    size_t size() const {
		return mySize;
	}

    //--------------------------------------------------
    void clear() {
		while(size()!=0){
			pop_back();
		}

		head = new Node();
		tail = &head->arr[0];
	}

    //--------------------------------------------------
    bool contains( const T& element, bool equals( const T& a, const T& b  ) ) const {

		if (size()==0){
			throw std::out_of_range("Empty list!");
		}

		int match = 0;
	
		Node* current = head;
		while(current->next!=NULL){
			for(int i =0; i < 50; ++i){
				if(current->arr[i] == element){
					match ++;
				}
			}
			current = current -> next;
		}

		for(int i =0; i < size()%50; ++i){
			if(current->arr[i] == element){
				match ++;
			}
		}


		return (match == 1)? true : false;
	}

    //--------------------------------------------------
    std::ostream& print( std::ostream& out ) const {
		if(size()==0){
			out << "<empty list>" << std::endl;
		}else{
			Node* current = head;
			out << "[" << current->arr[0] << std::flush;

			while(current!=NULL){

				if(current!=head){
					out << "," << current->arr[0] << std::flush;
				}

				for (int i = 1; i< 50; ++i){
					if(current->arr[i])
					out << "," << current->arr[i] << std::flush;
				}

				current = current -> next;
			}
			out << "]" << std::endl;
		}
		return out;
	}

	T& operator[](int i){

		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (i < 0 || i >= size()){
			throw std::domain_error("Invalid index!");
		}
		
		if(i < 50){
			Node* current = head;
			return (current->arr[i]);
		}else{
			Node* current = head;

			for (int k = 0; k < (i -(i%50))/50; ++k){
				current = current -> next;
			}
			return (current->arr[i%50]);
		}
	}

	T const& operator[](int i) const{
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (i < 0 || i >= size()){
			throw std::domain_error("Invalid index!");
		}	
			
		if(i < 50){
			Node* current = head;
			return (current->arr[i]);
		}else{
			Node* current = head;

			for (int k = 0; k < (i -(i%50))/50; ++k){
				current = current -> next;
			}
			return (current->arr[i%50]);
		}
	}


  }; //end class CDAL
} // end namespace cop3530

#endif // _CDAL_H_
