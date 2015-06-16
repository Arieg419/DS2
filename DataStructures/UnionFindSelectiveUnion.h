/*
 * UnionFindSelectiveUnion.h
 *
 *  Created on: Jun 15, 2015
 *      Author: dor
 */

#ifndef DATASTRUCTURES_UNIONFINDSELECTIVEUNION_H_
#define DATASTRUCTURES_UNIONFINDSELECTIVEUNION_H_

#include "UnionFind.h"
#include "InjectiveDictionary.h"

template<class T>
class UnionFindSelectiveUnion: public UnionFind<T> {
private:
//	int* Real2Fake;
//	int* Fake2Real;
	InjectiveDictionary dict; // key is the set, and data is the item
	T* data; // hold items data.
public:
	UnionFindSelectiveUnion(int n, T defaultData);
	virtual ~UnionFindSelectiveUnion();
	void Union(int i, int j);
	int Find(int i);
	void SetData(int i, T data);
	T GetData(int i);
	void PrintReal();
};

template<class T>
UnionFindSelectiveUnion<T>::UnionFindSelectiveUnion(int n, T defaultData) :
		UnionFind<T>(n, defaultData), dict(n) {
	this->data = new T[n];
	for (int i = 0; i < n; i++) {
		data[i] = defaultData;
	}
}

template<class T>
UnionFindSelectiveUnion<T>::~UnionFindSelectiveUnion() {
	delete[] data;
}

template<class T>
void UnionFindSelectiveUnion<T>::Union(int item1, int item2) {
	dict.remove(Find(item1));
	dict.remove(Find(item2));
	UnionFind<T>::Union(item1, item2);
	dict.set(item1, UnionFind<T>::Find(item1));
}

template<class T>
int UnionFindSelectiveUnion<T>::Find(int item) {
	int main_item = UnionFind<T>::Find(item);
	return dict.getKey(main_item);
}

template<class T>
void UnionFindSelectiveUnion<T>::SetData(int set, T data) {
	// check if legal set
	if (set < 0 || set >= this->max_size)
		throw SetDoesNotExist();
	if (Find(set) != set)
		throw SetDoesNotExist();

	this->data[set] = data;
}

template<class T>
T UnionFindSelectiveUnion<T>::GetData(int set) {
	// check if legal set
	if (set < 0 || set >= this->max_size)
		throw SetDoesNotExist();
	if (Find(set) != set)
		throw SetDoesNotExist();

	return this->data[set];
}

template<class T>
void UnionFindSelectiveUnion<T>::PrintReal() {
	// for debugging pupose only. shitty complexity!
	for (int i = 0; i < this->max_size; i++) {
		bool printed = false;
		for (int j = 0; j < this->max_size; j++) {
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

#endif /* DATASTRUCTURES_UNIONFINDSELECTIVEUNION_H_ */
