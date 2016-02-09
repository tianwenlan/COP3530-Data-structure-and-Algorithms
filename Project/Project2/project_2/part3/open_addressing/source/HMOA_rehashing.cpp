// Author: Wenlan Tian
// Project 2 for COP 3530
// Part III-3: Hash map with open addressing, rehashing probing
// Date: 11/24/2014
// Version 1

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "HMOA_rehashing.h"

int main(){

///////////////TEST <int, char> ///////////
	HMOA<int, char> hmoa;
	//when it's empty, test remove(),search(),is_empty(),size(),print() function
	char x = 'x';

//	hmoa.remove(12,x);
//	hmoa.search(12,x);
	std::cout << "When it's empty: " << std::endl;
	std::cout << (hmoa.is_empty() ? "Current list is empty" : "Current list is not empty" ) << std::endl;
	std::cout << "current size: " << hmoa.size() << std::endl;
//	hmoa.print(std::cout);

	//test insert
	hmoa.insert (12,'b');
	hmoa.print(std::cout);

	hmoa.insert (23,'d');
	hmoa.print(std::cout);

	hmoa.insert (15,'c');
	hmoa.print(std::cout);

	hmoa.insert (15,'e');
	hmoa.print(std::cout);

	hmoa.insert (16,'f');
	hmoa.print(std::cout);

	//test 	cluster_distribution()
	hmoa.cluster_distribution();


	hmoa.insert (26,'g');
	hmoa.print(std::cout);

	//test size
	std::cout << "current size: " << hmoa.size() << std::endl;

	//test is_empty() when it's not empty
	std::cout << (hmoa.is_empty() ? "Current list is empty" : "Current list is not empty" ) << std::endl;

	//test capacity
	std::cout << "Capacity: " << hmoa.capacity() << std::endl;

	//test size
	std::cout << "Size: " << hmoa.size() << std::endl;

	//test load
	std::cout << "Load: " << hmoa.load() << std::endl;


	//test search
	char m = 'm';

	if(hmoa.search(23,m)>0){
		std::cout << "found" << std::endl;
	}else{
		std::cout << "not found" << std::endl;
	}

	if(hmoa.search(121,m)>0){
		std::cout << "found" << std::endl;
	}else{
		std::cout << "not found" << std::endl;
	}

	//test remove
	char y = 'y';
	hmoa.remove (23,y);
	hmoa.print(std::cout);

	//continue test insert()
	hmoa.insert (37,'k');
	hmoa.print(std::cout);

	hmoa.insert (19,'l');
	hmoa.print(std::cout);

	//test 	cluster_distribution()
	hmoa.cluster_distribution();


	hmoa.insert (47,'p');
	hmoa.print(std::cout);

	hmoa.insert (18,'q');
	hmoa.print(std::cout);

	hmoa.insert (11,'w');
	hmoa.print(std::cout);

	hmoa.insert (181,'o');
	hmoa.print(std::cout);

//	hmoa.insert (110,'z');  //throw out_of_rang exception
//	hmoa.print(std::cout);

//	test remove_random()
	hmoa.remove_random();
	hmoa.print(std::cout);

//	test clear()
	hmoa.clear();
	std::cout << "current size: " << hmoa.size() << std::endl;
//	hmoa.print(std::cout);
//

	return 0;
}
