// PSLL_test.cpp
// 
// Purpose: test my Pool-using Singly-Linked List
/// Author: Wenlan Tian
// Date: 09-28-1014
//
// =========================================================================

#include <iostream>
#include "PSLL.H"

bool same_char( const char& a, const char& b ) { // argument for contains()
  return (a == b); 
}

void in_list( const cop3530::PSLL<char>& list, char c, std::ostream& out ) {
  out << c << " is " << (list.contains( c, same_char ) ? "" : "not ")
	    << "in the list ";
//  list.print( out );
  out << std::endl;
}


int main() {

	cop3530::PSLL<char> l;

	//test is_empty() when it's empty
	std::cout << "When it's empty: " << std::endl;

	std::cout << (l.is_empty() ? "Current list is empty" : "Current list is not empty" ) << std::endl;

	//test size() when it's empty
	std::cout << "list_size: " << l.size() << std::endl;

	//test print() when it's empty
	std::cout << "current list:" << std::flush;
	l.print( std::cout ); 

	std::cout << std::endl;
	//test push_front() and print()
	for (int i = 0; i < 10000; ++i){
		l.push_back('A');
	}

	std::cout << "current list after push front 10000 'A':" << std::flush;
	l.print( std::cout ); 

	//test is_empty() when it's not empty
	std::cout << (l.is_empty() ? "Current list is empty" : "Current list is not empty" ) << std::endl;

	//test size()
	std::cout << "list_size: " << l.size() << std::endl;
	
	//test clear()
	l.clear();
	std::cout << "current list after clear:"  << std::flush;
	l.print( std::cout );

	//test push_back
	//from no element to 10000 elements: test no element case, and memory leak
	for (int i = 0; i < 10000; ++i){
		l.push_back('A');
	}

	std::cout << "current list after push back 10000 'A':" << std::flush;
	l.print( std::cout ); 
	std::cout << "list_size: " << l.size() << std::endl;

	//test item_at(position) 
	l.push_front('X');
	l.push_front('Y');
	l.push_front('Z');
	l.push_back('B');
	l.push_back('C');

	std::cout << "current list afer push_front or push_back five specific chars:" << std::flush;
	l.print( std::cout ); 

	std::cout << "item at position 0: " <<l.item_at(0)<< std::endl; // the first item
	std::cout << "item at position 1000: " << l.item_at(1000)<< std::endl; // the item in the middle
	// std::cout << "item at position 20000" <<l.item_at(20000) << std::endl; // the item does not exist, throw an exception

	//test T& operator[](int i)
	std::cout << "item at position 0: " <<l[0]<< std::endl; // the first item
	std::cout << "item at position 1000: " << l[1000]<< std::endl; // the item in the middle
	// std::cout << "item at position 20000" <<l[20000] << std::endl; // the item does not exist, throw an exception

	//test T const& operator[](int i) const
	const cop3530::PSLL<char> list=l;
	//std::cout << "item at position 0 in constant list: " <<list[0]<< std::endl; // the first item
	//std::cout << "item at position 1000 in constant list: " << list[1000]<< std::endl; // the item in the middle
	// std::cout << "item at position 20000" <<list[20000] << std::endl; // the item does not exist, throw an exception


	
	//test contains()
	in_list( l, 'x', std::cout );
	in_list( l, 'X', std::cout );
	in_list( l, 'Z', std::cout );
	in_list( l, 'C', std::cout );

	//test insert()
	l.insert( 'M', 0 );
	std::cout << "current list after insert 'M' at first position:" << std::flush;
	l.print( std::cout ); 
	l.insert( 'N', 4 );
	std::cout << "current list after insert 'N' at 4th position:" << std::flush;
	l.print( std::cout ); 
//	l.insert( 'Z', 20000 ); // throw an exception

	//test replace()
	l.replace( 'P', 4 );
	std::cout << "item at position 4" << l.item_at(4)<< std::endl; // the first item
	std::cout << "current list ater place position 4 with 'P': " << std::flush;
	l.print( std::cout ); 

	//test remove()
	l.remove(4);  //remove item at position 4
	l.remove(0);  //remove the first item
	std::cout << "current list after remove the items at positions 4 & 0 :" << std::flush;
	l.print( std::cout ); 
//	l.remove(20000);  //throw an exception

	//test pop_front()
	std::cout << "list_size before pop_front(): " << l.size() << std::endl;

	for (int i = 1; i <= 4000; ++i){
		l.pop_front();
	}

	std::cout<< "list_size after pop_front: " << l.size() << std::endl;

	//test pop_back()

	for (int i = 1; i <= 4000; ++i){
		l.pop_back();
	}

	std::cout<< "list_size after pop_back: " << l.size() << std::endl;
	std::cout << "current list after pop_back :" << std::flush;
	l.print( std::cout ); 

	///////////test iterator and const_iterator/////////////////
	
	//push_front and push_back five specific chars
	l.push_front('X');
	l.push_front('Y');
	l.push_front('Z');
	l.push_back('B');
	l.push_back('C');

	std::cout << "current list used for iterator test:" << std::flush;
	l.print( std::cout ); 

	///////iterator/////
	
		//test begin() and *()
		cop3530::PSLL<char>::iterator iter_begin = l.begin();
		std::cout << "The begin of the iterator is: " << *iter_begin << std::endl;

		//test ->()
		std::cout << "The begin of the iterator is: " << *(iter_begin.operator->()) << std::endl;

		//test end() and *()
		cop3530::PSLL<char>::iterator iter_end = l.end();
		//std::cout << "The end of the iterator is: " << *iter_end << std::endl;
		//Because the end() points to NULL, the program terminates
		
		//test immutable
		*iter_begin = 'M';
		std::cout << "After asign 'M' to the begin of the iterator: " << *iter_begin << std::endl;

		//test operator=()
		cop3530::PSLL<char>::iterator iter1;
		iter1 = iter_begin;
		std::cout << "The begin of the iter1 is: " << *iter1 << std::endl;

		//test operator++(int)
		std::cout << "The item should be M: " << *(iter_begin++) << std::endl;	

		//test operator++()
		std::cout << "The item should be X: " << *(++iter_begin) << std::endl;

		//test operator==() and operator!=() 
		cop3530::PSLL<char> l1;

		for(int i =0; i< 9998; ++i){
			l1.push_front('O');
		}
		l1.push_front('X');
		l1.push_front('Y');
		l1.push_front('M');
		l1.push_back('B');
		
		cop3530::PSLL<char>::iterator iter2 = l1.begin();

		//when they are same
		if (*iter1==*iter2){
			std::cout << "==() passed" << std::endl;
		}else {
			std::cout << "==() failed" << std::endl;
		}

		if (*iter1!=*iter2){
			std::cout << "!=() failed" << std::endl;
		}else {
			std::cout << "!=() passed" << std::endl;
		}

		//when they are different
		if (*iter1==*(++iter2)){
			std::cout << "==() failed" << std::endl;
		}else {
			std::cout << "==() passed" << std::endl;
		}

		if (*iter1!=*(++iter2)){
			std::cout << "!=() passed" << std::endl;
		}else {
			std::cout << "!=() failed" << std::endl;
		}


	///////const_iterator/////
		const cop3530::PSLL<char> *const_list = &l;

		//test begin() and *()
		cop3530::PSLL<char>::const_iterator const_iter_begin = const_list->begin();
		std::cout <<  "The begin of the const iterator is: " << *const_iter_begin << std::endl;
		//std::cout << "The end of the const iterator is: " << *const_iter_end << std::endl;
		
		//test ->()
		std::cout << "The begin of the const iterator is: " << *(const_iter_begin.operator->()) << std::endl;

		//test end() and *()
		cop3530::PSLL<char>::const_iterator const_iter_end = const_list->end();
		//std::cout << "The end of the const iterator is: " << *cosnt_iter_end << std::endl;
		//Because the end() points to NULL, the program terminates
		
		//test immutable
		// *const_iter_begin = 'M'; //throw exception

		//test operator=()
		cop3530::PSLL<char>::const_iterator const_iter1;
		const_iter1 = const_iter_begin;
		std::cout << "The begin of the iter1 is: " << *const_iter1 << std::endl;

		//test operator++(int)
		std::cout << "The item should be M: " << *(const_iter_begin++) << std::endl;	

		//test operator++()
		std::cout << "The item should be X: " << *(++const_iter_begin) << std::endl;

		for(int i =0; i< 9998; ++i){
			l1.push_front('O');
		}
		l.push_front('X');
		l.push_front('Y');
		l.push_front('M');
		l.push_back('B');

		//test operator==() and operator!=() 
		const cop3530::PSLL<char> *const_l1 = &l;
		
		cop3530::PSLL<char>::const_iterator const_iter2 = const_l1->begin();

		//when they are same
		if (*const_iter1==*const_iter2){
			std::cout << "==() passed" << std::endl;
		}else {
			std::cout << "==() failed" << std::endl;
		}

		if (*const_iter1!=*const_iter2){
			std::cout << "!=() failed" << std::endl;
		}else {
			std::cout << "!=() passed" << std::endl;
		}

		//when they are different
		if (*const_iter1==*(++const_iter2)){
			std::cout << "==() failed" << std::endl;
		}else {
			std::cout << "==() passed" << std::endl;
		}

		if (*const_iter1!=*(++const_iter2)){
			std::cout << "!=() passed" << std::endl;
		}else {
			std::cout << "!=() failed" << std::endl;
		}
}
  

/*
	std::cout << "list_size: " << l.size() << std::endl;
	std::cout << "pool_size: " << l.poolSize() << std::endl;

*/
