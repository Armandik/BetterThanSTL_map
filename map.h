#pragma once
#include <iostream>

template<class T1, class T2>
struct pair {

	T1 first;
	T2 second;
};

template<class T>
class node {

private:

	pair<int, T> _values;

public:

	node* left;
	node* right;
	int height;

	node(int key, T value);

	// Getters
	int key() { return _values.first; }
	T value() { return _values.second; }

	// Setters
	void setKey(int key) { _values.first = key; }
	void setValue(T value) { _values.second = value; }
};

template<class T>
class map {

private:

	node<T>* _root;
	int _size;


	node<T>* rotation_right(node<T>* head);
	node<T>* rotation_left(node<T>* head);
	node<T>* rotation_rightleft(node<T>* head);
	node<T>* rotation_leftright(node<T>* head);
	node<T>* recursiveInsert(node<T>* head, int key, T value);
	node<T>* recursiveErase(node<T>* head, int key);
	void recursiveClear(node<T>* head);
	int balanceFactor(node<T>* head);

public:

	map();
	~map();

	int size() { return _size; }
	int height(node<T>* head);
	node<T>* search(int key);
	void insert(int key, T value);
	void printTree(node<T>* head);
	void erase(int key);
	void clear();

	// Getters
	node<T>* root() { return _root; }

};



// NODE FUNCTIONS
template<class T>
inline node<T>::node(int key, T value) {

	_values.first = key;
	_values.second = value;

	left = 0;
	right = 0;

	height = 0;
}

// MAP FUNCTIONS
template<class T>
map<T>::map() {

	_root = 0;
	_size = 0;

}

template<class T>
map<T>::~map() {

	clear();

}

template<class T>// Returns the node that contains the specified key
node<T>* map<T>::search(int key) {

	node<T>* v = _root;

	while (v != 0) {

		if (key == v->key())
			return v;
		else if (key < v->key())
			v = v->left;
		else v = v->right;
	}

	return 0;
}

template<class T>// recursively searches the location where it will create a new node and rebalances the tree
node<T>* map<T>::recursiveInsert(node<T>* head, int key, T value) {

	// Create the new node if head is not a node
	if (head == 0) {

		_size++;
		node<T>* tmp = new node<T>(key, value);
		return tmp;
	}

	// Recursively search for the location where the new node will be placed
	if (key < head->key()) 
		head->left = recursiveInsert(head->left, key, value);
	else if (key > head->key())
		head->right = recursiveInsert(head->right, key, value);

	// Update height
	head->height = 1 + std::max(height(head->left), height(head->right));
	
	// Balance tree through rotations
	int bal = balanceFactor(head);
	if (bal > 1) { // unbalanced left subtree
		if (key < head->left->key())
			return rotation_right(head);
		else
			return rotation_leftright(head);
	}
	else if (bal < -1) { // unbalanced right subtree
		if (key > head->right->key()) {
			return rotation_left(head);
		}
		else
			return rotation_rightleft(head);
	}
	
	return head;

}

template<class T>// recursively searches for a node to delete and then rebalances the tree
node<T>* map<T>::recursiveErase(node<T>* head, int key){

	if (head == 0)
		return 0;

	if (key < head->key())
		head->left = recursiveErase(head->left, key);
	else if (key > head->key())
		head->right = recursiveErase(head->right, key);
	else {
		node<T>* r = head->right;

		if (head->right == 0) {
			node<T>* l = head->left;
			delete head;
			head = l;
		}
		else if (head->left == 0) {
			delete head;
			head = r;
		}
		else {
			while (r->left != 0)
				r = r->left;

			head->setKey(r->key());
			head->setValue(r->value());
			head->right = recursiveErase(head->right, r->key());
		}
	}
	if (head == 0)
		return head;

	// Update height
	head->height = 1 + std::max(height(head->left), height(head->right));

	// Balance tree through rotations
	int bal = balanceFactor(head);
	if (bal > 1) { // unbalanced left subtree
		if (height(head->left) > height(head->right))
			return rotation_right(head);
		else
			return rotation_leftright(head);
	}
	else if (bal < -1) { // unbalanced right subtree
		if (height(head->right) >height(head->left))
			return rotation_left(head);
		else
			return rotation_rightleft(head);
	}

	return head;

}

template<class T>// recursively clears the subtree starting from an input node
void map<T>::recursiveClear(node<T>* head){

	if (head != 0) {
		recursiveClear(head->left);
		recursiveClear(head->right);
		delete head;
		_size--;
	}

}

template<class T>// Insertion of a node
void map<T>::insert(int key, T value) {

	_root = recursiveInsert(_root, key, value);
}

template<class T>// In order print of the tree
void map<T>::printTree(node<T>* head) {

	if (head == 0)
		return;

	printTree(head->left);
	std::cout << head->value() /*<< ", height:" << height(head) << ", balance " << balanceFactor(head)*/ << "\n";
	printTree(head->right);
}

template<class T>// Erases node with the right key
void map<T>::erase(int key){

	_root = recursiveErase(_root, key);
}

template<class T>
void map<T>::clear(){

	recursiveClear(_root);
	_root = 0;

}


template<class T>// Right rotation for balancing
node<T>* map<T>::rotation_right(node<T>* head){

	node<T>* tmp = head->left;
	head->left = tmp->right;
	tmp->right = head;

	// Height adjustments
	head->height = 1 + std::max(height(head->left), height(head->right));
	tmp->height = 1 + std::max(height(tmp->left), height(tmp->right));

	return tmp;

}

template<class T>// Left rotation for balancing
node<T>* map<T>::rotation_left(node<T>* head){

	node<T>* tmp = head->right;
	head->right = tmp->left;
	tmp->left = head;

	// Height adjustments
	head->height = 1 + std::max(height(head->left), height(head->right));
	tmp->height = 1 + std::max(height(tmp->left), height(tmp->right));

	return tmp;

}

template<class T>// Right + Left rotation for balancing
node<T>* map<T>::rotation_rightleft(node<T>* head){

	node<T>* tmp = head->right;
	head->right = rotation_right(tmp);
	return rotation_left(head);

}

template<class T>// Left + Right rotation for balancing
node<T>* map<T>::rotation_leftright(node<T>* head){

	node<T>* tmp = head->left;
	head->left = rotation_left(tmp);
	return rotation_right(head);

}

template<class T>// Returns height of the node
int map<T>::height(node<T>* head) {

	if (head == 0)
		return -1;
	else
		return head->height;
}

template<class T>// Returns balance factor of the node
int map<T>::balanceFactor(node<T>* head) {

	if (head == 0)
		return 0;
	else
		return(height(head->left) - height(head->right));
}