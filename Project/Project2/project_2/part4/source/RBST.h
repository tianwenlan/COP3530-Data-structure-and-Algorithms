#ifndef _RBST_H_
#define _RBST_H_


#include <iostream>
#include <stdexcept>
#include <string>
#include <queue>
#include <stack>
#include <cstdlib>

const int myCapacity = 50;

template <typename K, typename V>
class RBST{
	private:

		struct Node {
			K key;
			V value;
			int left;
			int right;

			Node():key(),value(),left(-1),right(-1){
			}

		};//end of struct

		int mySize;
		int root;
		int free;

		Node tree[50];

	public:
		RBST(int);
		int insert (K, V);
		int remove (K, V&);
		int search (K, V&);
		void clear();
		bool is_empty();
		std::size_t capacity();
		std::size_t size();
		double load();
		std::ostream& print (std::ostream&);
		void cluster_distribution();
		K remove_random(); 
		int insert_at_root(Node*, int, K, V);
		void rotate_right(Node*,int);
		void rotate_left(Node*,int);
		
		int nrand(int n){
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
RBST<K,V>::RBST(int capacity):mySize(0),root(-1),free(0){
	//allocate an array of capacity nodes
//	Node tree[50];

	for (int i =0; i< capacity -1; i++){
		tree[i].left = i+1;
	}
	tree[capacity-1].left = -1;

}

//if there is space available, adds the specified key/value-pair to the hash map and returns true; otherwise returns false. 
//If an item already exists in the map with the same key, replace its value.
template <typename K, typename V>
int RBST<K,V>::insert(K key, V value){


	//generate the random number [0,50)
//	int R = nrand(50);
	int R =30;
	//std::cout << R << std::endl;

	if(R==0){
 
		return insert_at_root(&tree[root],root,key,value);
	}

	//	insert_at_leaf(&tree[root],key,value);
		int num = 0;

		if(is_empty()){
			tree[0].key = key;
			tree[0].value = value;
			free = 1;
			root = 0;

			mySize++;
			num =1;
			return 1;
		}

		tree[free].key = key;
		tree[free].value = value;

		Node *temp = &tree[root];

		if(size()==1){

			if (key == temp->key){
				temp -> value = value;
			}else if (key < temp -> key){
				temp -> left = free;
				free++;
				mySize++;
			}else {
				temp -> right = free;
				free++;
				mySize++;
			}
			num =2;
		}else{

			while((key < temp->key && temp->left!=free)|| (key > temp->key&&temp->right != free)){
				if(key == temp->key){
					temp->value = value;
					return num;
				}else if(key < temp->key){
					temp = &tree[temp->left];
				}else{
					temp = &tree[temp -> right];
				}
				num++;
			}

			if (key < temp -> key){
				temp -> left = free;
				free++;
				mySize++;
			}else{
				temp -> right = free;
				free++;
				mySize++;
			}
		}
		return num;
    
}

template <typename K, typename V>
int RBST<K,V>::insert_at_root(Node* current_root, int index, K key,V value){
	int num = 0;
	if(mySize==0){
		tree[0].key = key;
		tree[0].value = value;
		free++;
		mySize++;
		return 1;
	}

	num++;

	if (key == current_root->key){
		current_root->value = value;
		return num;
	}else if (key < current_root->key){
		insert_at_root(&tree[current_root->left], index, key, value);
		rotate_right(current_root,index);
		mySize ++;
		free++;
	}else{
		insert_at_root(&tree[current_root->right], index, key, value);
		rotate_left(current_root,index);
		mySize ++;
		free++;
	}
	return num;
}

template <typename K, typename V>
void RBST<K,V>::rotate_right(Node* current_root, int index){
	Node* q = &tree[current_root->left];
	if(!q) return;
    current_root->left = q->right; 
	q->right = index;
	current_root = q;
}

template <typename K, typename V>
void RBST<K,V>::rotate_left(Node* current_root, int index){
	Node* q = &tree[current_root->right];
	if(!q ) return;
    current_root->right = q->left; 
	q->left = index;
	current_root = q;
}


//if there is an item matching key, removes the key/value-pair from the tree, stores it's value in value, and returns the number of probes required, V; otherwise returns -1 * V.

template <typename K, typename V>
int RBST<K,V>::remove(K key, V& value){
	if(is_empty()){
			throw std::out_of_range("Empty list!");
	}

	if (search(key, value)<0) return -1*size();

	Node *temp = &tree[root];

	if(size() ==1){
		root = -1;
		temp[0].right = -1;
		temp[0].left = 1;
		free = 0;
		mySize --;
		return 1;
	}else{
		int num = 0;

		while((key < temp->key && temp->left!=free)|| (key > temp->key&&temp->right != free)){
			num++;
			if(key == temp->key){
				//node has no child
				if(temp->left == -1 && temp->right == -1){
				
				//node has one child
				}else if(temp->left == -1 || temp->right == -1){

				//node has two children
				}else{

				}
			}else if(key < temp->key){
				temp = &tree[temp->left];
			}else{
				temp = &tree[temp -> right];
			}
		}

		mySize--;
		return -1* num;

	}
}


//if there is an item matching key, stores it's value in value, and returns true (the item remains in the map); 
//otherwise returns false.
template <typename K, typename V>
int RBST<K,V>::search(K key, V& value){
		int num =0;

		if(is_empty()){
			throw std::out_of_range("Empty list!");
		}

		std::queue<Node*> q;
		q.push(&tree[root]);

		while(!q.empty()){
			Node* n = q.front();
			q.pop();
			if(n->key== key){
				n->value = value;
				return num;
			}
			num++;

			if(n->left!=free) q.push(&tree[n->left]);
			if(n->right!=-1) q.push(&tree[n->right]);
		}
		
		return -1*num;
}

//removes all items from the map.
template <typename K, typename V>
void RBST<K,V>::clear(){
	for (int i =0; i< myCapacity -1; i++){
		tree[i].left = i+1;
		tree[i].key = K();
		tree[i].value = V();
		tree[i].right = -1;
	}
	tree[myCapacity-1].left = -1;
	tree[myCapacity-1].left = -1;
	tree[myCapacity-1].key = K();
	tree[myCapacity-1].value = V();
	root = -1;
	free = 0;
	mySize = 0;
}

//returns true IFF the map contains no elements.
template <typename K, typename V>
bool RBST<K,V>::is_empty(){
	return (mySize==0)? true : false;
}

//returns the number of slots in the map.
template <typename K, typename V>
std::size_t RBST<K,V>::capacity(){
	return myCapacity;
}

//returns the number of items actually stored in the map.
template <typename K, typename V>
std::size_t RBST<K,V>::size(){
	return mySize;
}

//returns the map's load factor (size = load * capacity).
template <typename K, typename V>
double RBST<K,V>::load(){
	return (double)size()/(double) capacity();
}


//inserts into the ostream, the backing array's contents in sequential order. 
//Empty slots shall be denoted by a hyphen, non-empty slots by that item's key. 
//[This function will be used for debugging/monitoring].
template <typename K, typename V>
std::ostream& RBST<K,V>::print( std::ostream& ostream ){

	if(root==-1){
		ostream << "empty tree!" << std::endl;
	}

	if(root!=-1){
		std::queue<Node*> q;
		q.push(&tree[root]);

		while(!q.empty()){
			Node* n = q.front();
			q.pop();
			if(n->key!=0){
				ostream << n->key << " ";
			}

			if(n->left!=free) q.push(&tree[n->left]);
			if(n->right!=-1) q.push(&tree[n->right]);
		}
	}
	return ostream;
}



//returns list of cluster sizes and instances, sorted by cluster size; for example, a map's whose backing array is populated thusly
template <typename K, typename V>
void RBST<K,V>::cluster_distribution(){
	if(is_empty()){
		throw std::out_of_range("Empty map!");
	}



	int count[myCapacity];

	for (int k =0; k < myCapacity;++k){
		count[k] = 0;
	}

	int i = 0;
	int j = 0;

	if(!tree[i].value){
		while(!tree[i].value){
			++i;
		}
	}

	if(root!=-1){
		std::queue<Node*> q;
		q.push(&tree[root]);

		while(!q.empty()){
			int num = 0;
			Node* n = q.front();
			q.pop();
			if(n->key!=0){
				 num ++;
			}

			if(n->left!=free) q.push(&tree[n->left]);
			if(n->right!=-1) q.push(&tree[n->right]);
		}
	}

}


//generate a random number, R, (1,size), and starting with slot zero in the backing array, find the R-th occupied slot; remove the item from that slot (adjusting subsequent items as necessary), and return its key.
template <typename K, typename V>
K RBST<K,V>::remove_random() {

	int R = nrand(size())+1;

	//remove the item in R-th slot (index R-1)
	Node* current = &tree[root];
	std::stack<Node*> s;
	bool done = false;

	while(!done){
		if(current!=NULL){
			s.push(current);
			current = current -> left;
		}else{
			if(!s.empty()){
				current = s.pop();
				remove(current);
				current = current -> right;
			}else{
				done = true;
			}
		}
	}

	mySize --;
	return ;
}

#endif
