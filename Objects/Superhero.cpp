/*
 * Superhero.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */

#include "Superhero.h"
#include "../Exceptions/SuperheroExceptions.h"

Superhero::Superhero(int id, int strength, int group) {
	this->id = id;
	this->strength = strength;
	this->group = -1;
}

int Superhero::getId() {
	return this->id;
}
int Superhero::getStrength() {
	return this->strength;
}
int Superhero::getGroup() {
	return this->group;
}

PairID Superhero::getStrengthID(){
	return PairID(this->getStrength(), this->getId());
}

void Superhero::setStrength(int strength) {
	if (strength<0) throw IllegalStrength();
	this->strength = strength;
}
void Superhero::setGroup(int group) {
	this->group = group;
}

Superhero::~Superhero() {
	// Auto is good enough
}
