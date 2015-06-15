/*
 * AVLExceptions.h
 *
 *  Created on: May 11, 2015
 *      Author: dor
 */

#ifndef AVLEXCEPTIONS_H_
#define AVLEXCEPTIONS_H_

#include <iostream>
#include <exception>
using namespace std;

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
