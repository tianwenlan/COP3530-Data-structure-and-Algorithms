#ifndef _HMOA_H_
#define _HMOA_H_

#include <iostream>
#include <stdexcept>

const int mapSize = 10;

class HMOA{
	private:
		struct item{
			int key;
			char value;
		};
		item a[mapSize];
		int mySize;
	public:
		HMOA();
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

HMOA::HMOA():mySize(0){
	for (int i =0; i < mapSize; ++i){
		a[i].key=0;
		a[i].value='\0';
	}
}

int HMOA::hash(int key){
	return key % mapSize;
}

//if there is space available, adds the specified key/value-pair to the hash map and returns true; otherwise returns false. 
//If an item already exists in the map with the same key, replace its value.
bool HMOA::insert(int key, char value){

	if(size()==capacity()){
		throw std::out_of_range("Map is full!");
	}

	int i = hash(key);

	while(a[i].value){
		if(a[i].key == key){
			a[i].value = value;
			return false;
		}
		++i;
		if (i == capacity()) {
			i = 0;
		}
	}
	a[i].key = key;
	a[i].value = value;
	mySize ++;
	return true;

}

//if there is an item matching key, removes the key/value-pair from the map, stores it's value in value, 
//and returns true; otherwise returns false.
//
bool HMOA::remove(int key, char& value){
	if(is_empty()){
		throw std::out_of_range("Empty map!");
	}

	if (!search(key, value)) return false;

	int i = hash(key);

	while(a[i].value && a[i].key!=key){
		++i;
		if (i == capacity()) {
			i = 0;
		}
		if (i == hash(key)) break;

	}

	while(a[i+1].value){
		a[i].key = a[i+1].key;
		a[i].value=a[i+1].value;
		++i;
	}

	a[i].key= 0;
	a[i].value='\0';
	mySize --;
	return true;

}

//if there is an item matching key, stores it's value in value, and returns true (the item remains in the map); 
//otherwise returns false.
bool HMOA::search(int key, char& value){
	if(is_empty()){
		throw std::out_of_range("Empty map!");
	}
	
	int i = hash(key);
	while(a[i].value && a[i].key!=key){
		++i;
		if (i == capacity()) {
			i = 0;
		}
		if (i == hash(key)) break;
	}

	if(!a[i].value){
		return false;
	}else{
		return true;
	}
}

//removes all items from the map.
void HMOA::clear(){
	int i = mapSize;

	while(i!=0){
		a[i].key = 0;
		a[i].value = '\0';
		--i;
	}

	mySize = 0;
}

//returns true IFF the map contains no elements.
bool HMOA::is_empty(){
	return (mySize==0)? true : false;
}

//returns the number of slots in the map.
std::size_t HMOA::capacity(){
	return mapSize;
}

//returns the number of items actually stored in the map.
std::size_t HMOA::size(){
	return mySize;
}

//returns the map's load factor (size = load * capacity).
double HMOA::load(){
	return (double)size()/(double) capacity();
}

//inserts into the ostream, the backing array's contents in sequential order. 
//Empty slots shall be denoted by a hyphen, non-empty slots by that item's key. 
//[This function will be used for debugging/monitoring].
std::ostream& HMOA::print( std::ostream& ostream ) const{
	if(mySize==0){
		throw std::out_of_range("Empty list!");
	}

	ostream << "[" ;

	for (int i =0; i < mapSize; ++i){
		if(!a[i].value){
			ostream << '-' << std::flush;
		}else{
			ostream << a[i].key << std::flush;
		}

		if (i!=mapSize-1){
			ostream << "|" ;
		}

	}
	
	ostream << "]" << std::endl;
	return ostream;

}

#endif
