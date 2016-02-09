#include <sys/resource.h>
#include <iostream>

using namespace std;

int main(void){
        int *c = new int;
        for (int i=0; i<100000000; i++){
                *c = i;
                delete c;
                c = new int;
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
//User time: 5.18821 seconds
//System time: 0.000999 seconds