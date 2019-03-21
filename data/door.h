/****************************************************************************
 * Fichier:			door.h
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Definition de la classe Door
 ****************************************************************************/

#ifndef DOOR_H
#define DOOR_H
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Door {

public:
	Door(void) = default;
	Door(unsigned doorNumber);

	string getDoorName(void) const { return doorName_; } ;
	vector<string> getRules(void) const { return rules_; };
	string getNextDoorByPassword(string password) const;

private:
	string doorName_;
	vector<string> rules_;
	map<string, string> doorMap_;// (password ; door)

	bool readFile(); // OuvrirPorte();
	bool readRule(fstream& file);
	bool readNextDoors(fstream & file);
};


#endif // !DOOR_H