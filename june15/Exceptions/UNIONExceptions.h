/*
 * UNIONExceptions.h
 *
 *  Created on: Jun 9, 2015
 *      Author: dor
 */

#ifndef EXCEPTIONS_UNIONEXCEPTIONS_H_
#define EXCEPTIONS_UNIONEXCEPTIONS_H_

#include <iostream>
#include <exception>
using namespace std;

class SetDoesNotExist:public exception {
public:
	const char* what() {
		return "The require index doesn't represent any set.\n";
	}
};

class ItemOutOfBounds:public exception {
public:
	const char* what() {
		return "The item index exceed the boundaries.\n";
	}
};

#endif /* EXCEPTIONS_UNIONEXCEPTIONS_H_ */
