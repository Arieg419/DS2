/*
 * AVLExceptions.h
 *
 *  Created on: May 11, 2015
 *      Author: dor
 */
#include <iostream>
#include <exception>
using namespace std;

#ifndef AVLEXCEPTIONS_H_
#define AVLEXCEPTIONS_H_

/*class OutOfMemory:public exception {
public:
	const char* what() {
		return "I do not have the necessary resources for this allocation\n";
	}
};*/

class KeyAlreadyExist:public exception {
public:
	const char* what() {
		return "The key is already exist in the tree\n";
	}
};

class KeyDoesNotExist:public exception {
public:
	const char* what() {
		return "The key does not exist in the tree\n";
	}
};

class IllegalInput:public exception {
public:
	const char* what() {
		return "The input was wrong. Please try harder.\n";
	}
};

#endif /* AVLEXCEPTIONS_H_ */
