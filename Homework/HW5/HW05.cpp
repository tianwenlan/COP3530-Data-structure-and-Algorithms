//Author: Wenlan Tian
//Date: Oct 16, 2014
//
//HW05: implement WinnerTree and LoserTree


#include <iostream>

template <class T>
class WinnerTree{
	private:
	T* first;
	int size;
	T elimiate;
	T[size];

	public:
	WinnerTree();
	T winner(); //returns the winning player
	void update_player(int, int);
	void eliminate_player(int);
	int size(); //returns the number of (non-eliminated) players
	bool empty(); //returns false IFF there are any (non-eliminated) players
	void pretty_print( ostream& ); //prints a textual representation of the tree following the examples below. 
};

template <class T>
class LoserTree{
	private:

	public:
	LoserTree();
	T winner(); //returns the winning player
	void update_winner( int new_score ); 
	void eliminate_winner();
	int size(); //returns the number of (non-eliminated) players
	bool empty(); //returns false IFF there are any (non-eliminated) players
	void pretty_print( ostream& ); //prints a textual representation of the tree following the examples below. 
};

//////////////////////////////////////WinnerTree//////////////////////////////

template <class T>
WinnerTree<T>::WinnerTree(){
}

//returns the winning player
template <class T>
T WinnerTree<T>::winner(){
	int p1, p2;
	return (T[p1] > T[p2] ? p1 : p2);
}

template <class T>
void WinnerTree<T>::update_player( int player, int new_score ){
	T[player] = new_score;
}

template <class T>
void WinnerTree<T>::eliminate_player( int player ){
}

//returns the number of (non-eliminated) players
template <class T>
int WinnerTree<T>::size(){ 
}

//returns false IFF there are any (non-eliminated) players
template <class T>
bool WinnerTree<T>::empty(){
}

//prints a textual representation of the tree following the examples below.
template <class T>
void WinnerTree<T>::pretty_print( ostream& ){
}



//////////////////////////////////////LoserTree//////////////////////////////
template <class T>
LoserTree<T>::LoserTree(){
}

//returns the winning player
template <class T>
T LoserTree<T>:: winner(){ 
	int p1, p2;
	return (T[p1] > T[p2] ? p1 : p2);
}

template <class T>
void LoserTree<T>::update_player( int player, int new_score ){
	T[player] = new_score;
}

template <class T>
void LoserTree<T>::eliminate_player( int player ){
}

//returns the number of (non-eliminated) players
template <class T>
int LoserTree<T>::size(){

}

//returns false IFF there are any (non-eliminated) players
template <class T>
bool LoserTree<T>::empty(){ 
}

//prints a textual representation of the tree following the examples below.
template <class T>
void LoserTree<T>::pretty_print( ostream& ){ 
}
