/*
 * UnionFindSelectiveUnion.h
 *
 *  Created on: Jun 15, 2015
 *      Author: dor
 */

#ifndef DATASTRUCTURES_UNIONFINDSELECTIVEUNION_H_
#define DATASTRUCTURES_UNIONFINDSELECTIVEUNION_H_

#include "UnionFind.h"

template<class T>
class UnionFindSelectiveUnion : public UnionFind<T> {
private:
	int* Real2Fake;
	int* Fake2Real;

public:
	UnionFindSelectiveUnion(int n, T defaultData);
	virtual ~UnionFindSelectiveUnion();
	void Union(int i, int j);
	int Find(int i);
	void SetData(int i, T data);
	T GetData(int i);
	void swap(int* num1, int* num2);
};

template<class T>
UnionFindSelectiveUnion<T>::UnionFindSelectiveUnion(int n, T defaultData) : UnionFind<T>(n, defaultData){
	Fake2Real = new int[n];
	Real2Fake = new int[n];
	for (int i=0; i<n; i++){
		Real2Fake[i]=i;
		Fake2Real[i]=i;
	}
}

template<class T>
UnionFindSelectiveUnion<T>::~UnionFindSelectiveUnion(){
	delete[] Real2Fake;
	delete[] Fake2Real;
}

template<class T>
void UnionFindSelectiveUnion<T>::Union(int i, int j){
	UnionFind<T>::Union(i,j);
	if (UnionFind<T>::Find(i)==i)
		return;
	swap(Real2Fake+i,Real2Fake+j);
	swap(Fake2Real+i,Fake2Real+j);
}

template<class T>
int UnionFindSelectiveUnion<T>::Find(int i){
	int result = UnionFind<T>::Find(Real2Fake[i]);
	return Fake2Real[result];
}

template<class T>
void UnionFindSelectiveUnion<T>::SetData(int i, T data){
	UnionFind<T>::SetData(Real2Fake[i],data);
}

template<class T>
T UnionFindSelectiveUnion<T>::GetData(int i){
	return UnionFind<T>::GetData(Real2Fake[i]);
}
template<class T>
void UnionFindSelectiveUnion<T>::swap(int* num1,int* num2){
	int tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}

#endif /* DATASTRUCTURES_UNIONFINDSELECTIVEUNION_H_ */
