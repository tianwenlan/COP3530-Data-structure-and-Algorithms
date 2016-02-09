// Author: Wenlan Tian
// Project 2 for COP 3530
// Part V: 2. Hash map with open addressing, linear probing
// Date: 12/04/2014
// Version 1

#include <iostream>
#include <cstdlib>
#include <string>


int main(){

	int origin[5] = {4983, 2028, 10555, 10550, 10555};

	for (int i =0; i < 5; ++i){
		int current = origin[i];

		for (double j = 0; j < 1.05; j+=0.05){
			std::cout << (int)(current + j* current) << std::endl;
		}
	}

	return 0;
}
