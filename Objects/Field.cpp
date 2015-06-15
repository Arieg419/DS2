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

}

Superhero* Field::GetStrongestSuperhero(int depID) {
	return groupsDepartments.GetData(depID);
}

int Field::GetNumOfSuperherosInRange(int min, int max) {
//TODO
	return -1;
}

/****************************** Private ***************************/
void Field::updateStrengthTree(int teamID, int factor) {
	int length = this->superheroesPowerTree.GetSize();
	if (length == 0)
		return;
	Superhero** superheroes = this->superheroesPowerTree.getSortedArray();

	// results arrays
	Superhero** updatedFruits = new Superhero*[length];
	PairID* updatedKeys = new PairID[length];

	// fill updated fruits using 2 pointers of fruits, and update fruits.
	int p1 = 0, p2 = 0, p3 = 0; // p1: fruit attack, p2: dont attack, p3: new array
	while (p1 < length && superheroes[p1]->getGroup()!=teamID)
		p1++; // set to first attack
	while (p2 < length && superheroes[p2]->getGroup()==teamID)
		p2++; // set to first safe

	if (p1 < length)
		superheroes[p1]->setStrength(superheroes[p1]->getStrength()*factor);

	// every iteration moving one fruit
	while (p3 < length) {
		bool copyP1;
		if (p1 == length) { // remain only safe fruits
			copyP1 = false; // move p2
		} else if (p2 == length) { // remain only to attack
			copyP1 = true;
		} else {
			if (superheroes[p1]->getPairID() < superheroes[p2]->getPairID())
				copyP1 = true;
			else
				copyP1 = false;
		}

		// deciding whether to copy p1 or p2
		if (copyP1) {
			updatedFruits[p3++] = superheroes[p1++];
			while (p1 < length && !insect.ShouldAttack(fruits[p1])) // calculate next p1
				p1++;
			if (p1 < length)
				insect.Attack(fruits[p1]);
		} else {
			updatedFruits[p3++] = superheroes[p2++];
			while (p2 < length && insect.ShouldAttack(fruits[p2])) // calculate next p2
				p2++;
		}
	}

	delete[] (superheroes);
	this->superheroesPowerTree.Reset();

	// converting array to a tree
	for (int i = 0; i < length; i++)
		updatedKeys[i] = updatedFruits[i]->getPairID();

	this->superheroesPowerTree.LoadSortedArray(updatedKeys, updatedFruits, length);
}
