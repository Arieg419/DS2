/*
 * Field.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */

#include "Field.h"

Field::Field(int n) : groupsDepartments(n, NULL){

}

Field::~Field() {
	// TODO Auto-generated destructor stub
}

void Field::AddSuperhero(int superhero, int strength) {
	Superhero *newGuy = new Superhero(superhero, strength,-1);
	this->superheroesPowerTree.Insert(PairID(strength,superhero), newGuy);
	this->superheroesIdTree.Insert(superhero, newGuy);
}

void Field::AssignSuperhero(int superheroID, int team) {
	Superhero *retVal = superheroesIdTree.getByKey(superheroID);
	retVal->setGroup(team);
	this->superheroesHashTable.Insert(superheroID,retVal);
	//TODO need to check if strongest superhero was changed.0
}

void Field::JoinDepartments(int team1, int team2) {
	//TODO
}

int Field::GetDepartment(int superheroID) {
	Superhero *retVal = superheroesIdTree.getByKey(superheroID);
	return groupsDepartments.Find(retVal->getGroup());
}

void Field::TeamUpgrade(int teamID, int factor) {
	//TODO
}

Superhero* Field::GetStrongestSuperhero(int depID) {
	return groupsDepartments.GetData(depID);
}

int Field::GetNumOfSuperherosInRange(int min, int max) {
	//TODO
	return -1;
}
