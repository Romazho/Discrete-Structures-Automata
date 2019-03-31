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
#include <assert.h>
#include <iterator>
#include <map>
#include <vector>
#include <string>

struct NextDoor
{
	NextDoor(const std::string& doorname, const bool& valid = false) :nextDoorName(doorname), validity(valid) {};  
	std::string nextDoorName;
	bool validity;

};
class Door {

public:
	/*Constructors w/ Destructor*/
	Door(void) = default;
	Door(const std::string& fileName, const bool& isPit = true); // Appel readFile()
	~Door();

	/*Getters*/
	std::string getDoorName(void) const { return doorName_; };
	std::vector<std::string> getRules(void) const { return rules_; };
	std::multimap<std::string, NextDoor*> getDoorMap(void) const { return doorMap_; };
	bool canOpen(const std::string & filename) const;
	bool isValid(const NextDoor& nextDoorPair) const;
	bool isPit() const { return isPit_; };
	std::vector<std::string> getPasswords() { return passwords_; };
	std::string getChosenDoor() { return chosenDoor_; };
	std::map<std::string, std::string> getPassMap() { return passMap_; };

	/*Setters*/
	void validate(const std::string& password);
	void chooseDoor(std::string doorSelection) {
		chosenDoor_ = "Porte" + doorSelection;
	};

	/*Operators*/
	friend std::ostream& operator<<(std::ostream&, const Door& door);



private:
	std::string doorName_;
	bool isPit_;
	std::string chosenDoor_;

	std::vector<std::string> rules_;
	std::multimap<std::string, NextDoor*> doorMap_;
	std::map<std::string, std::string> passMap_; //prend un string:doorname et retourne string:password
	std::vector<std::string> passwords_;

	void readFile(const std::string& fileName);
	void readRule(std::fstream& file);
	void readNextDoors(std::fstream & file);
};


#endif // !DOOR_H