/*
 * InjectiveDictionary.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: dor
 */

#include "InjectiveDictionary.h"

InjectiveDictionary::InjectiveDictionary(int size) {
	// TODO Auto-generated constructor stub
	key2data = new int[size];
	data2key = new int[size];
	for (int i = 0; i < size; i++) {
		key2data[i] = i;
		data2key[i] = i;
	}
}

InjectiveDictionary::~InjectiveDictionary() {
	delete[] key2data;
	delete[] data2key;
}

int InjectiveDictionary::getData(int key){
	return key2data[key];
}

int InjectiveDictionary::getKey(int data){
	return data2key[data];
}

void InjectiveDictionary::set(int key, int data){
	key2data[key]=data;
	data2key[data]=key;
}

void InjectiveDictionary::remove(int key){
	int data = getData(key);
	key2data[key]=-1;
	data2key[data]=-1;
}
