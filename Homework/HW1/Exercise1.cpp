#include <string>
#include <iostream>
using namespace std;

const int maxSize = 5;

template <class T> 
class Queue{
	private:
		int head;
		int tail;
		int n;
		T array[maxSize];
		
	public:
		Queue();
		int size();
		bool isEmpty();
		bool full();
		void enqueue(T&);
		void dequeue(T&);
		void print();
};

template <class T> 
Queue<T>::Queue(){
	head = -1;
	tail = -1;
	n =0;
}

template <class T> 
bool Queue<T>::isEmpty(){
	if (head == -1 && tail ==-1){
		cerr << "Current queue is empty!" << endl;
		return true;
	}else{
		return false;
	}
}

template <class T> 
bool Queue<T>::full(){
	if ((head == 0 && tail+1 == maxSize) || head - tail == 1){
		cerr << "Current queue is full!" << endl;
		return true;
	}else{
		return false;
	}
}

template <class T> 
int Queue<T>::size(){
	if(head<=tail){
		n = tail-head+1;
		cout << "Current size: " << n << endl;
		return n;
	}else{
		n = maxSize-(head-tail-1);
		cout << "Current size: " << n << endl;
		return n;
	}
}

template <class T> 
void Queue<T>::enqueue(T& item){
	cout << "Please enter the item to the enqueued: " << flush;
	cin >> item;
	//check if the queue is full
	//if full
	if(full()){
		return;
	}else if (tail +1 < maxSize){
		array[tail+1]=item;
		tail++;
	}else if (tail + 1 == maxSize){
		tail = 0;
		array[tail]=item;
	}else if(head == -1){
		head =0;
	}
}

template <class T> 
void Queue<T>::dequeue(T& item){
	//if empty
	if(isEmpty()){
		return;
	}else if (head == tail){
		head = -1;
		tail = -1;
	}else if (head+1 < maxSize){
		head++;
	}else if (head+1 == maxSize){
		head = 0;
	}
}

template <class T> 
void Queue<T>::print(){
	if(isEmpty()){
		return;
	}else if(head <= tail){
		for (int i = head; i<=tail; ++i){
			cout << array[i] << " " << flush;
		}
		cout << endl;
	}else if(tail < head){
		for (int i = head; i!=maxSize; ++i){
			cout << array[i] << " " << flush; 
		}
		for (int i = 0; i<=tail; ++i){
			cout << array[i] << " " << flush;
		}
		cout << endl;
	}
}

void menu(){
	cout << "0=exit, 1=enqueue, 2=dequeue, 3=size, 4=full, 5=empty, 6==print, 7==help" << endl;
}

template <class T> 
void workOnQueue(T& typeHolder, string &tName){
	int num =0;
	Queue<T> myQueue;
	T item;

	menu();

	while(1){
		cout << ">" << flush;
		cin >> num;

		if(cin.good()){
			switch(num){
				case 0: //eixt
					return;
				case 1: //enqueue
					myQueue.enqueue(item);
					break;
				case 2: //dequeue
					myQueue.dequeue(item);
					break;
				case 3: //size
					myQueue.size();
					break;
				case 4: //is full
					myQueue.full();
					break;
				case 5: //is empty
					myQueue.isEmpty();
					break;
				case 6: //print
					myQueue.print();
					break;
				case 7: //help
					menu();
					break;
			}
		}
	}
}

int main(){

	while (1) {
	cout << "Please choose the type you want to input (0-quit, 1-ints, 2-chars, 3-string)" << endl;
	cout << ">" << flush;

	int inputType=0;

	cin >> inputType;

		if (cin.good()){
			switch (inputType){
				case 0:
					cout << "bye bye" << endl;
					return 0;
				case 1:
					{
					int indicator;
					string s("Integer ");
					workOnQueue(indicator, s);
					break;
					}
				case 2:
					{
					char indicator;
					string s("Characters ");
					workOnQueue(indicator, s);
					break;
					}
				case 3:
					{
					string indicator;
					string s("String ");
					workOnQueue(indicator, s);
					break;
					}
			}
		}
	}

	return 0;
}


