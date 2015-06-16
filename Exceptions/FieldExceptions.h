/*
 * FieldExceptions.h
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */

#ifndef EXCEPTIONS_FIELDEXCEPTIONS_H_
#define EXCEPTIONS_FIELDEXCEPTIONS_H_

#include <iostream>
#include <exception>
using namespace std;

class FieldInvalidInput:public exception {
public:
	const char* what() {
		return "\n";
	}
};

class FieldFailure:public exception {
public:
	const char* what() {
		return "\n";
	}
};

#endif /* EXCEPTIONS_FIELDEXCEPTIONS_H_ */
