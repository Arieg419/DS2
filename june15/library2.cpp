/*
 * library2.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */
#include <iostream>
#include "library2.h"
#include "Objects/Field.h"

void* Init(int n) {
	Field* field = new Field(n);
	return field;
}

StatusType AddSuperhero(void* DS, int superheroID, int strength) {
	((Field*) DS)->AddSuperhero(superheroID, strength);
	// TODO: Exceptions
	return SUCCESS;
}

StatusType AssignSuperhero(void* DS, int superheroID, int team) {
	((Field*) DS)->AssignSuperhero(superheroID, team);
	return SUCCESS;
}

StatusType JoinDepartments(void* DS, int team1, int team2) {
	((Field*) DS)->JoinDepartments(team1, team2);
	return SUCCESS;
}

StatusType GetDepartment(void* DS, int superheroID, int* department) {
	*department = ((Field*) DS)->GetDepartment(superheroID);
	return SUCCESS;
}

StatusType TeamUpgrade(void* DS, int teamID, int factor) {
	((Field*) DS)->TeamUpgrade(teamID, factor);
	return SUCCESS;
}

StatusType GetStrongestSuperhero(void* DS, int depID, int* superhero) {
	*superhero = ((Field*) DS)->GetStrongestSuperhero(depID)->getId();
	return SUCCESS;
}

StatusType GetNumOfSuperherosInRange(void* DS, int min, int max, int* num) {
	*num = ((Field*) DS)->GetNumOfSuperherosInRange(min, max);
	return SUCCESS;
}

void Quit(void** DS) {
	delete ((Field*)*DS);
	*DS = NULL;
}
