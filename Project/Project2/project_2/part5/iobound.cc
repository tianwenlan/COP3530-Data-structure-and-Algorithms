#include <sys/resource.h>
#include <iostream>
#include <fstream>

using namespace std;

void readfile(string filename){
        fstream in(filename.data());
        string item;
        while (!in.eof()) {
                item = "";
                in >> item;
        }
        in.close();
}

int main(void){
        int *c = new int;
        for (int i=0; i<1000000; i++){
                readfile("iobound.cc");
        }
        struct rusage r;
        struct timeval utime, stime;
        getrusage(0, &r);
        utime = r.ru_utime;
        stime = r.ru_stime;
        cout << "User time: " << utime.tv_sec + 1.0*utime.tv_usec/1000000 << " seconds" << endl;
        cout << "System time: " << stime.tv_sec + 1.0*stime.tv_usec/1000000 << " seconds" << endl;
}

//OUTPUT
//User time: 21.0668 seconds
//System time: 4.97824 seconds