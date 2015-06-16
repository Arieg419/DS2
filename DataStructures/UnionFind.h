/*
 * UnionFind.h
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */

#ifndef DATASTRUCTURES_UNIONFIND_H_
#define DATASTRUCTURES_UNIONFIND_H_

#include "../Exceptions/UNIONExceptions.h"

template<class T>
class UnionFind {
private:
	int* parents; // Main array that represent the items.
	int* size; // used to determine which set to merge into the other(during union)
	T* data; // hold items data.
protected:
	int max_size;
public:
	UnionFind(int n, T defaultData);
	virtual ~UnionFind();

	void Union(int i, int j);
	int Find(int i);
	void SetData(int i, T data);
	T GetData(int i);

	void Print();
};

template<class T>
UnionFind<T>::UnionFind(int n, T defaultData) {
	this->max_size = n;
	this->parents = new int[n];
	this->size = new int[n];
	this->data = new T[n];

	for (int i = 0; i < n; i++) {
		this->parents[i] = -1; // (-1) represent root(set head)
		this->size[i] = 1;
		this->data[i] = defaultData;
	}
}

template<class T>
UnionFind<T>::~UnionFind() {
	delete[] parents;
	delete[] size;
	delete[] data;
}

template<class T>
void UnionFind<T>::Union(int a, int b) {
	int bigger, smaller;
	// check if legal set
	if (a < 0 || a >= max_size || b < 0 || b >= max_size)
		throw SetDoesNotExist();
	int i = Find(a);
	int j = Find(b);
	// find the bigger&smaller set
	bigger = (this->size[i] > this->size[j]) ? i : j;
	smaller = (i == bigger) ? j : i;
	// merge sets
	this->parents[smaller] = bigger;
	// update size
	this->size[bigger] += this->size[smaller];

	// make sure i is the name of the department
	if (bigger == i)
		return;
}

template<class T>
int UnionFind<T>::Find(int i) {
	int current; // temporary variable for interations
	// check if legal item
	if (i < 0 || i >= max_size)
		throw ItemOutOfBounds();

	// find set
	current = i;
	while (this->parents[current] != -1)
		current = this->parents[current];
	int root = current;

	// shrink trails
	current = i;
	while (this->parents[current] != -1) {
		int next = this->parents[current];
		this->parents[current] = root;
		current = next;
	}

	return root;
}

template<class T>
void UnionFind<T>::SetData(int i, T data) {
	// check if legal set
	if (i < 0 || i >= max_size)
		throw SetDoesNotExist();
	if (this->parents[i] != -1)
		throw SetDoesNotExist();

	this->data[i] = data;
}

template<class T>
T UnionFind<T>::GetData(int i) {
	// check if legal set
	if (i < 0 || i >= max_size)
		throw SetDoesNotExist();
	if (this->parents[i] != -1)
		throw SetDoesNotExist();

	return this->data[i];
}

template<class T>
void UnionFind<T>::Print() {
	// for debugging pupose only. shitty complexity!
	for (int i = 0; i < max_size; i++) {
		bool printed = false;
		for (int j = 0; j < max_size; j++) {
			if (Find(j) == i) {
				if (!printed) {
					cout << "set " << i << ": ";
					printed = true;
				}
				cout << j << "  ";
			}

		}
		if (printed)
			cout << endl;
	}
}

#endif /* DATASTRUCTURES_UNIONFIND_H_ */
