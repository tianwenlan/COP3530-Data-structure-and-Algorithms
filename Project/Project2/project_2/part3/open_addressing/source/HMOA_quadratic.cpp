// Author: Wenlan Tian
// Project 2 for COP 3530
// Part III-1: Hash map with open addressing, quadratic probing
// Date: 11/24/2014
// Version 1

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "HMOA_quadratic.h"

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
//	hmoa.remove (23,y);
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

	///////////////TEST <double, double> ///////////
	HMOA<double, double> hmoa1;
	//when it's empty, test remove(),search(),is_empty(),size(),print() function

//	hmoa1.remove(12.6,14.3);
//	hmoa1.search(12.6,56.3);
	std::cout << "When it's empty: " << std::endl;
	std::cout << (hmoa1.is_empty() ? "Current list is empty" : "Current list is not empty" ) << std::endl;
	std::cout << "current size: " << hmoa1.size() << std::endl;
//	hmoa1.print(std::cout);

	//test insert
	hmoa1.insert (12.5,35.1);
	hmoa1.print(std::cout);

	hmoa1.insert (23.5,35.3);
	hmoa1.print(std::cout);

	hmoa1.insert (15.3,13.6);
	hmoa1.print(std::cout);

	hmoa1.insert (15.3,30.3);
	hmoa1.print(std::cout);

	hmoa1.insert (16.6,220.3);
	hmoa1.print(std::cout);

	//test 	cluster_distribution()
	hmoa1.cluster_distribution();


	hmoa1.insert (26.2,35.6);
	hmoa1.print(std::cout);

	//test size
	std::cout << "current size: " << hmoa1.size() << std::endl;

	//test is_empty() when it's not empty
	std::cout << (hmoa1.is_empty() ? "Current list is empty" : "Current list is not empty" ) << std::endl;

	//test capacity
	std::cout << "Capacity: " << hmoa1.capacity() << std::endl;

	//test size
	std::cout << "Size: " << hmoa1.size() << std::endl;

	//test load
	std::cout << "Load: " << hmoa1.load() << std::endl;


/*	//test search

	if(hmoa1.search(23.5,24.3)>0){
		std::cout << "found" << std::endl;
	}else{
		std::cout << "not found" << std::endl;
	}

	if(hmoa1.search(28.5,35.3)>0){
		std::cout << "found" << std::endl;
	}else{
		std::cout << "not found" << std::endl;
	}

	//test remove
	hmoa1.remove (23.5,35.2);
	hmoa1.print(std::cout);
*/
	//continue test insert()
	hmoa1.insert (37.2,52.4);
	hmoa1.print(std::cout);

	hmoa1.insert (1933.2,52.22);
	hmoa1.print(std::cout);

	//test 	cluster_distribution()
	hmoa1.cluster_distribution();

	hmoa1.insert (47.653,202.3);
	hmoa1.print(std::cout);

	hmoa1.insert (102.2,103.3);
	hmoa1.print(std::cout);

	hmoa1.insert (11.42,203.2);
	hmoa1.print(std::cout);

	hmoa1.insert (181.35,52.3);
	hmoa1.print(std::cout);

//	hmoa1.insert (110.3,204.4);  //throw out_of_rang exception
//	hmoa1.print(std::cout);

//	test remove_random()
	hmoa1.remove_random();
	hmoa1.print(std::cout);

//	test clear()
	hmoa1.clear();
	std::cout << "current size: " << hmoa1.size() << std::endl;
//	hmoa1.print(std::cout);
//


	return 0;
}
