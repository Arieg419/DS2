/*
 * FieldExceptions.h
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */

#ifndef EXCEPTIONS_HASHTABLEEXCEPTIONS_H_
#define EXCEPTIONS_HASHTABLEEXCEPTIONS_H_

#include <iostream>
#include <exception>
using namespace std;

class HashKeyDoesNotExist:public exception {
public:
	const char* what() {
		return "The key does not exist in the structure.\n";
	}
};

#endif /* EXCEPTIONS_HASHTABLEEXCEPTIONS_H_ */
