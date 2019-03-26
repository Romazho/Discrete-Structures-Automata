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
#include "automate.h"

using Password = std::string;
using NextDoor = std::pair<std::string, bool>; // pair < nom_porte , validité >

class Door {

public:
	Door(void) = default;
	Door(std::string doorNumber, bool ispit = true); // Appel readFile()
	std::string getDoorName(void) const { return doorName_; } ;
	std::vector<std::string> getRules(void) const { return rules_; };
	std::map<Password, NextDoor> getDoorMap(void) const { return doorMap_; };

	bool isValid(const NextDoor& nextDoorPair) const; // Donne si la porte est valide ou pas
	void validate(NextDoor& nextDoorPair) { nextDoorPair.second = true; }; // Indique que la porte est maintenant valide


	friend std::ostream& operator<<(std::ostream&, const Door& door);

private:
	std::string doorName_;
	bool isPit_;

	std::vector<std::string> rules_;
	std::map<Password, NextDoor> doorMap_;
	bool readFile(); // OuvrirPorte();
	bool readRule(std::fstream& file);
	bool readNextDoors(std::fstream & file);
};


#endif // !DOOR_H