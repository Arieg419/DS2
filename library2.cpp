/*
 * library2.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */
#include <iostream>
#include "library2.h"

void* Init(int n) {
	return NULL;
}

StatusType AddSuperhero(void* DS, int superheroID, int strength) {
	return SUCCESS;
}

StatusType AssignSuperhero(void* DS, int superheroID, int team) {
	return SUCCESS;
}

StatusType JoinDepartments(void* DS, int team1, int team2) {
	return SUCCESS;
}

StatusType GetDepartment(void* DS, int superheroID, int* department) {
	return SUCCESS;
}

StatusType TeamUpgrade(void* DS, int teamID, int factor) {
	return SUCCESS;
}

StatusType GetStrongestSuperhero(void* DS, int depID, int* superhero) {
	return SUCCESS;
}

StatusType GetNumOfSuperherosInRange(void* DS, int min, int max, int* num) {
	return SUCCESS;
}

void Quit(void** DS) {

}
