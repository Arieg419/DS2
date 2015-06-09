/*
 * HashTable.h
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */

#ifndef DATASTRUCTURES_HASHTABLE_H_
#define DATASTRUCTURES_HASHTABLE_H_

#include "../DataStructures/AVLRankTree.h"
#include "../Exceptions/HashTableExceptions.h"

template<class T>
class HashTable {
private:
	struct HashNode {
	public:
		int key;
		T data;

		HashNode(int key, T data) {
			this->key = key;
			this->data = data;
		}
		HashNode() {
			this->key = int();
			this->data = T();
		}
	};
	AVLRankTree<int, HashNode> **hshTable;
	int tableSize;
	int counter;

	void InsertHashArray(AVLRankTree<int, HashNode>** array, int key, T val);
	void extendHashTable();
public:

	HashTable();
	~HashTable();
	int hashingFunction(int key);
	void Insert(int key, T data);
	T Find(int key);
};

template<class T>
HashTable<T>::HashTable() {
	int h_table_size = 2;
	tableSize = h_table_size;
	counter=0;
	hshTable = new AVLRankTree<int, HashNode>*[h_table_size];
	for (int i = 0; i < h_table_size; i++) {
		hshTable[i] = NULL;
	}
}

template<class T>
HashTable<T>::~HashTable() {
	for (int i = 0; i < this->tableSize; i++) {
		if (hshTable[i] != NULL) {
			delete hshTable[i];
		}
	}
	delete[] hshTable;
}

template<class T>
int HashTable<T>::hashingFunction(int key) {
	return (key % this->tableSize);
}

template<class T>
void HashTable<T>::Insert(int key, T data) {
	if (counter==tableSize)
		extendHashTable();
	InsertHashArray(hshTable, key, data);
	counter++;
}

template<class T>
T HashTable<T>::Find(int key) {
	int hashOutput = hashingFunction(key);
	if (hshTable[hashOutput] == NULL)
		throw HashKeyDoesNotExist();

	AVLRankTree<int, HashNode> *tree = hshTable[hashOutput];
	return tree->getByKey(key).data;
}

template<class T>
void HashTable<T>::extendHashTable() {
	int oldTableSize = this->tableSize;
	this->tableSize *= 2;
	//HashTable
	AVLRankTree<int, HashNode>** newHshTable =
			new AVLRankTree<int, HashNode>*[this->tableSize]; //allocating new hash table.
	for (int i = 0; i < this->tableSize; i++) {
		newHshTable[i] = NULL;
	}

	// add data to the new array
	for (int i = 0; i < oldTableSize; i++) { //updating new hashArray from old Array
		AVLRankTree<int, HashNode>* currentTree;
		currentTree = this->hshTable[i];
		if (currentTree==NULL) continue;
		HashNode* array = currentTree->getSortedArray();
		for (int j = 0; j < currentTree->GetSize(); j++) {
			InsertHashArray(newHshTable, array[j].key, array[j].data);
		}
		delete[] array;
	}

	// delete old array
	for (int i = 0; i < oldTableSize; i++) {
		if (hshTable[i] != NULL) {
			delete hshTable[i];
		}
	}
	delete[] hshTable;

	hshTable = newHshTable;
}

// ############################################################## //
template<class T>
void HashTable<T>::InsertHashArray(AVLRankTree<int, HashNode>** array, int key,
		T val) {
	AVLRankTree<int, HashNode>* newTree;
	int hashOutput = hashingFunction(key);

	if (array[hashOutput] == NULL) {
		newTree = new AVLRankTree<int, HashNode>();
		array[hashOutput] = newTree;
	} else {
		newTree = array[hashOutput];
	}
	newTree->Insert(key, HashNode(key, val));
}

#endif /* DATASTRUCTURES_HASHTABLE_H_ */
