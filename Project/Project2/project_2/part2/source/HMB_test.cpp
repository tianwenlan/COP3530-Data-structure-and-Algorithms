//#ifndef _HMB_H_
//#define _HMB_H_

// Author: Wenlan Tian
// Project 2 for COP 3530
// Part II: Hash map using buckets
// Date: 11/14/2014
// Version 1

#include <iostream>
#include <stdexcept>
#include "HMB.h"

int main(){

	HMB hmb;

	//when it's empty, test remove(),search(),is_empty(),size(),print() function
	char x = 'x';

//	hmb.remove(12,x);
//	hmb.search(12,x);
	std::cout << "When it's empty: " << std::endl;
	std::cout << (hmb.is_empty() ? "Current list is empty" : "Current list is not empty" ) << std::endl;
	std::cout << "current size: " << hmb.size() << std::endl;
//	hmb.print(std::cout);


	//test insert
	hmb.insert (12,'b');
	hmb.print(std::cout);

	hmb.insert (23,'d');
	hmb.print(std::cout);

	hmb.insert (15,'c');
	hmb.print(std::cout);

	hmb.insert (15,'e');
	hmb.print(std::cout);

	hmb.insert (16,'f');
	hmb.print(std::cout);

	hmb.insert (26,'g');
	hmb.print(std::cout);

	//test size
	std::cout << "current size: " << hmb.size() << std::endl;

	//test is_empty() when it's not empty
	std::cout << (hmb.is_empty() ? "Current list is empty" : "Current list is not empty" ) << std::endl;

	//test capacity
	std::cout << "Capacity: " << hmb.capacity() << std::endl;

	//test size
	std::cout << "Size: " << hmb.size() << std::endl;

	//test load
	std::cout << "Load: " << hmb.load() << std::endl;

	//test search
	char m = 'm';

	if(hmb.search(12,m)){
		std::cout << "found" << std::endl;
	}else{
		std::cout << "not found" << std::endl;
	}

	if(hmb.search(121,m)){
		std::cout << "found" << std::endl;
	}else{
		std::cout << "not found" << std::endl;
	}

	//test remove
	char y = 'y';
	hmb.remove (23,y);
	hmb.print(std::cout);

	//continue test insert()
	hmb.insert (37,'k');
	hmb.print(std::cout);

	hmb.insert (19,'l');
	hmb.print(std::cout);

	hmb.insert (47,'p');
	hmb.print(std::cout);

	hmb.insert (18,'q');
	hmb.print(std::cout);

	hmb.insert (11,'w');
	hmb.print(std::cout);

	hmb.insert (181,'o');
	hmb.print(std::cout);

//	hmb.insert (110,'z');  //throw out_of_rang exception
//	hmb.print(std::cout);
//
//	test clear()
	hmb.clear();
	std::cout << "current size: " << hmb.size() << std::endl;
//	hmb.print(std::cout);

	return 0;
}
