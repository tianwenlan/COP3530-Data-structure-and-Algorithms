// Author: Wenlan Tian
// Project 2 for COP 3530
// Part IV: Randomized Binary Search Tree
// Date: 11/30/2014
// Version 1

#include <iostream>
#include <stdexcept>
#include <string>
#include <queue>
#include <stack>
#include <cstdlib>
#include "RBST.h"

int main(){

///////////////TEST <unsigned int, char> ///////////
	RBST<unsigned int, char> rbst(50);
	//when it's empty, test remove(),search(),is_empty(),size(),print() function
	char x = 'x';

	//	rbst.remove(12,x);
	//	rbst.search(12,x);
	std::cout << "When it's empty: " << std::endl;
	std::cout << (rbst.is_empty() ? "Current list is empty" : "Current list is not empty" ) << std::endl;
	std::cout << "current size: " << rbst.size() << std::endl;
	//	rbst.print(std::cout);

	//test insert
	rbst.insert (12,'B');
	rbst.insert (12,'A');
	rbst.insert (15,'C');

	rbst.print(std::cout);

	std::cout<< std::endl;

	//test size
	std::cout << "Size: " << rbst.size() << std::endl;

	//test search
	char m = 'm';

	if(rbst.search(15,m)>0){
		std::cout << "found: " << rbst.search(15,m) << std::endl;
	}else{
		std::cout << "not found: " << rbst.search(15,m)<< std::endl;
	}

	if(rbst.search(17,m)>0){
		std::cout << "found: " << rbst.search(17,m) << std::endl;
	}else{
		std::cout << "not found: " << rbst.search(17,m)<< std::endl;
	}

	//test remove
	char y = 'y';
//	rbst.remove (12,y);
	rbst.print(std::cout);
	std::cout << std::endl;

	//test capacity
	std::cout << "Capacity: " << rbst.capacity() << std::endl;

	//test size
	std::cout << "Size: " << rbst.size() << std::endl;

	//test load
	std::cout << "Load: " << rbst.load() << std::endl;

	//test 	cluster_distribution()
//	rbst.cluster_distribution();
	//test clear()
	rbst.clear();
	std::cout << "Size: " << rbst.size() << std::endl;

/*
///////////////TEST <double, double> ///////////
	RBST<double, double> rbst1(50);
	//when it's empty, test remove(),search(),is_empty(),size(),print() function
	//	rbst1.remove(12,x);
	//	rbst1.search(12,x);
	std::cout << "When it's empty: " << std::endl;
	std::cout << (rbst1.is_empty() ? "Current list is empty" : "Current list is not empty" ) << std::endl;
	std::cout << "current size: " << rbst1.size() << std::endl;
	//	rbst1.print(std::cout);

	//test insert
	rbst1.insert (12.5,15.22);
	rbst1.insert (12.5,19.2);
	rbst1.insert (15.4,30.223);

	rbst1.print(std::cout);

	std::cout<< std::endl;

	//test size
	std::cout << "Size: " << rbst1.size() << std::endl;

	//test search
	if(rbst1.search(15.4,43.3)>0){
		std::cout << "found: " << rbst1.search(15,43.3) << std::endl;
	}else{
		std::cout << "not found: " << rbst1.search(15,43.3)<< std::endl;
	}

	if(rbst1.search(17.4,22.3)>0){
		std::cout << "found: " << rbst1.search(17,22.3) << std::endl;
	}else{
		std::cout << "not found: " << rbst1.search(17,22.3)<< std::endl;
	}

	//test remove
//	rbst.remove (12.5,44.4);
	rbst1.print(std::cout);
	std::cout << std::endl;

	//test capacity
	std::cout << "Capacity: " << rbst1.capacity() << std::endl;

	//test size
	std::cout << "Size: " << rbst1.size() << std::endl;

	//test load
	std::cout << "Load: " << rbst1.load() << std::endl;

	//test 	cluster_distribution()
//	rbst1.cluster_distribution();
//
*/
	return 0;
}
