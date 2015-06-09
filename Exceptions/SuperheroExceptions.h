/*
 * UNIONExceptions.h
 *
 *  Created on: Jun 9, 2015
 *      Author: dor
 */

#ifndef EXCEPTIONS_SUPERHEROEXCEPTIONS_H_
#define EXCEPTIONS_SUPERHEROEXCEPTIONS_H_

#include <iostream>
#include <exception>
using namespace std;

class IllegalStrength:public exception {
public:
	const char* what() {
		return "Strength Must be positive!.\n";
	}
};

#endif /* EXCEPTIONS_SUPERHEROEXCEPTIONS_H_ */
