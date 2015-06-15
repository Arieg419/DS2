/*
 * Superhero.h
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */

#ifndef OBJECTS_SUPERHERO_H_
#define OBJECTS_SUPERHERO_H_

#include "../DataStructures/PairID.h"

class Superhero {
private:
	int id;
	int strength;
	int group;
public:
	Superhero(int id, int strength, int group);
	int getId();
	int getStrength();
	int getGroup();
	PairID getStrengthID();
	void setStrength(int strength);
	void setGroup(int group);
	virtual ~Superhero();
};

#endif /* OBJECTS_SUPERHERO_H_ */
