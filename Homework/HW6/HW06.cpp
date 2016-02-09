//Author: Wenlan Tian
//Date: Nov 04, 2014
//
//HW06: implement 0-1 knapsack

#include <iostream>
#include <string>

int max(int a, int b){
	return (a >b) ? a:b;
}

int sack(int weight[], int value[], std::string name[], int itemType, int capacity){
	int item[itemType+1][capacity+1];
	for (int i =0; i <= itemType; ++i){
		for (int j =0; j <= capacity; ++j){
			if (i == 0 || j == 0) {
				item[i][j]= 0;
			}else if(weight[i-1]<=j){
				item[i][j] = max(value[i-1]+item[i-1][j-weight[i-1]] ,item[i-1][j]);
			}else{
				item[i][j] = item[i-1][j];
			}
		}
	}

	//print the items to be taken
	std::cout << "An optimal solution to this problem is to take: " << std::flush;
	int j = capacity; 

	for (int i = itemType; i > 0; --i){
		if (item[i][j]!=item[i-1][j]){
			std::cout << name[i-1] << " " << std::flush;
			j -= weight[i-1];
			if (j<0) break;
		}
	}

	std::cout << std::endl;

	return item[itemType][capacity];
}

int main(){
	int weight[] = {3,6,4,2};
	int value[] = {14,30,17,9};
	std::string name[] = {"A","B","C","D"};
	int capacity = 10;
	int itemType = sizeof(value)/sizeof(value[0]);
	sack(weight, value, name, itemType, capacity);

	return 0;
}
