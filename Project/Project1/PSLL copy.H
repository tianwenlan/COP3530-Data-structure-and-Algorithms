#ifndef _PSLL_H_
#define _PSLL_H_

// PSLL.H
// 
// Pool-Using Singly-linked list (PSLL)
//
// Author: Wenlan Tian
// Project 1 for COP 3530
// Date: 09/17/2014
// Version 1

#include <iostream>
#include <stdexcept>

namespace cop3530 {

	template <typename T>
	class PSLL {
	private:
    struct Node {
		T data;
		Node* next;

		Node():data(),next(NULL){}

    }; // end struct Node

	Node* head;
	Node* tail;
 	Node* free;

	int list_size;
	int pool_size;

	void shrink(){
		for (int i =0; i < (pool_size - (list_size/2)) ;++i){
			Node* before_pool = free;
			while(before_pool-> next ->next != NULL){
				before_pool= before_pool -> next;
			}
			Node* current_pool = before_pool->next;
			before_pool->next = NULL;
			pool_size--;
			delete current_pool;
		}
	}


	public:

		class PSLL_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
		typedef PSLL_Iter self_type;
		typedef PSLL_Iter& self_reference;

      
		private:
			Node* here;
      
		public:
		explicit PSLL_Iter( Node* start = NULL ) : here( start ) {
		}
		PSLL_Iter( const PSLL_Iter& src ) : here( src.here ) {
		}
       
		reference operator*() const {
			if(here == NULL){
				throw std::invalid_argument("Null in the iterator");
			}

			return here -> data;
		}
		pointer operator->() const {
			if(here == NULL){
				throw std::invalid_argument("Null in the iterator");
			}

			return &(operator*());
		}
      
		self_reference operator=( const PSLL_Iter& src ) {
			here = src.here;
			return *this;	
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

		bool operator==(const PSLL_Iter& rhs) const {
			return here == rhs.here;
		}
		bool operator!=(const PSLL_Iter& rhs) const {
			return here != rhs.here;
		}
     }; // end PSLL_Iter

    class PSLL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
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
		typedef PSLL_Const_Iter self_type;
		typedef PSLL_Const_Iter& self_reference;
      
     private:
		const Node* here;
      
     public:
		explicit PSLL_Const_Iter( Node* start = NULL ) : here( start ) {
		}
		PSLL_Const_Iter( const PSLL_Const_Iter& src ) : here( src.here ) {
		}
       
		reference operator*() const {
			if(here == NULL){
				throw std::invalid_argument("Null in the iterator");
			}

			return here -> data;
		}

		pointer operator->() const {
			if(here == NULL){
				throw std::invalid_argument("Null in the iterator");
			}

			return &(operator*());
		}
      
		self_reference operator=( const PSLL_Const_Iter& src ) {
			here = src.here;
			return *this;	
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

		bool operator==(const PSLL_Const_Iter& rhs) const {
			return here == rhs.here;
		}

		bool operator!=(const PSLL_Const_Iter& rhs) const {
			return here != rhs.here;
		}
     }; // end PSLL_Const_Iter

	//--------------------------------------------------
	// types
    //--------------------------------------------------
	typedef std::size_t size_t;
	typedef T value_type;
	typedef PSLL_Iter iterator;
	typedef PSLL_Const_Iter const_iterator;	

	iterator begin() {
		return PSLL_Iter( head ); 
	}

    iterator end() {
		return PSLL_Iter(tail->next ); 
	}
     
    const_iterator begin() const { 
		return PSLL_Const_Iter( head ); 
	}
    const_iterator end() const {
		return PSLL_Const_Iter( tail->next ); 
	} 



    //--------------------------------------------------
    // Constructors/destructor/assignment operator
    //--------------------------------------------------

    PSLL():head(NULL),tail(NULL),free(NULL), list_size(0),pool_size(0){
	}
    
    //--------------------------------------------------
    PSLL( const PSLL& src ) {
	}
    
    //--------------------------------------------------
    ~PSLL() {
		// safely dispose of this PSLL's contents
		clear();
    }
    
    //--------------------------------------------------
    PSLL& operator=( const PSLL& src ) {
		if (src.head == NULL){
			throw std::out_of_range("Try to copy an empty list!");
		}

		if ( &src == this ) // check for self-assignment
			return *this;     // do nothing

		// safely dispose of this SSLL's contents
		if(head!=NULL){
			clear();
		}

		// populate this SSLL with copies of the other SSLL's contents
		Node* current = src.head;
		while(current!= NULL){
			push_back(current->data);
			current= current->next;
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
			throw std::domain_error("Invalid position!");
		}
			
		if (position == 0 || size()==0){
			push_front(element);
		}else if (position == size()){
			push_back(element);
		}else{	
			Node* current_pool = free;

			Node* before = head;
			int count = 1;

			while (count != position){
				count ++;
				before = before -> next;
			}

			if(current_pool==NULL){
				Node* temp = new Node();
				temp ->data = element;
				temp -> next = before -> next;
				before -> next = temp;
			}else if(current_pool->next ==NULL){
				current_pool->data = element;
				current_pool->next = before->next;
				before ->next = current_pool;
				free = NULL;
				pool_size--;
			}else{
				Node* before_pool = free;

				while(before_pool->next -> next!= NULL){
					before_pool = before_pool->next;
				}
				before_pool -> next -> next = before-> next;
				before-> next = before_pool -> next;
				before -> next -> data = element;
				before_pool -> next = NULL;
				pool_size--;

				if(size()>=100 && pool_size > size()/2){
					shrink();
				}
			}
			list_size++;
		}
	}
    
    //--------------------------------------------------
    void push_front( const T& element ) {
		Node* current_pool = free;

		if(size()==0){
			if(free==NULL){
				Node* temp = new Node();
				temp -> data = element;
				head = temp;
				tail = head;
			}else if(current_pool->next ==NULL){
				current_pool->data = element;
				head = current_pool;
				tail = head;
				free = NULL;
				pool_size--;
			}else{
				Node* before_pool = free;
				while(before_pool->next !=NULL){
					before_pool = before_pool->next;
				}
				before_pool-> next-> data = element;
				head = before_pool-> next;
				before_pool ->next = NULL;
				pool_size--;

				if(size()>=100 && pool_size > size()/2){
					shrink();
				}
			}
		}else{
			if (current_pool == NULL){
				Node* temp = new Node();
				temp -> data = element;
				temp -> next = head;
				head = temp;
			}else if(current_pool->next ==NULL){
				current_pool->data = element;
				current_pool->next = head;
				head = current_pool;
				pool_size--;
			}else{
				Node* before_pool = free;
				while(before_pool->next !=NULL){
					before_pool = before_pool->next;
				}
				before_pool-> next-> data = element;
				before_pool-> next-> next = head;
				head = before_pool-> next;
				before_pool ->next = NULL;
				pool_size--;

				if(size()>=100 && pool_size > size()/2){
					shrink();
				}

			}
		}
		list_size++;
	}
    
    //--------------------------------------------------
    void push_back( const T& element ) {
		Node* current_pool = free;

		if(size()==0){
			if(free == NULL){
				Node* temp = new Node();
				temp -> data = element;
				head = temp;
				tail = head;
			}else if(current_pool->next ==NULL){
				current_pool->data = element;
				head = current_pool;
				tail = head;
				free = NULL;
				pool_size--;
			}else{
				Node* before_pool = free;
				while(before_pool->next ->next !=NULL){
					before_pool = before_pool->next;
				}
				before_pool-> next-> data = element;
				head = before_pool-> next;
				tail = head;
				before_pool ->next = NULL;
				pool_size--;
				if(size()>=100 && pool_size > size()/2){
					shrink();
				}

			}
		}else{
			Node* current = head;
			while (current -> next != NULL){
				current = current -> next;
			}

			if (free==NULL){
				Node* temp = new Node();
				temp -> data = element;

				current -> next = temp;
				tail = temp;
			}else if(current_pool -> next ==NULL){
				current_pool->data = element;
				current -> next = current_pool;
				tail = current_pool;
				free = NULL;
				pool_size--;
			}else{
				Node* before_pool = free;

				while(before_pool->next ->next !=NULL){
					before_pool = before_pool->next;
				}
				before_pool->next->data = element;
				current -> next = before_pool->next;
				tail = current ->next;
				before_pool ->next = NULL;
				pool_size--;

				if(size()>=100 && pool_size > size()/2){
					shrink();
				}

			}
		}
		list_size++;
	}
    
    //--------------------------------------------------we
    T pop_front() {

		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}

		Node* current_list = head;
				
		if(free==NULL){
			head = current_list->next;
			free = current_list;
			pool_size++;
			current_list -> next = NULL;
			list_size--;
			return current_list->data;
		}else{

			Node* current_pool = free;

			while(current_pool->next!=NULL){
				current_pool = current_pool->next;
			}
			T result = current_list->data;

			head = current_list->next;

			current_pool->next = current_list;
			pool_size++;
			current_list -> next = NULL;
			list_size--;

			if(list_size >=100 && pool_size > list_size/2){
					shrink();
			}

			return result;
		}
	}

    //--------------------------------------------------
    T pop_back() {

		if (is_empty()){
			throw std::out_of_range("Empty list!");
		}

		Node* current_list = head;

		if(size()==1 && free == NULL){
			free = current_list;
			pool_size++;
			head = NULL;
			tail = NULL;
			list_size--;
			return current_list->data;
		}else if(size()==1 && free != NULL){
			Node* current_pool = free;

			while(current_pool->next!=NULL){
				current_pool = current_pool->next;
			}
			current_pool->next = current_list;
			pool_size++;

			if(size()>=100 && pool_size > size()/2){
				shrink();
			}

			head = NULL;
			tail = NULL;
			list_size--;
			return current_list->data;
		}else{

			Node* current_pool = free;

			Node* before = head;

			while (before -> next -> next != NULL){  //
				before = before -> next;
			}

			T result = before->next->data;

			if(free == NULL){
				free = before->next;
			}else{
				while(current_pool->next!=NULL){
					current_pool = current_pool->next;
				}
				current_pool->next =  before->next;
			}
			pool_size++;

			if((size()>=100) && (pool_size > size()/2)){
				shrink();
			}

			before->next = NULL;
			list_size--;
			tail = before;
			return result;

		}
	
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
		}else{

			Node* before = head;

			int count = 1;

			while (count != position){
				count ++;
				before = before -> next;
			}

			Node* current = before -> next;
			
			before -> next = before -> next -> next;

			if(free == NULL){
				free = current;
				current -> next = NULL;
			}else{
				Node* current_pool = free;

				while(current_pool->next!=NULL){
					current_pool = current_pool->next;
				}		
				current_pool->next = current;
				current -> next = NULL;
			}
			pool_size++;
			list_size--;

			if(size()>=100 && pool_size > size()/2){
				shrink();
			}

			return current->data;
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
		
		Node* temp = head;
		int count = 0;
		T result;

		while (temp != NULL){
			if(count == position){
				result = temp -> data;
				break;
			}
			temp = temp-> next;
			count ++;
		}

		return result;
	}

    //--------------------------------------------------
    bool is_empty() const {
		return (head == NULL)? true : false;
	}

    //--------------------------------------------------
    size_t size() const {
		return list_size;
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
		if(size()!=0){
			Node* temp = head;
			while(temp!=NULL){
				if(temp->data == element){
					match ++;
				}
				temp = temp -> next;
			}

			if(match == 1){
				return true;
			}else{
				return false;
			}
		}

		return false;
	}

    //--------------------------------------------------
    std::ostream& print( std::ostream& out ) const {
		if(size()==0){
			out << "<empty list>" << std::endl;
		}else if (size()==1){
			Node* temp = head;
			out << "[" << temp->data <<  "]" << std::endl;
		}else{
			Node* temp = head;
			out << "[" << temp ->data;
			temp = temp -> next;
			while(temp!=NULL){
				out << "," << temp->data;
				temp = temp -> next;
			}
			out << "]" << std::endl;
		}

		if(free==NULL){
			std::cout << "<empty pool>" << std::endl;
		}else{
			Node* temp_pool = free;
			int count_pool = 0;
			while (temp_pool != NULL){
				count_pool ++;
				temp_pool = temp_pool -> next;
			}
			out << "Pool size: "<< std::flush;
			out << count_pool << std::endl;
		}
	}

	T& operator[](int i){
		if (is_empty()){
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

	T const& operator[](int i) const{
		if (is_empty()){
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


  }; //end class PSLL


} // end namespace cop3530

#endif // _PSLL_H_

