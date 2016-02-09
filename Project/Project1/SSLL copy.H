#ifndef _SSLL_H_
#define _SSLL_H_

// SSLL.H
// 
// Singly-linked list (non-polymorphic)
//
// Author: Wenlan Tian
// Project 1 for COP 3530
// Date: 09/17/2014
// Version 1

#include <iostream>

namespace cop3530 {

  template <typename T>
  class SSLL {
  private:
    struct Node {
		T data;
		Node* next;

		Node():data(),next(NULL){
		}

    }; // end struct Node

	Node* head;
	Node* tail;
	int mySize;

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
			if(here == NULL){
				throw std::invalid_argument("Null in the iterator");
			}
			return here -> data;;
		}
		pointer operator->() const {
			if(here == NULL){
				throw std::invalid_argument("Null in the iterator");
			}
			return *(here -> data);
		}

		//copy an iterator..      
		self_reference operator=( const SSLL_Iter& src ) {
			here->data = src.here->data;
			return *this;
		}

		self_reference operator++() {
			here = here ->next;
			return *this;
		} // preincrement

		self_type operator++(int) {
			self_type result = *this;
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
		return SSLL_Iter(tail->next ); 
	}
     
    const_iterator begin() const { 
		return SSLL_Const_Iter( head ); 
	}
    const_iterator end() const {
		return SSLL_Const_Iter( tail->next ); 
	} 


    //--------------------------------------------------
    // Constructors/destructor/assignment operator
    //--------------------------------------------------

    SSLL():head(NULL),tail(NULL),mySize(0) {
	}
    
    //--------------------------------------------------
    SSLL( const SSLL& src ) {
	}
    
    //--------------------------------------------------
    ~SSLL()  {
		clear();
      // safely dispose of this SSLL's contents
    }
    
    //--------------------------------------------------
    SSLL& operator=( const SSLL& src ) {
      if ( &src == this ) // check for self-assignment
	return *this;     // do nothing
      
      // safely dispose of this SSLL's contents
      // populate this SSLL with copies of the other SSLL's contents
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

		Node* current = head;
		int count = 0;

		while (count != position){
			current = current -> next;
			count ++;
		}

		T result = current -> data;
		current -> data = element;
		return result;
	}

    //--------------------------------------------------
    void insert( const T& element, int position ) {
		if (position < 0 || position > size()){
			throw std::domain_error("Invalid insertion position!");
		}
		
		if (position == 0){
			push_front(element);
		}else if (position == size() || size()==0){
			push_back(element);
		}else{
			Node* before = head;
			int count = 0;

			while (before != NULL){
				count ++;
				if(count != position){
					before = before -> next;
				}else{
					break;
				}
			}

			Node* temp = new Node();
			temp ->data = element;

			temp -> next = before -> next;
			before -> next = temp;

			mySize ++;
		//	delete temp;

		}
	}
    
    //--------------------------------------------------
    void push_front( const T& element ) {
		Node* temp = new Node();
		temp -> data = element;

		if(is_empty()){
			head = temp;
		}else{
			temp -> next = head;
			head = temp;
		}

		mySize++;
//		delete temp;
	}
    
    //--------------------------------------------------
    void push_back( const T& element ) {
		Node* temp = new Node();
		temp -> data = element;

		if(is_empty()){
			head = temp;
		}
	//	else if(size()==1){
	//		Node* current = head;
	//		current->next = temp;
	//	}
		
		else{
			Node* current = head;

			while (current -> next != NULL){
				current = current -> next;
			}
			current -> next = temp;
		}
		tail = temp;
		mySize++;

//		delete temp;
	}
    
    //--------------------------------------------------
    T pop_front() {
		if(is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		Node* current = head;
		
		if(size()==1){
			head = NULL;
			tail = NULL;
			mySize--;
			return current->data;
		}else{
			T result;
			result = current->data;
			head = current -> next;
			mySize--;
			return result;
		}
	}

    //--------------------------------------------------
    T pop_back() {
		if(is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		Node* before = head;
		if (size()==1){
			head = NULL;
			tail = NULL;
			mySize --;
			return before ->data;
		}else{

			while(before -> next ->next != NULL){
				before = before -> next;
			}
			T result = before -> next ->data;

			before -> next = NULL;
			tail = before;
			mySize--;

			return result;
		}
	}

    //--------------------------------------------------
    T remove( int position ) {
		if(is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (position < 0 || position >= size()){
			throw std::domain_error("Invalid position!");
		}
		
		if (position == 0){
			return pop_front();
		}else if (position == size()-1){
			return pop_back();
		}else{

			Node* temp = new Node();
			Node* before = head;
			int count = 1;

			while (count != position){
				count ++;
				before = before -> next;
			}

			temp = before -> next;
			before -> next = temp -> next;
			T result = temp ->data;
	//		delete temp;
			mySize--;
			return result;
		}
	}

    //--------------------------------------------------
    T item_at( int position ) const {
		if(is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (position < 0 || position >= size()){
			throw std::domain_error("Invalid position!");
		}
		
		Node* current = head;
		int count = 0;

		while (current != NULL){
			if(count == position){
				break;
			}
			current = current-> next;
			count ++;
		}
		return (current -> data);
	}

    //--------------------------------------------------
    bool is_empty() const {
		return (head == NULL)? true :false;
	}

    //--------------------------------------------------
    size_t size() const {
		return mySize;
	}

    //--------------------------------------------------
    void clear() {
		while(head!=NULL){
			pop_back();
		}
	}

    //--------------------------------------------------
    bool contains( const T& element, bool equals( const T& a, const T& b  ) ) const {
		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}

		int match = 0;
		
		Node* temp = head;
		while(temp!=NULL){
			if(temp->data == element){
				match ++;
			}
			temp = temp -> next;
		}

		return (match == 1) ? true :false;
	}

    //--------------------------------------------------
    std::ostream& print( std::ostream& out ) const {
		if(size()==0){
			std::cout << "<empty list>" << std::endl;
		}else if (size()==1){
			Node* temp = head;
		    out << "[" << temp->data <<  "]" << std::endl;
			return out;
		}else{
			Node* temp = head;
			out << "[" << temp ->data;
			temp = temp -> next;
			while(temp->next!=NULL){
				out << "," << temp->data;
				temp = temp -> next;
			}
			out << "]" << std::endl;
			return out;
		}
	}

	T& operator[](int i){
		if(is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (i< 0 || i >= size()){
			throw std::domain_error("Invalid index!");
		}
		
		Node* temp = head;

		for (int k = 0; k < i; ++k){
			temp = temp-> next;
		}
		return (temp -> data);
	}

	T const& operator[](int i) const{
		if(is_empty()){
			throw std::out_of_range("Empty list!");
		}
		
		if (i < 0 || i >= size()){
			throw std::domain_error("Invalid index!");
		}

		Node* temp = head;

		for (int k = 0; k < i; ++k){
			temp = temp-> next;
		}
		return (temp -> data);
	}

  }; //end class SSLL

} // end namespace cop3530

#endif // _SSLL_H_
