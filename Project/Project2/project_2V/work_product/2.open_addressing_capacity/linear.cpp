// Author: Wenlan Tian
// Project 2 for COP 3530
// Part V: 2. Hash map with open addressing, linear probing
// Date: 12/04/2014
// Version 1

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <fstream>

#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8) +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

int mapSize = 0;

class HMOA{
	private:
		struct item{
			std::string key;
			int value;
		};

		item a[mapSize];
		int mySize;
	public:
		HMOA();
		int hash(std::string,int);
		std::size_t hash(std::string const&);
		int probe(std::string,int);
		int insert (std::string, int);
		int remove (std::string, int&);
		int search (std::string, int&);
		void clear();
		bool is_empty();
		std::size_t capacity();
		std::size_t size();
		double load();
		std::ostream& print (std::ostream&) const;
		std::string remove_random();
		void readfile(std::string);
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

HMOA::HMOA():mySize(0){
	for (int i =0; i < mapSize; ++i){
		a[i].value = 0;
	}
}

int HMOA::hash(std::string key, int i){
	return hash(key) + i * probe(key,i);
}

std::size_t HMOA::hash( std::string const& s ) {
  const char * data = s.c_str();
  int len = s.length();
  uint32_t hash = len, tmp;
  int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= data[sizeof (uint16_t)] << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += *data;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return std::size_t( hash );
}



int HMOA::probe(std::string key, int i){
	//linear probing
	return 1;

}

//if there is space available, adds the specified key/value-pair to the hash map and returns true; otherwise returns false. 
//If an item already exists in the map with the same key, replace its value.
int HMOA::insert(std::string key, int value){

	if(mySize == mapSize) return -1;

	int i = hash(key)%capacity();

	int P =0;

	if(!a[i].value){
		a[i].key = key;
		a[i].value= value;
		mySize++;
		return P;
	}else{

		while(a[i].value){
			P++;
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
		mySize++;
		return P;
	}
}

//if there is an item matching key, removes the key/value-pair from the map, stores it's value in value, 
//and returns true; otherwise returns false.
//
int HMOA::remove(std::string key, int& value){
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

	a[i].key =  (std::string)NULL;
	a[i].value = 0;
	mySize --;
	return P;
}

//if there is an item matching key, stores it's value in value, and returns true (the item remains in the map); 
//otherwise returns false.
int HMOA::search(std::string key, int& value){
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
void HMOA::clear(){
	int i = mapSize;

	while(i!=0){
		a[i].key =(std::string)NULL;
		a[i].value = 0;
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

void HMOA::readfile(std::string fileName){
	std::fstream in(fileName.data());
	std::ifstream inStream;
	std::string tempString;

	inStream.open(fileName.c_str(), std::ifstream::in); 

	if(!inStream.is_open()) {
		std::cout << "File " << fileName << " cannot be opened!" << std::endl;
	    return;
    }

	int i = 0;

	while(inStream >> tempString){
		++i;
		insert(tempString, i);
	}

	in.close();
}

std::string HMOA::remove_random() {

	//generate the random number [1,mapSize)
	int R = nrand(size())+1;

	//remove the item in R-th slot (index R-1)
	std::string key_return = a[R-1].key;
	while(a[R].value){
		a[R-1].key=a[R].key;
		a[R-1].value = a[R].value;
		++R;
	}

	a[R-1].key = (std::string)NULL;
	a[R-1].value=0;
	mySize --;
	return key_return;

}


int closePrime(int n){
	std::string fileName = "prime.txt";
	std::fstream in(fileName.data());
	std::ifstream inStream;
	int temp;

	inStream.open(fileName.c_str(), std::ifstream::in); 

	if(!inStream.is_open()) {
		std::cout << "File " << fileName << " cannot be opened!" << std::endl;
	    return 0;
    }

	int i = 0;

	while(inStream >> temp){

		if (temp > n){
			return temp;
		}
	}

	in.close();

	return 0;
}


int main(){

	HMOA hmoa;

	std::string data_sets[5]={"aeneid","war_peace","UID","coords","entries"};

	std::string data_aeneid[7] = {"aeneid_vergil-unique.txt","avu-1.txt","avu-2.txt","avu-3.txt","avu-4.txt","avu-5.txt","aeneid_vergil.txt"};

	std::string data_war_peace[7] = {"war-and-peace_tolstoi-unique.txt","wtu-1.txt","wtu-2.txt","wtu-3.txt","wtu-4.txt","wtu-5.txt","war-and-peace_tolstoi.txt"};

	std::string data_UID[7] = {"localities-uid-unique.txt","uid-1.txt","uid-2.txt","uid-3.txt","uid-4.txt","uid-5.txt","localities-uid.txt"};

	std::string data_coords[7] = {"localities-coords-unique.txt","coords-1.txt","coords-2.txt","coords-3.txt","coords-4.txt","coords-5.txt","localities-coords.txt"};

	std::string data_entries[8] = {"localities-coords.txt","localities-country.txt","localities-location.txt","localities-original.txt","localities-population.txt","localities-uid.txt","original-1.txt","original-2.txt"};

	int capacity_avu[5] = {4983, 0, 8192, 8191, 6151};
	int capacity_wp[5] = {2028, 0, 2048, 2039, 1543};
	int capacity_uid[5] = {10555, 0, 16384, 16381, 12289};
	int capacity_coords[5] = {10550, 0, 16384, 16381, 12289};
	int capacity_entries[5] = {10555, 0, 16384, 16381, 12289};

	std::ofstream output;
	std::string outFileName = "linear.txt";

	output.open(outFileName.c_str()); 
	if (output.fail()){
		std::cerr << "Output file cannot be opened" << std::endl;
		return 1;
	}


	//for different a
	for (double i = 0; i <1.05; i+=0.05){
		capacity_avu[0]= 4983+4983*i;
		capacity_avu[1]=closePrime(capacity_avu[0]);

		capacity_wp[0]= 4983+4983*i;
		capacity_wp[1]=closePrime(capacity_wp[0]);

		capacity_uid[0]= 4983+4983*i;
		capacity_uid[1]=closePrime(capacity_uid[0]);

		capacity_coords[0]= 4983+4983*i;
		capacity_coords[1]=closePrime(capacity_coords[0]);

		capacity_entries[0]= 4983+4983*i;
		capacity_entries[1]=closePrime(capacity_entries[0]);

		double load_factor = 0;

		//for each load factor from 0.03 to 0.99 by 0.03
		for (double j = 0.03; j < 0.09; j+=0.03){ 		
			load_factor = j;

			//for each set of data sets  [e.g., The Aeneid set of data sets]
			for (int k = 0; k < 5;++k){
				int mySize = 0;

				if (k==4){
					mySize = 8;
				}else{
					mySize = 7;
				}

				std::string current_data[8];
				int current_capacity[5];

				if (data_sets[k]=="aeneid"){
					for(int m =0; m < 7; ++m){
						current_data[m]=data_aeneid[m];
					}
					for(int m =0; m < 5; ++m){
						current_capacity[m]=capacity_avu[m];
					}
				}else if (data_sets[k]=="war_peace"){
					for(int m =0; m < 7; ++m){
						current_data[m]=data_war_peace[m];
					}
					for(int m =0; m < 5; ++m){
						current_capacity[m]=capacity_wp[m];
					}

				}else if (data_sets[k]=="UID"){
					for(int m =0; m < 7; ++m){
						current_data[m]=data_UID[m];
					}
					for(int m =0; m < 5; ++m){
						current_capacity[m]=capacity_uid[m];
					}

				}else if (data_sets[k]=="coords"){
					for(int m =0; m < 7; ++m){
						current_data[m]=data_coords[m];
					}

					for(int m =0; m < 5; ++m){
						current_capacity[m]=capacity_coords[m];
					}

				}else if (data_sets[k]=="entries"){
					for(int m =0; m < 8; ++m){
						current_data[m]=data_entries[m];
					}

					for(int m =0; m < 5; ++m){
						current_capacity[m]=capacity_entries[m];
					}

				}

				//for each data set in that set of data sets
				for (int l =0; l<mySize; ++l){

					std::string fileName = current_data[l];

					std::fstream in(fileName.data());
					std::ifstream inStream;
					std::string tempString;

					inStream.open(fileName.c_str(), std::ifstream::in); 

					if(!inStream.is_open()) {
						std::cout << "File " << fileName << " cannot be opened!" << std::endl;
						return 1;
					 }

					int o = 0;
	
					while(inStream >> tempString){
						++o;
						while (hmoa.load()  < load_factor){
							hmoa.insert(tempString, i);
						}
						
						hmoa.remove_random();
						hmoa.insert(tempString, o);
					}

					in.close();

					
					for (int n = 0; n < mySize; ++n){
						if(n == l or n == mySize-1) continue;

						std::string fileName1 = current_data[n];

						std::fstream in(fileName1.data());
						std::ifstream inStream1;
						std::string tempString1;

						int p = 0;
						int success = 0;
						int failure = 0;
						int search_result = 0;

						while(inStream1 >> tempString1){
							++p;
							search_result = hmoa.search(tempString1, p);

							if (search_result > 0){
								++success;
							}else {
								++failure;
							}
							
						}
						in.close();
	
						output << "capacity" << std::endl;
						output << "table size: " << std::endl;
						output << "number of items in trial data set: " << o << std::endl;
						output << "number of items in unique data set: " << p << std::endl;
						output << "insert probe count distribution: " << std::endl;
						output << "search success probe count distribution: " << success << std::endl;
						output << "search failure probe count distribution: " << failure  << std::endl;

					}


				}
				
			}


		}

	}

	return 0;
}
