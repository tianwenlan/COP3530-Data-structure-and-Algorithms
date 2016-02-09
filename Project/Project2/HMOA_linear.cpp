//#ifndef _HMOA_H_
//#define _HMOA_H_

// Author: Wenlan Tian
// Project 2 for COP 3530
// Part III-1: Hash map with open addressing, linear probing
// Date: 11/14/2014
// Version 1

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const int mapSize = 10;

template <typename K, typename V>
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
		int hash(K,int);
		int hash(K);
		int probe(K,int);
		int insert (K, V);
		int remove (K, V&);
		int search (K, V&);
		void clear();
		bool is_empty();
		std::size_t capacity();
		std::size_t size();
		double load();
		std::ostream& print (std::ostream&) const;
		void cluster_distribution();
		K remove_random();
		int nrand(int n) {
			if(n<=0 || n > RAND_MAX)
				throw std::domain_error("nrand(n):n is not a valid value");
			const int bucket_size = RAND_MAX/n;
			int r;

			while (r>=n){
				r = rand()/bucket_size;
			}
			return r;
		}
};

template <typename K, typename V>
HMOA<K,V>::HMOA():mySize(0){
	for (int i =0; i < mapSize; ++i){
		a[i].key = K();
		a[i].value = V();
	}
}

template <typename K, typename V>
int HMOA<K,V>::hash(K key, int i){
	return hash(key) + i * probe(key,i);
}

template <typename K, typename V>
int HMOA<K,V>::hash(K key){
	return (int)key % mapSize;
}

template <typename K, typename V>
int HMOA<K,V>::probe(K key, int i){
	//linear probing
	return 1;

	//quadratic probing
//	return i;

	//rehashing
//	return hash2(key);
}


//if there is space available, adds the specified key/value-pair to the hash map and returns true; otherwise returns false. 
//If an item already exists in the map with the same key, replace its value.
template <typename K, typename V>
int HMOA<K,V>::insert(K key, V value){

	if(mySize == mapSize) return -1;

	int i = hash(key);

	int P =0;

	if(!a[i].value){
		a[i].key = key;
		a[i].value= value;
		mySize++;
		return P;
	}

		while(a[i].value){
			if(a[i].key == key){
				a[i].value = value;
				return P;
			}

			i += hash(key,i);
			++P;
			if (i >= capacity()) {
				i = i-capacity()-(capacity()-hash(key));
			}
			if(i == hash(key)) break;

		}

		a[i].key = key;
		a[i].value = value;
		mySize++;
		return P;
}

//if there is an item matching key, removes the key/value-pair from the map, stores it's value in value, 
//and returns true; otherwise returns false.
//
template <typename K, typename V>
int HMOA<K,V>::remove(K key, V& value){
	if(is_empty()){
		throw std::out_of_range("Empty map!");
	}

	if(search(key, value)<0) return search(key, value);

	int i = hash(key);
	int P =0;

	while(a[i].value && a[i].key!=key){
		i += hash(key,i);
		if (i >= capacity()) {
			i = i-capacity()-(capacity()-hash(key));
		}
		++P;
		if(i == hash(key)) break;
	}

	int j = i + hash(key,i);

	if (j >= capacity()) {
		j = j-capacity()-(capacity()-hash(key));
	}

	while(a[j].value){
		a[i].key = a[j].key;
		a[i].value=a[j].value;
		j = i + hash(key,i);
		if (j >= capacity()) {
			j = j-capacity()-(capacity()-hash(key));
		}
		i = j;
	}

	a[i].key = K();
	a[i].value = V();
	mySize --;
	return P;
}

//if there is an item matching key, stores it's value in value, and returns true (the item remains in the map); 
//otherwise returns false.
template <typename K, typename V>
int HMOA<K,V>::search(K key, V& value){
	if(is_empty()){
		throw std::out_of_range("Empty map!");
	}

	int i = hash(key);
	int P =0;

	if (a[i].value && a[i].key==key){
		a[i].value = value;
		return P;
	}

	while(a[i].value && a[i].key!=key){
		i += hash(key,i);
		if (i >= capacity()) {
			i = i-capacity()-(capacity()-hash(key));
		}
		++P;
		if (i == hash(key)) break;

	}

	if(!a[i].value){
		return -1*P;
	}else{
		a[i].value = value;
		return P;
	}
}

//removes all items from the map.
template <typename K, typename V>
void HMOA<K,V>::clear(){
	int i = mapSize;

	while(i!=0){
		a[i].key = K();
		a[i].value = V();
		--i;
	}

	mySize = 0;
}

//returns true IFF the map contains no elements.
template <typename K, typename V>
bool HMOA<K,V>::is_empty(){
	return (mySize==0)? true : false;
}

//returns the number of slots in the map.
template <typename K, typename V>
std::size_t HMOA<K,V>::capacity(){
	return mapSize;
}

//returns the number of items actually stored in the map.
template <typename K, typename V>
std::size_t HMOA<K,V>::size(){
	return mySize;
}

//returns the map's load factor (size = load * capacity).
template <typename K, typename V>
double HMOA<K,V>::load(){
	return (double)size()/(double) capacity();
}

//inserts into the ostream, the backing array's contents in sequential order. 
//Empty slots shall be denoted by a hyphen, non-empty slots by that item's key. 
//[This function will be used for debugging/monitoring].
template <typename K, typename V>
std::ostream& HMOA<K,V>::print( std::ostream& ostream ) const{
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

//returns list of cluster sizes and instances, sorted by cluster size; for example, a map's whose backing array is populated thusly
template <typename K, typename V>
void HMOA<K,V>::cluster_distribution(){

	if(is_empty()){
		throw std::out_of_range("Empty map!");
	}

	int count[mapSize];

	for (int k =0; k < mapSize;++k){
		count[k] = 0;
	}

	int i = 0;
	int j = 0;

	if(!a[i].value){
		while(!a[i].value){
			++i;
		}
	}

	while (i <= mapSize){
		int num = 0;
		while (a[i].value){
			++num;
			++i;
		}

		count[j] = num;
		++j;

		while(!a[i].value){
			++i;
		}

	}

	if (a[0].value && a[mapSize-1].value){
		count[0]=count[0]+count[j];
		j--;
	//	count[j]=0;
	}

	std::cout << "(" ;

	for (int m =0; m < j-1; ++m){
		if (count[m]!=0){
			int repeat = 1;
			for (int n = m+1; n < j; ++n){
				if (count[m]==count[n]){
					count[n]=0;
					repeat++;
				}else{
					continue;
				}
			}
			std::cout << "(" << count[m] <<"," << repeat << ")";
		}
	}
	
	std::cout << ")" << std::endl;
}


//generate a random number, R, (1,size), and starting with slot zero in the backing array, find the R-th occupied slot; remove the item from that slot (adjusting subsequent items as necessary), and return its key.
template <typename K, typename V>
K HMOA<K,V>::remove_random() {

	//generate the random number [1,mapSize)
	int R = nrand(size())+1;

	//remove the item in R-th slot (index R-1)
	K key_return = a[R-1].key;
	while(a[R].value){
		a[R-1].key=a[R].key;
		a[R-1].value = a[R].value;
		++R;
	}

	a[R-1].key = K();
	a[R-1].value=V();
	mySize --;
	return key_return;

}

int main(){

///////////////TEST <int, char> ///////////
	HMOA<unsigned int, char> hmoa;
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
