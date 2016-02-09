#include <sys/resource.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

//////////////////hash functions////////////////

int capacity = 0;

std::size_t hash( std::string const& s ) {
  char const* data = s.c_str();
  std::size_t hash;
  std::size_t a = 31415U;
  std::size_t b = 27183U;

  for ( hash = 0; *data != 0; ++data, a = a * b % 25165843U )
    hash = a * hash + *data;
  
  return hash;
}

void readfile(std::string fileName){
	std::fstream in(fileName.data());
	std::string item;
	std::ifstream inStream;
	std::string tempString;

	inStream.open(fileName.c_str(), std::ifstream::in); 

	if(!inStream.is_open()) {
		std::cout << "File " << fileName << " cannot be opened!" << std::endl;
	    return;
    }

    while (inStream >> tempString) {
        int index = hash(tempString) % capacity;
     }
    in.close();
}


int main(){

	int capacity_avu[13] = {5245, 229, 751, 5261, 256, 1024, 8192, 251, 1021, 8191, 193, 769, 6151};
	int capacity_cau[13] = {1788, 79, 257, 1789, 128, 256, 2048, 127, 251, 2039, 97, 193, 1543};
	int capacity_dcdu[13] = {2947, 131, 431, 2953, 256, 512, 4096, 251, 509, 4093, 193, 389, 3079};
	int capacity_odu[13] = {2334, 103, 337, 2339, 128, 512, 4096, 127, 509, 4093, 193, 389, 3079};
	int capacity_wtu[13] = {2135, 97, 307, 2137, 128, 512, 4096, 127, 509, 4093, 97, 389, 3079};
	int capacity_localities[13] = {11111, 487, 1597, 11113, 512, 2048, 16384, 509, 2039, 16381, 389, 1543, 12289};

	std::string fileName[10] = {"aeneid_vergil-unique.txt","confucian-analects-unique.txt", "divine-comedy_dante-unique.txt", 
		"origin-of-the-species_darwin-unique.txt", "war-and-peace_tolstoi-unique.txt", 
		"localities-uid.txt", "localities-population.txt", "localities-location.txt","localities-coords.txt", "localities-original.txt"};

	int num_key[10] = {capacity_avu[0], capacity_cau[0], capacity_dcdu[0], capacity_odu[0],capacity_wtu[0], 
		capacity_localities[0],capacity_localities[0],capacity_localities[0],capacity_localities[0],capacity_localities[0]};

	// print to file
	std::ofstream output;
	std::string outFileName = "hash_string_3.txt";

	output.open(outFileName.c_str()); 
	if (output.fail()){
		std::cerr << "File " << outFileName << " cannot be opened" << std::endl;
		return 1;
	}

		for(int i = 0; i < 10; i++){

			output << "========== Data: " << fileName[i] << " ========="<< std::endl;

			int current_capacity[13];

			if (fileName[i]=="aeneid_vergil-unique.txt"){
				for (int m = 0; m < 13; ++m){
					current_capacity[m] =  capacity_avu[m]; 
				}
			}else if(fileName[i]=="confucian-analects-unique.txt"){
				for (int m = 0; m < 13; ++m){
					current_capacity[m] =  capacity_cau[m]; 
				}
			}else if(fileName[i]=="divine-comedy_dante-unique.txt"){
				for (int m = 0; m < 13; ++m){
					current_capacity[m] =  capacity_dcdu[m]; 
				}
			}else if(fileName[i]=="origin-of-the-species_darwin-unique.txt"){
				for (int m = 0; m < 13; ++m){
					current_capacity[m] =  capacity_odu[m]; 
				}
			}else if(fileName[i]=="war-and-peace_tolstoi-unique.txt"){
				for (int m = 0; m < 13; ++m){
					current_capacity[m] =  capacity_wtu[m]; 
				} 
			}else {
				for (int m = 0; m < 13; ++m){
					current_capacity[m] =  capacity_localities[m]; 
				}
			}

			capacity = current_capacity[0];

			int *c = new int;
			
			for (int k =0; k< 100000; ++k){
				readfile(fileName[i]);
			}
		
			struct rusage r;
			struct timeval utime, stime;
			float mean_utime, mean_stime, total_utime, total_stime;
			getrusage(0, &r);
			utime = r.ru_utime;
			stime = r.ru_stime;

			total_utime = utime.tv_sec + 1.0*utime.tv_usec/1000000;
			total_stime = stime.tv_sec + 1.0*stime.tv_usec/1000000;

			mean_utime = (utime.tv_sec + 1.0*utime.tv_usec/1000000)/num_key[i]/100000;
			mean_stime = (stime.tv_sec + 1.0*stime.tv_usec/1000000)/num_key[i]/100000;

			output << "User time: " << total_utime << " seconds" << std::endl;
			output << "System time: " << total_stime << " seconds" << std::endl;
			output  << "Mean user time: " << mean_utime << " seconds" << std::endl;
			output  << "Mean system time: " << mean_stime << " seconds" << std::endl;
			

	/*

	for(int i = 0; i < 10; i++){
		output << "========== Data: " << fileName[i] << " ========="<< std::endl;
		int current_capacity[13];

		if (fileName[i]=="aeneid_vergil-unique.txt"){
			for (int m = 0; m < 13; ++m){
				current_capacity[m] =  capacity_avu[m]; 
			}
		}else if(fileName[i]=="confucian-analects-unique.txt"){
			for (int m = 0; m < 13; ++m){
				current_capacity[m] =  capacity_cau[m]; 
			}
		}else if(fileName[i]=="divine-comedy_dante-unique.txt"){
			for (int m = 0; m < 13; ++m){
				current_capacity[m] =  capacity_dcdu[m]; 
			}
		}else if(fileName[i]=="origin-of-the-species_darwin-unique.txt"){
			for (int m = 0; m < 13; ++m){
				current_capacity[m] =  capacity_odu[m]; 
			}
		}else if(fileName[i]=="war-and-peace_tolstoi-unique.txt"){
			for (int m = 0; m < 13; ++m){
				current_capacity[m] =  capacity_wtu[m]; 
			} 
		}else {
			for (int m = 0; m < 13; ++m){
				current_capacity[m] =  capacity_localities[m]; 
			}
		}
		
		for (int j = 0; j < 13; j++){
			output << "--- Capacity = " << current_capacity[j] << " ---" << std::endl;
		//	capacity = current_capacity[j];

			int *c = new int;
			
			for (int k =0; k< 10000; ++k){
				readfile(fileName[i]);
			}
		
			struct rusage r;
			struct timeval utime, stime;
			int mean_utime, mean_stime, total_utime, total_stime;
			getrusage(0, &r);
			utime = r.ru_utime;
			stime = r.ru_stime;

			total_utime = utime.tv_sec + 1.0*utime.tv_usec/1000000;
			total_stime = stime.tv_sec + 1.0*stime.tv_usec/1000000;

			mean_utime = (utime.tv_sec + 1.0*utime.tv_usec/1000000)/num_key[i]/10000;
			mean_stime = (stime.tv_sec + 1.0*stime.tv_usec/1000000)/num_key[i]/10000;

			output << "User time: " << total_utime << " seconds" << std::endl;
			output << "System time: " << total_stime << " seconds" << std::endl;
			output  << "Mean user time: " << mean_utime << " seconds" << std::endl;
			output  << "Mean system time: " << mean_stime << " seconds" << std::endl;
			
		}


*/

	}

	return 0;

}

