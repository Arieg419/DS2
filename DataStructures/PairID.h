/*
 * PairID.h
 *
 *  Created on: May 8, 2015
 *      Author: dor
 */

#ifndef DATASTRUCTURES_PAIRID_H_
#define DATASTRUCTURES_PAIRID_H_

class PairID {
	//int msi,lsi; // Most/Least Significant Int
public:
	int msi, lsi;
	PairID(int msi = 0 , int lsi = 0);
	virtual ~PairID();

	void setIntegers(int mi, int li);

	bool operator==(const PairID& other);
	bool operator!=(const PairID& other);

	bool operator>(const PairID& other);
	bool operator>=(const PairID& other);

	bool operator<(const PairID& other);
	bool operator<=(const PairID& other);
};

#endif /* DATASTRUCTURES_PAIRID_H_ */
