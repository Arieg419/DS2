/*
 * AVLRankTree.h
 *
 *  Created on: May 3, 2015
 *      Author: dor
 */

#ifndef AVLRankTree_H_
#define AVLRankTree_H_

#include <iostream>
#include <assert.h>
#include <stdlib.h>

#include "../Exceptions/AVLExceptions.h"

using namespace std;

template<class K, class T>
class AVLRankTree {
private:
	struct Node {
		K key;
		T data;
		int height;
		Node* left;
		Node* right;
		Node* parent;

		int getBalance() {
			int leftHeight = 0, rightHeight = 0;
			if (left) {
				leftHeight = left->height;
			}
			if (right) {
				rightHeight = right->height;
			}
			return leftHeight - rightHeight;
		}
	};

	// variables
	Node* root;
	Node* smallest; // most left in the tree
	int size;

	// functions
	void RemoveNode(Node* node);
	void updateHeights(Node* node);
	void updateSmallest();
	void balance(Node* node);
	void llRotation(Node* node);
	void rrRotation(Node* node);
	void rlRotation(Node* node);
	void lrRotation(Node* node);
	Node* getNode(K key);
	void ParentPointTo(Node* child, Node* newChild);
	// recursions
	void print2(Node* nodeToPrint, int level);
	T* getSortedArray2(T* array, Node* node);
	void destroy2(Node* node);
	Node* LoadSortedArray2(K* sortedKeysArray, T* sortedArray, int length,
			Node* parent);

public:
	AVLRankTree();
	virtual ~AVLRankTree();
	void Reset();
	void LoadSortedArray(K* sortedKeysArray, T* sortedDataArray, int length);
	int GetSize();
	void Insert(K key, T data);
	void Remove(K key);
	T getByKey(K key);
	bool DoesExist(K key);
	T* getSortedArray();
	T getSmallest();
	void print();
};

/********************************* Public Functions *******************************/

template<class K, class T>
AVLRankTree<K, T>::AVLRankTree() {
	root = NULL;
	smallest = NULL;
	size = 0;
}

template<class K, class T>
AVLRankTree<K, T>::~AVLRankTree() {
	destroy2(root); // release allocated memory
	root = NULL;
	return;
}

template<class K, class T>
void AVLRankTree<K, T>::Reset() {
	destroy2(root); // release allocated memory
	this->size = 0;
	root = NULL;
	return;
}

template<class K, class T>
void AVLRankTree<K, T>::LoadSortedArray(K* sortedKeysArray, T* sortedDataArray,
		int length) {
	// verify sorted keys array
	for (int i = 1; i < length; i++)
		if (sortedKeysArray[i - 1] > sortedKeysArray[i])
			throw IllegalInput();
	Reset();
	root = LoadSortedArray2(sortedKeysArray, sortedDataArray, length, NULL);
	updateSmallest();
	this->size = length;
	return;
}

// Time complexity: O(1)
template<class K, class T>
int AVLRankTree<K, T>::GetSize() {
	return this->size;
}

// Time complexity: O(log(n))
template<class K, class T>
void AVLRankTree<K, T>::Insert(K key, T data) {
	if (DoesExist(key)) {
		throw KeyAlreadyExist();
	}

	// Create the node
	Node* new_node = new Node();
	new_node->height = 1; // height of the subtree with this node as root.
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	new_node->key = key;
	new_node->data = data;

	// choose where to add the node and add it.
	if (root == NULL) { // tree is empty
		root = new_node;
		smallest = new_node;
		this->size++;
		return;
	} else { // tree is not empty.
		Node* current = root;
		Node* parent = NULL;

		//////////////////////////////////////////////////////
		while ((current != NULL) && (current->key != key)) {
			parent = current;
			if (key < current->key) { // left subtree
				current = current->left;
			} else { // right subtree
				current = current->right;
			}
		}

		// add to tree
		if (key < parent->key)
			parent->left = new_node;
		else
			parent->right = new_node;
		new_node->parent = parent;
		/////////////////////////////////////////////////////

		updateHeights(new_node);
		this->balance(new_node);

		this->size++;

		return;
	}
}

// Time complexity: O(log(n))
template<class K, class T>
void AVLRankTree<K, T>::Remove(K key) {
	Node* node = getNode(key);
	if (node)
		RemoveNode(node);
	return;
}

// Time complexity: log(n)
template<class K, class T>
T AVLRankTree<K, T>::getByKey(K key) {
	Node* node = getNode(key);
	if (!node)
		throw KeyDoesNotExist();
	return node->data;
}

// Time complexity: log(n)
template<class K, class T>
bool AVLRankTree<K, T>::DoesExist(K key) {
	return (getNode(key) != NULL);
}

// allocating an array that will hold the entire tree sorted.
// Time complexity: O(n)
template<class K, class T>
T* AVLRankTree<K, T>::getSortedArray() {
	T* result = new T[this->size];

	getSortedArray2(result, root); // placing the tree in "result"
	return result;
}

// return the T with the smallest key
template<class K, class T>
T AVLRankTree<K, T>::getSmallest() {
	if (smallest)
		return this->smallest->data;
	throw KeyDoesNotExist();
}

// printing the tree. using the recursion print2
template<class K, class T>
void AVLRankTree<K, T>::print() {
	print2(root, 1);
}

/********************************* Private Functions *******************************/
template<class K, class T>
void AVLRankTree<K, T>::RemoveNode(Node* node) {
	// if leaf
	if (!(node->left) && !(node->right)) {
		ParentPointTo(node, NULL);
		if (node->parent) {
			updateHeights(node->parent);
			this->balance(node->parent);
		} else {
			this->smallest = NULL;
		}
		this->size--;
		delete node;
		return;
	}
	// if only right child
	else if (!(node->left) && (node->right)) {
		ParentPointTo(node, node->right);
		node->right->parent = node->parent;

		if (node->parent) {
			updateHeights(node->parent);
			this->balance(node->parent);
		} else {
			updateSmallest();
		}
		delete node;
		this->size--;
		return;
	}

	// if only left child
	else if ((node->left) && !(node->right)) {
		ParentPointTo(node, node->left);
		node->left->parent = node->parent;

		if (node->parent) {
			updateHeights(node->parent);
			this->balance(node->parent);
		} else {
			updateSmallest();
		}
		delete node;
		this->size--;
		return;
	}

	// if node has 2 childrens
	else {
		// find new root for subtree
		Node* current = node->right;
		while (current->left)
			current = current->left;

		// switch current and node.
		K backupK = current->key;
		current->key = node->key;
		node->key = backupK;

		T backupT = current->data;
		current->data = node->data;
		node->data = backupT;

		RemoveNode(current); // recursive call. will happen only once, because now node doesn't have 2 children.
	}
}

// Updating the height property of the node and his ancestors.
template<class K, class T>
void AVLRankTree<K, T>::updateHeights(Node* node) {
	Node* current = node;
	while (current != NULL) {
		int leftHeight = 0, rightHeight = 0;
		if (current->left) {
			leftHeight = current->left->height;
		}
		if (current->right) {
			rightHeight = current->right->height;
		}
		current->height =
				((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
		current = current->parent;
	}
}

// Updating the smallest key. O(log(k)).
template<class K, class T>

void AVLRankTree<K, T>::updateSmallest() {
	Node* current = root;
	if (!current) {
		this->smallest = NULL;
		return; // empty tree
	}
	while (current->left != NULL) {
		current = current->left;
	}
	this->smallest = current;
}

template<class K, class T>
void AVLRankTree<K, T>::balance(Node* node) {
	int balanceFactor = node->getBalance();
	if (balanceFactor >= 2) { //left Heavy
		//assert(node->left->getBalance() != 0);
		if (node->left->getBalance() >= 0) {
			llRotation(node);
		} else {
			lrRotation(node);
		}
	} else if (balanceFactor <= -2) { //left Heavy
		//assert(node->right->getBalance() != 0);
		if (node->right->getBalance() > 0) {
			rlRotation(node);
		} else {
			rrRotation(node);
		}
	}

	if (node->parent) {
		balance(node->parent);
	}

	updateSmallest();
}

// node: the node with the |balance|>=2
template<class K, class T>
void AVLRankTree<K, T>::llRotation(Node* node) {
	Node* parent = node->parent;
	Node* lChild = node->left;

	// parent-node relation
	ParentPointTo(node, lChild);
	lChild->parent = parent;

	Node* lrChild = node->left->right; //backup
	// node-child relation
	lChild->right = node;
	node->parent = lChild;
	// restore lost chain
	node->left = lrChild;
	if (lrChild)
		lrChild->parent = node;

	updateHeights(node);
}

// node: the node with the |balance|>=2
template<class K, class T>
void AVLRankTree<K, T>::rrRotation(Node* node) {
	Node* parent = node->parent;
	Node* rChild = node->right;

	// parent-node relation
	ParentPointTo(node, rChild);
	rChild->parent = parent;

	Node* rlChild = node->right->left; //backup
	// node-child relation
	rChild->left = node;
	node->parent = rChild;
	// restore lost chain
	node->right = rlChild;
	if (rlChild)
		rlChild->parent = node;

	updateHeights(node);
}

// node: the node with the |balance|>=2
template<class K, class T>
void AVLRankTree<K, T>::lrRotation(Node* node) {
	rrRotation(node->left);
	llRotation(node);
}

// node: the node with the |balance|>=2
template<class K, class T>
void AVLRankTree<K, T>::rlRotation(Node* node) {
	llRotation(node->right);
	rrRotation(node);
}

template<class K, class T>
typename AVLRankTree<K, T>::Node* AVLRankTree<K, T>::getNode(K key) {
	Node* current = root;
	while ((current != NULL) && (current->key != key)) { // while wasn't placed yet
		if (key < current->key) { // left subtree
			current = current->left;
		} else { // right subtree
			current = current->right;
		}
	}
	return current;
}

template<class K, class T>
void AVLRankTree<K, T>::ParentPointTo(Node* child, Node* newChild) {
	if (child->parent == NULL)
		root = newChild;
	else {
		if (child->parent->left == child) {
			child->parent->left = newChild;
		} else {
			child->parent->right = newChild;
		}

	}
}

/************************************* Recursions ***********************************/

template<class K, class T>
void AVLRankTree<K, T>::print2(Node* nodeToPrint, int level) {
	int i;
	if (nodeToPrint) {
		print2(nodeToPrint->right, level + 1);
		cout << "\n";
		if (nodeToPrint == root) {
			cout << "Root ->";
		}

		for (i = 0; i < level && nodeToPrint != root; i++) {
			cout << "       ";
		}
		//cout << nodeToPrint->key;
		//cout << nodeToPrint->data;
		cout << nodeToPrint->height;
		//cout << nodeToPrint->getBalance();

		print2(nodeToPrint->left, level + 1);
	}
}

// placing the subtree starts with node in the array, and return pointer to the next place in the array
template<class K, class T>
T* AVLRankTree<K, T>::getSortedArray2(T* array, Node* node) {
	if (node == NULL)
		return array;
	array = getSortedArray2(array, node->left);
	*array = node->data;
	array++;
	return getSortedArray2(array, node->right);
}

// destroying the array, post order
template<class K, class T>
void AVLRankTree<K, T>::destroy2(Node* node) {
	if (node == NULL)
		return;
	destroy2(node->left);
	destroy2(node->right);
	delete node;
}

template<class K, class T>
typename AVLRankTree<K, T>::Node* AVLRankTree<K, T>::LoadSortedArray2(
		K* sortedKeysArray, T* sortedDataArray, int length, Node* parent) {
	if (length == 0)
		return NULL;
	Node* node = new Node();

	int pos = length / 2;
	node->key = sortedKeysArray[pos];
	node->data = sortedDataArray[pos];
	node->parent = parent;
	node->left = LoadSortedArray2(sortedKeysArray, sortedDataArray, pos, node);
	node->right = LoadSortedArray2(sortedKeysArray + pos + 1,
			sortedDataArray + pos + 1, length - pos - 1, node);

	// find the height
	if (!node->left && !node->right) // no childs
		node->height = 1;
	else if (!node->left) // right child only
		node->height = node->right->height + 1;
	else if (!node->right) // left child only
		node->height = node->left->height + 1;
	else
		node->height =
				(node->left->height > node->right->height) ?
						node->left->height : node->right->height; // both children exist

	return node;
}

#endif /* AVLRankTree_H_ */
