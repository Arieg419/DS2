/*
 * main.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: dor
 */

#include <iostream>
#include "DataStructures/AVLRankTree.h"

//#include "Objects/Fruit.h"
using namespace std;

void AVLInterface();

int main(int argc, const char**argv) {
	AVLInterface();
	return 0;
}

void AVLInterface() {
	cout << "Good morning Sir. You may create your AVLRankTree now." << endl;
	int choice, item, ID, *arr;

	AVLRankTree<int, int> avl;
	while (1) {
		cout << "\n\n-----------------------" << endl;
		cout << "AVL Tree Implementation" << endl;
		cout << "-----------------------" << endl;
		cout << "1.Add new item into the tree" << endl;
		cout << "2.Remove item from the tree" << endl;
		cout << "3.Display Balanced AVL Tree" << endl;
		cout << "4.AVL Tree to Array" << endl;
		cout << "5.Get leftest" << endl;
		cout << "9.Exit" << endl;
		cout << "Enter your Choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "What is the ID? ";
			cin >> ID;
			cout << "Enter Item: ";
			cin >> item;
			//avl.Insert(ID, new int(item));
			avl.Insert(ID, item);
			break;
		case 2:
			cout << "What is the ID? ";
			cin >> ID;
			avl.Remove(ID);
			break;
		case 3:
			cout << "Balanced AVL Tree:" << endl;
			avl.print();
			break;
		case 4:
			cout << "array:" << endl;
			arr = avl.getSortedArray();
			cout << arr[0];
			for (int i = 1; i < avl.GetSize(); i++) {
				cout << "," << arr[i];
			}
			cout << endl;
			free(arr);
			break;
		case 5:
			cout << "minimin key is:" << endl;
			cout << avl.getSmallest() << endl;
			break;
		case 9:
			exit(0);
			break;
		default:
			cout << "Wrong Choice" << endl;
		}
	}
}
