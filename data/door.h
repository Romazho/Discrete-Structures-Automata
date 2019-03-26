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

struct NextDoor
{
	NextDoor(std::string doorname, bool valid = false) :nextDoorName(doorname),validity(valid) {};
	std::string nextDoorName;
	bool validity;
	
};
class Door {

public:
	Door(void) = default;
	Door(std::string doorNumber, bool ispit = true); // Appel readFile()
	~Door();
	std::string getDoorName(void) const { return doorName_; } ;
	std::vector<std::string> getRules(void) const { return rules_; };
	std::map<std::string, NextDoor*> getDoorMap(void) const { return doorMap_; };
	bool canOpen(const std::string & filename);
	bool contains(const std::string& filename) const;

	bool isValid(const NextDoor& nextDoorPair) const; // Donne si la porte est valide ou pas
	void validate(std::string& password) ; // Indique que la porte est maintenant valide

	friend std::ostream& operator<<(std::ostream&, const Door& door);

	bool isPit() const { return isPit_; };
private:
	std::string doorName_;
	bool isPit_;
	std::vector<std::string> rules_;
	std::map<std::string, NextDoor*> doorMap_;
	bool readFile(); // OuvrirPorte();
	bool readRule(std::fstream& file);
	bool readNextDoors(std::fstream & file);
};


#endif // !DOOR_H