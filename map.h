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
	~node();

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
	int balanceFactor(node<T>* head);

public:

	map();
	~map();

	int size() { return _size; }
	int height(node<T>* head);
	node<T>* search(int key);
	void insert(int key, T value);
	void printTree(node<T>* head);
	void erase(node<T>* head);
	void erase(int key) { erase(search(key)); }

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

template<class T>
node<T>::~node() {

	if (left)
		delete left;

	if (right)
		delete right;
}


// MAP FUNCTIONS
template<class T>
map<T>::map() {

	_root = 0;
	_size = 0;

}

template<class T>
map<T>::~map() {



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

template<class T>
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

template<class T>// Insertion of a node
void map<T>::insert(int key, T value) {

	_root = recursiveInsert(_root, key, value);
}

template<class T>// In order print of the tree
void map<T>::printTree(node<T>* head) {

	if (head == 0)
		return;

	printTree(head->left);
	std::cout << head->value() << ", height:" << height(head) << ", balance " << balanceFactor(head)<< "\n";
	printTree(head->right);
}

template<class T>// Erase node
void map<T>::erase(node<T>* head){



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

template<class T>// Right+Left rotation for balancing
node<T>* map<T>::rotation_rightleft(node<T>* head){

	node<T>* tmp = head->right;
	head->right = rotation_right(tmp);
	return rotation_left(head);

}

template<class T>// Left+Right rotation for balancing
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