/*
 * library2.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */
#include <iostream>
#include "library2.h"
#include "Objects/Field.h"
#include "Exceptions/FieldExceptions.h"

void* Init(int n) {
	Field* field = new Field(n);
	return field;
}

StatusType AddSuperhero(void* DS, int superheroID, int strength) {
	if (!DS)
		return INVALID_INPUT;
	try {
		((Field*) DS)->AddSuperhero(superheroID, strength);
	} catch (FieldInvalidInput& e) {
		return INVALID_INPUT;
	} catch (FieldFailure& e) {
		return FAILURE;
	} catch (std::bad_alloc& err) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType AssignSuperhero(void* DS, int superheroID, int team) {
	if (!DS)
		return INVALID_INPUT;
	try {
		((Field*) DS)->AssignSuperhero(superheroID, team);
	} catch (FieldInvalidInput& e) {
		return INVALID_INPUT;
	} catch (FieldFailure& e) {
		return FAILURE;
	} catch (std::bad_alloc& err) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType JoinDepartments(void* DS, int team1, int team2) {
	if (!DS)
		return INVALID_INPUT;
	try {
		((Field*) DS)->JoinDepartments(team1, team2);
	} catch (FieldInvalidInput& e) {
		return INVALID_INPUT;
	} catch (FieldFailure& e) {
		return FAILURE;
	} catch (std::bad_alloc& err) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType GetDepartment(void* DS, int superheroID, int* department) {
	if (!DS || department==NULL)
		return INVALID_INPUT;
	try {
		*department = ((Field*) DS)->GetDepartment(superheroID);
	} catch (FieldInvalidInput& e) {
		return INVALID_INPUT;
	} catch (FieldFailure& e) {
		return FAILURE;
	} catch (std::bad_alloc& err) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType TeamUpgrade(void* DS, int teamID, int factor) {
	if (!DS)
		return INVALID_INPUT;
	try {
		((Field*) DS)->TeamUpgrade(teamID, factor);
	} catch (FieldInvalidInput& e) {
		return INVALID_INPUT;
	} catch (FieldFailure& e) {
		return FAILURE;
	} catch (std::bad_alloc& err) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType GetStrongestSuperhero(void* DS, int depID, int* superhero) {
	if (!DS || superhero==NULL)
		return INVALID_INPUT;
	try {
		*superhero = ((Field*) DS)->GetStrongestSuperhero(depID)->getId();
	} catch (FieldInvalidInput& e) {
		return INVALID_INPUT;
	} catch (FieldFailure& e) {
		return FAILURE;
	} catch (std::bad_alloc& err) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType GetNumOfSuperherosInRange(void* DS, int min, int max, int* num) {
	if (!DS || num==NULL)
		return INVALID_INPUT;
	try {
		*num = ((Field*) DS)->GetNumOfSuperherosInRange(min, max);
	} catch (FieldInvalidInput& e) {
		return INVALID_INPUT;
	} catch (FieldFailure& e) {
		return FAILURE;
	} catch (std::bad_alloc& err) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

void Quit(void** DS) {
	delete ((Field*) *DS);
	*DS = NULL;
}
