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
	if(!hasBeenInit) {
		minID = superhero;
		maxID = superhero;
		hasBeenInit = true;
	} else {
		if(superhero < minID) {
			minID = superhero;
		}
		if(superhero > maxID) {
			maxID = superhero;
		}
	}
	hasBeenInit = true;
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
	groupsDepartments.SetData(team1,strongest1);
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
//TODO
}

Superhero* Field::GetStrongestSuperhero(int depID) {
	return groupsDepartments.GetData(depID);
}

int Field::GetNumOfSuperherosInRange(int min, int max) {
//TODO
	//function accesses getRange method of AVL Ranked Tree
	//so we need to grab that DS(Obejct)
	//Algorithm ############
	//1. Get superheroesPower Tree. All heroes sorted in an AVL tree based on strength.
	//2. Node rank is all of nodes children including itself.
	//3. Get superhero with value equal to or closest to Minimum power level.
	//4. Traverse the tree until you reach a superhero with the max interval val
	//5. Get the height from the min node the max node.
	//6. Deduct the nodes that are left to the minimum, look at his left childs ranks and subtract.
	//Superhero* minSuperHero = this->superheroesPowerTree.getByKey(min);
	//Superhero* maxSuperHero = this->superheroesPowerTree.getByKey(max);
	//int diffInHeight = minSuperHero
	return -1;
}
