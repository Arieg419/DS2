/*
 * Field.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */

#include "Field.h"

Field::Field(int n) :
		groupsDepartments(n, NULL) {

}

Field::~Field() {
	// TODO Auto-generated destructor stub
}

void Field::AddSuperhero(int superhero, int strength) {
	Superhero *newGuy = new Superhero(superhero, strength, -1);
	this->superheroesPowerTree.Insert(PairID(strength, superhero), newGuy);
	this->superheroesIdTree.Insert(superhero, newGuy);
}

void Field::AssignSuperhero(int superheroID, int team) {
	Superhero *superhero = superheroesIdTree.getByKey(superheroID);
	superhero->setGroup(team);
	this->superheroesHashTable.Insert(superheroID, superhero);
	// update strongest
	int department = groupsDepartments.Find(team);
	Superhero* old_strongest = groupsDepartments.GetData(department);
	if (superhero->getStrength() > old_strongest->getStrength()) {
		groupsDepartments.SetData(department, superhero);
	} else if (superhero->getStrength() == old_strongest->getStrength()) {
		if (superhero->getId() < old_strongest->getId())
			groupsDepartments.SetData(department, superhero);
	}
}

void Field::JoinDepartments(int team1, int team2) {
	Superhero* strongest1 = groupsDepartments.GetData(team1);
	Superhero* strongest2 = groupsDepartments.GetData(team2);

	groupsDepartments.Union(team1, team2);
	// TODO: Make "team1" the name of the deparment. unless it will happen, the following part will fail!
	// READ the upper row !!!!!!!!!!!!!!!!!!!!!
	groupsDepartments.SetData(team1, strongest1);
	if (strongest2->getStrength() > strongest1->getStrength()) {
		groupsDepartments.SetData(team1, strongest2);
	} else if (strongest1->getStrength() == strongest2->getStrength()) {
		if (strongest2->getId() < strongest1->getId())
			groupsDepartments.SetData(team1, strongest2);
	}
}

int Field::GetDepartment(int superheroID) {
	Superhero *retVal = superheroesIdTree.getByKey(superheroID);
	return groupsDepartments.Find(retVal->getGroup());
}

void Field::TeamUpgrade(int teamID, int factor) {
	Superhero* strongest1 = updateStrengthTree(teamID, factor); // update StrengthTree
	if (strongest1 == NULL) // Tree is empty
		return;
	int department = groupsDepartments.Find(strongest1->getGroup());
	Superhero* strongest2 = groupsDepartments.GetData(department);

	// Set strongest to the department
	if (strongest1->getStrength() > strongest2->getStrength()) {
		groupsDepartments.SetData(department, strongest1);
	} else if (strongest1->getStrength() == strongest2->getStrength()) {
		if (strongest1->getId() < strongest2->getId())
			groupsDepartments.SetData(department, strongest1);
	}
}

Superhero* Field::GetStrongestSuperhero(int depID) {
	return groupsDepartments.GetData(depID);
}

int Field::GetNumOfSuperherosInRange(int min, int max) {
//TODO
	return -1;
}

/****************************** Private ***************************/
int Field::updateStrengthTree(int teamID, int factor) {
	Superhero* strongest;
	int length = this->superheroesPowerTree.GetSize();
	if (length == 0)
		return NULL;
	Superhero** superheroes = this->superheroesPowerTree.getSortedArray();

	// results arrays
	Superhero** updatedSuperheroes = new Superhero*[length];
	PairID* updatedKeys = new PairID[length];

	// fill updated superheroes using 2 pointers of fruits, and update fruits.
	int p1 = 0, p2 = 0, p3 = 0; // p1: in team, p2: not in team, p3: new array
	while (p1 < length && superheroes[p1]->getGroup() != teamID)
		p1++; // set to first attack
	while (p2 < length && superheroes[p2]->getGroup() == teamID)
		p2++; // set to first safe

	if (p1 < length)
		superheroes[p1]->setStrength(superheroes[p1]->getStrength() * factor);

	// every iteration moving one fruit
	while (p3 < length) {
		bool copyP1;
		if (p1 == length) { // remain only safe fruits
			copyP1 = false; // move p2
		} else if (p2 == length) { // remain only to attack
			copyP1 = true;
		} else {
			if (superheroes[p1]->getStrengthID()
					< superheroes[p2]->getStrengthID())
				copyP1 = true;
			else
				copyP1 = false;
		}

		// deciding whether to copy p1 or p2
		if (copyP1) {
			strongest = superheroes[p1];
			updatedSuperheroes[p3++] = superheroes[p1++];
			while (p1 < length && superheroes[p1]->getGroup() != teamID) // calculate next p1
				p1++;
			if (p1 < length)
				superheroes[p1]->setStrength(
						superheroes[p1]->getStrength() * factor);
		} else {
			updatedSuperheroes[p3++] = superheroes[p2++];
			while (p2 < length && superheroes[p2]->getGroup() == teamID) // calculate next p2
				p2++;
		}
	}

	delete[] (superheroes);
	this->superheroesPowerTree.Reset();

	// converting array to a tree
	for (int i = 0; i < length; i++)
		updatedKeys[i] = updatedSuperheroes[i]->getStrengthID();

	this->superheroesPowerTree.LoadSortedArray(updatedKeys, updatedSuperheroes,
			length);

	return strongest;
}
