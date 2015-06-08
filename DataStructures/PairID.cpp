/*
 * PairID.cpp
 *
 *  Created on: May 8, 2015
 *      Author: dor
 */

#include "PairID.h"

PairID::PairID(int msi, int lsi) {
	this->msi = msi;
	this->lsi = lsi;
}

PairID::~PairID() {
}

void PairID::setIntegers(int i, int j) {
	this->msi = i;
	this->lsi = j;
}

bool PairID::operator==(const PairID& other) {
	return (msi==other.msi) && (lsi==other.lsi);
}
bool PairID::operator!=(const PairID& other) {
	return !(operator==(other));
}

bool PairID::operator>(const PairID& other) {
	if (msi==other.msi){
		return lsi>other.lsi;
	} else {
		return msi>other.msi;
	}
}
bool PairID::operator>=(const PairID& other) {
	return operator>(other) || operator ==(other);
}

bool PairID::operator<(const PairID& other) {
	return !(operator>=(other));
}
bool PairID::operator<=(const PairID& other) {
	return operator<(other) || operator ==(other);
}
