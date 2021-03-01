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

	node* parent;
	node* left;
	node* right;

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

	// void rightRotation(node<T>* head);
	// void leftRotation(node<T>* head);
	int height(node<T>* head);
	int balanceFactor(node<T>* head);
	node<T>* recursiveInsert(node<T>* head, node<T>* prnt, int key, T value);

public:

	map();
	~map();

	node<T>* search(int key);
	void insert(int key, T value);
	void printTree(node<T>* head);

	// Getters
	node<T>* root() { return _root; }

};



// NODE FUNCTIONS
template<class T>
inline node<T>::node(int key, T value) {

	_values.first = key;
	_values.second = value;

	parent = 0;
	left = 0;
	right = 0;
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

}

template<class T>
map<T>::~map() {



}

template<class T>
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
node<T>* map<T>::recursiveInsert(node<T>* head, node<T>* prnt, int key, T value) {

	if (head == 0) {

		node<T>* tmp = new node<T>(key, value);
		tmp->parent = prnt;
		return tmp;
	}
	else {

		if (key < head->key()) 
			head->left = recursiveInsert(head->left, head, key, value);
		else if (key > head->key())
			head->right = recursiveInsert(head->right, head, key, value);

		return head;
	}

}

template<class T>
void map<T>::insert(int key, T value) {

	_root = recursiveInsert(_root, 0, key, value);
}

template<class T>
void map<T>::printTree(node<T>* head) {

	if (head == 0)
		return;

	printTree(head->left);
	std::cout << head->value() << ", height:" << height(head) << ", balance" << balanceFactor(head)<< "\n";
	printTree(head->right);
}

template<class T>
int map<T>::height(node<T>* head) {

	if (head == 0)
		return -1;
	else
		return (std::max(height(head->left), height(head->right)) + 1);
}

template<class T>
int map<T>::balanceFactor(node<T>* head) {

	if (head == 0)
		return 0;
	else
		return(height(head->left) - height(head->right));

}