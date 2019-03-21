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
using Password = std::string;
using NextDoor = std::pair<string, bool>; // pair < nom_porte , validité >

class Door {

public:
	Door(void) = default;
	Door(string doorNumber, bool ispit = true); // Appel readFile()
	string getDoorName(void) const { return doorName_; } ;
	vector<string> getRules(void) const { return rules_; };
	map<Password, NextDoor> getDoorMap(void) const { return doorMap_; };

	bool isValid(const NextDoor& nextDoorPair) const; // Donne si la porte est valide ou pas
	void validate(NextDoor& nextDoorPair) { nextDoorPair.second = true; }; // Indique que la porte est maintenant valide

	friend ostream& operator<<(ostream&, const Door& door);

private:
	string doorName_;
	bool isPit_;

	vector<string> rules_;
	map<Password, NextDoor> doorMap_;

	bool readFile(); // OuvrirPorte();
	bool readRule(fstream& file);
	bool readNextDoors(fstream & file);
};


#endif // !DOOR_H