/*
 * InjectiveDictionary.h
 *
 *  Created on: Jun 16, 2015
 *      Author: dor
 */

#ifndef DATASTRUCTURES_INJECTIVEDICTIONARY_H_
#define DATASTRUCTURES_INJECTIVEDICTIONARY_H_

class InjectiveDictionary {
private:
	int *key2data, *data2key;
public:
	InjectiveDictionary(int size);
	virtual ~InjectiveDictionary();

	int getData(int key);
	int getKey(int data);
	void remove(int key);
	void set(int key, int data);
};

#endif /* DATASTRUCTURES_INJECTIVEDICTIONARY_H_ */
