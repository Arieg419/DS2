/*
 * Field.h
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */

#ifndef OBJECTS_FIELD_H_
#define OBJECTS_FIELD_H_

#include "Superhero.h"

class Field {
public:
	Field();
	virtual ~Field();
	void AddSuperhero(Superhero superhero, int strength);
	void AssignSuperhero(int superheroID, int team);
	void JoinDepartments(int team1, int team2);
	int GetDepartment(int superheroID, int* department);
	void TeamUpgrade(int teamID, int factor);
	Superhero* GetStrongestSuperhero(int depID);
	int GetNumOfSuperherosInRange(int min, int max);
};

#endif /* OBJECTS_FIELD_H_ */
