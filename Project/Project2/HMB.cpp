//#ifndef _HMB_H_
//#define _HMB_H_

// Author: Wenlan Tian
// Project 2 for COP 3530
// Part II: Hash map using buckets
// Date: 11/14/2014
// Version 1

#include <iostream>
#include <stdexcept>

const int mapSize = 10;

class HMB{
	struct Node{
		int key;
		char value;
		Node* next;

		Node():key(0),value('\0'),next(NULL){
		}
	};

	private:
		Node* a[mapSize];
		int mySize;
	public:
		HMB();
		int hash(int);
		bool insert (int, char);
		bool remove (int, char&);
		bool search (int, char&);
		void clear();
		bool is_empty();
		std::size_t capacity();
		std::size_t size();
		double load();
		std::ostream& print (std::ostream&) const;
};

HMB::HMB():mySize(0){
	for (int i =0; i < mapSize; ++i){
		a[i]=NULL;
	}
}

int HMB::hash(int key){
	return key % mapSize;
}

//if there is space available, adds the specified key/value-pair to the hash map and returns true; otherwise returns false. 
//If an item already exists in the map with the same key, replace its value.
bool HMB::insert(int key, char value){

	if(size()==capacity()){
		throw std::out_of_range("Map is full!");
	}

	int i = hash(key);

	Node* before = a[i];

	if (before == NULL){
		Node* current = new Node();
		current -> key = key;
		current -> value = value;
		a[i] = current;
	}else if (before->next == NULL){
		if (before->key == key){
			before->value = value;
			return false;
		}else{
			before -> next = new Node();
			before -> next -> key = key;
			before -> next -> value = value;
		}
	}else{
		while (before ->next != NULL){
			if (before->next->key == key){
				before->next->value = value;
				return false;
			}
			before = before -> next;
		}
		before -> next = new Node();
		before -> next -> key = key;
		before -> next -> value = value;
	}

	mySize ++;
	return true;
}

//if there is an item matching key, removes the key/value-pair from the map, stores it's value in value, 
//and returns true; otherwise returns false.
bool HMB::remove(int key, char& value){
	if(is_empty()){
		throw std::out_of_range("Empty map!");
	}

	if (!search(key, value)) return false;

	int i = hash(key);

	Node* before = a[i];

	if (!before -> next){
		a[i] = NULL;
	}else{
		while (before -> next){
			if (before->next->key == key){
				before->next->value = value;
				break;
			}
			before = before -> next;
		}

		std::cout << before -> key << std::endl;

		if (before -> next -> next){

			before -> next = before -> next -> next;
		}else{
			before -> next = NULL;
		}
	}
	mySize --;
	return true;
}

//if there is an item matching key, stores it's value in value, and returns true (the item remains in the map); 
//otherwise returns false.
bool HMB::search(int key, char& value){
	if(is_empty()){
		throw std::out_of_range("Empty map!");
	}

	int i = hash(key);

	Node* current = a[i];

	if (current == NULL){
		return false;
	}
	
	if(!current -> next ){
		if (current -> key == key){
			current -> value = value;
			return true;
		}else{
			return false;
		}

	}

	//current -> next != NULL

	while (current -> next){			
		if (current -> key == key){
			current -> value = value;
			return true;
		}

			current = current -> next;
	}

	return false;

}

//removes all items from the map.
void HMB::clear(){
	for (int i =0; i< mapSize; ++i){
		if(a[i]){
			Node* before = a[i];
			if (!before -> next){
				a[i]=NULL;
				delete before;
			}else{

				while (before -> next != NULL){
					before = before -> next;
				}

				Node * current = before -> next;

				before -> next = NULL;

				delete current;
			}
		}
	}

	mySize = 0;
}

//returns true IFF the map contains no elements.
bool HMB::is_empty(){
	return (mySize==0)? true : false;
}

//returns the number of slots in the map.
std::size_t HMB::capacity(){
	return mapSize;
}

//returns the number of items actually stored in the map.
std::size_t HMB::size(){
	return mySize;
}

//returns the map's load factor (size = load * capacity).
double HMB::load(){
	return (double)size()/(double) capacity();
}

//inserts into the ostream, the backing array's contents in sequential order. 
//Empty slots shall be denoted by a hyphen, non-empty slots by that item's key. 
//[This function will be used for debugging/monitoring].
std::ostream& HMB::print( std::ostream& ostream ) const{
	ostream << "[" ;

	for (int i =0; i < mapSize; ++i){
		if(!a[i]){
			ostream << '-' << std::flush;
		}else{
			Node* current = a[i];
			ostream << current->key;
			while (current -> next!=NULL){
				current = current -> next;
				ostream << "," << current-> key;
			}
		}
		if (i!=mapSize-1){
			ostream << "|" ;
		}
	}
	
	ostream << "]" << std::endl;
	return ostream;

}

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
