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

namespace cop3530 {

  template <typename T>
  class CDAL {
  private:
    struct Node {
		Node* next;
		T* arr;

		Node(){
			next = NULL;
			arr = new T[50];
		}

    }; // end struct Node
  
	int mySize = 0;
	Node* head;
	Node* first;


  public:

	    class SSLL_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
		typedef SSLL_Iter self_type;
		typedef SSLL_Iter& self_reference;
      
     private:
		Node* here;
      
     public:
		explicit SSLL_Iter( Node* start = NULL ) : here( start ) {
		}
		SSLL_Iter( const SSLL_Iter& src ) : here( src.here ) {
		}
       
		reference operator*() const {
			return here -> data;;
		}
		pointer operator->() const {
		}
      
		self_reference operator=( const SSLL_Iter& src ) {
		}

		self_reference operator++() {
			here = here ->next;
			return *this;
		} // preincrement

		self_type operator++(int) {
			self_type result (*this);
			here = here ->next;
			return result;
		} // postincrement

		bool operator==(const SSLL_Iter& rhs) const {
			return here == rhs.here;
		}
		bool operator!=(const SSLL_Iter& rhs) const {
			return here != rhs.here;
		}
     }; // end SSLL_Iter

    class SSLL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
		typedef SSLL_Const_Iter self_type;
		typedef SSLL_Const_Iter& self_reference;
      
     private:
		Node* here;
      
     public:
		explicit SSLL_Const_Iter( Node* start = NULL ) : here( start ) {
		}
		SSLL_Const_Iter( const SSLL_Const_Iter& src ) : here( src.here ) {
		}
       
		reference operator*() const {
			return here -> data;
		}
		pointer operator->() const {
		}
      
		self_reference operator=( const SSLL_Const_Iter& src ) {
		}

		self_reference operator++() {
			here = here ->next;
			return *this;
		} // preincrement

		self_type operator++(int) {
			self_type result (*this);
			here = here -> next;
			return result;
		} // postincrement

		bool operator==(const SSLL_Const_Iter& rhs) const {
			return here == rhs.here;
		}

		bool operator!=(const SSLL_Const_Iter& rhs) const {
			return here != rhs.here;
		}
     }; // end SSLL_Const_Iter

	//--------------------------------------------------
	// types
    //--------------------------------------------------
	typedef std::size_t size_t;
	typedef T value_type;
	typedef SSLL_Iter iterator;
	typedef SSLL_Const_Iter const_iterator;	

	iterator begin() {
		return SSLL_Iter( head ); 
	}

    iterator end() {
		return SSLL_Iter(tail ); 
	}
     
    const_iterator begin() const { 
		return SSLL_Const_Iter( head ); 
	}
    const_iterator end() const {
		return SSLL_Const_Iter( tail ); 
	} 



    //--------------------------------------------------
    // Constructors/destructor/assignment operator
    //--------------------------------------------------

    CDAL() {
		mySize = 0;
		first = new Node();
		head = first;
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
      if ( &src == this ) // check for self-assignment
	return *this;     // do nothing
      
      // safely dispose of this CDAL's contents
      // populate this CDAL with copies of the other CDAL's contents
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
		
		if(position < 50){
			first->arr[position] = element;
		}else{
			Node* temp = head;

			for (int i = 0; i < (position -(position%50))/50; ++i){
				temp = temp -> next;
			}

			temp->arr[position%50] = element;
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
		}else if (size()==50){
			Node* current = head;
			Node* tempNode = new Node();
			if(position==50){
				tempNode->arr[0]= element;
				current -> next = tempNode;
			}else{
				tempNode->arr[0]=current->arr[49];
				for (int i = 49; i > position; --i){
					current->arr[i] = current->arr[i-1];
				}
				current->arr[position] = element;
			}
		}else{
			Node* current = head;

			int position_node= (position -position%50)/50;
			int total_node = (size()-size()%50)/50;

			//move to the node with position to be inserted
			for (int i =0; i< position_node; ++i){
				current = current -> next;
			}

			T temp = NULL;

			if (position_node < total_node){

				for(int i = position_node; i< total_node; i++){

					if (i== position_node){
						temp = current->arr[49];
                 
						for(int j = 49; j > position%50; --j){
							current->arr[j] = current->arr[j-1];
						}
						current->arr[position%50] = element;
					}else{
						temp = current->arr[49];

						for (int j =49; j> 0; --j){
							current->arr[j] = current->arr[j-1];
						}
						current->arr[0] = temp;
					}

					current = current -> next;
				}
			

				if (size()%50==0){
					Node* tempNode = new Node();
					tempNode->arr[0]=current->arr[49];

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
				}

			}else{
					for (int i = size()%50; i> position%50; --i){
						current->arr[i] = current->arr[i-1];
					}
					current->arr[position%50]=element;


			}
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
			T temp = NULL;

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
		}else if(size()%50==0){
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

			while(current -> next != NULL){

				for (int i = 0; i< 49; ++i){
					current->arr[i] = current->arr[i+1];
				}
				current->arr[49] = current->next->arr[0];

				current = current -> next;
			}

			if (size()%50==1){
				current->arr[0] = NULL;
			}else{
				for (int i = 0; i< size()%50 -1; ++i){
					current->arr[i] = current->arr[i+1];
				}
				current->arr[size()%50-1] = NULL;
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
		
		T result;

		Node* temp = head;
		while(temp -> next != NULL){
			temp = temp -> next;
		}

		if(size()<=50){
			result = first->arr[size()-1];
			first->arr[size()-1]=NULL;
		}else if(size()%50==1){
			std::cout << result ;
			result = temp->arr[0];
			temp->arr[0] = NULL;
			delete []temp->arr;
			temp = NULL;
		}else{
			result = temp->arr[size()%50-1];
			temp->arr[size()%50-1]=NULL;
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
			pop_front();
		}else if(position == size()-1){
			pop_back();
		}else if (size() <= 50){
			Node* current = head;
			for (int i = position; i< 49; ++i){
				current->arr[i] = current->arr[i+1];
			}
			mySize--;
		}else{
			Node* current = head;

			for (int i =0; i< (position-position%50)/50; ++i){
				current = current -> next;
			}

			while(current -> next != NULL){

				for (int i = position%50; i< 49; ++i){
					current->arr[i] = current->arr[i+1];
				}
				current->arr[49] = current->next->arr[0];

				current = current -> next;
			}

			if (size()%50==1){
				current->arr[0] = NULL;
			}else{
				for (int i = 0; i< size()%50 -1; ++i){
					current->arr[i] = current->arr[i+1];
				}
				current->arr[size()%50-1] = NULL;
			}

			mySize--;
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
			std::cout << "Item at position " << position << " is " << first->arr[position] << std::endl;
			return (first->arr[position]);
		}else{
			Node* temp = head;

			for (int i = 0; i < (position -(position%50))/50; ++i){
				temp = temp -> next;
			}
			std::cout << "Item at position " << position << " is " << temp->arr[position%50] << std::endl;
			return (temp->arr[position%50]);
		}
	}

    //--------------------------------------------------
    bool is_empty() const {
		return (!first->next && first->arr[0]== NULL) ? true:false;
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

		first = new Node();
		head = first;
	}

    //--------------------------------------------------
    bool contains( const T& element, bool equals( const T& a, const T& b  ) ) const {
		int match = 0;

		if (size()==0){
			return false;
		}
	
		Node* current = head;
		while(current->next->next!=NULL){
			for(int i =0; i < 50; ++i){
				if(current->arr[i] == element){
					match ++;
				}
			}
			current = current -> next;
		}

		for(int i =0; i < size()%50; ++i){
			if(current->next->arr[i] == element){
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
					if(current->arr[i]!=NULL)
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
			return (first->arr[i]);
		}else{
			Node* temp = head;

			for (int k = 0; k < (i -(i%50))/50; ++k){
				temp = temp -> next;
			}
			return (temp->arr[i%50]);
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
			return (first->arr[i]);
		}else{
			Node* temp = head;

			for (int k = 0; k < (i -(i%50))/50; ++k){
				temp = temp -> next;
			}
			return (temp->arr[i%50]);
		}
	}


  }; //end class CDAL
} // end namespace cop3530

#endif // _CDAL_H_
