/****************************************************************************
 * Fichier:			door.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Door
 ****************************************************************************/

#include "door.h"

Door::Door(unsigned doorNumber) {
	doorName_ = "Porte" + std::to_string(doorNumber) + ".txt";
	readFile();
}

void Door::isValid(const NextDoor& nextDoorPair) const
{
	(nextDoorPair.second) ? cout << "valide" : cout << "non valide";
}

bool Door::readFile() {
	fstream file(doorName_,ios::in);
	return readRule(file);
}

bool Door::readRule(fstream & file)
{
	string line;
	if (file.peek() == '{') { 
		for (;;) {
			file >> line;
			if (line.back() == ',')
				line.erase(line.size() - 1);
			if (line.back() == '}')
				break;
			rules_.push_back(line);
		}
		return readNextDoors(file);
	}
	return false;
}


bool Door::readNextDoors(fstream & file)
{
	if (file.eof())
		return false;
	Password password;
	string door;
	NextDoor nextDoor;
	bool validation = false;

	if (rules_.size() == 1 && rules_.front() == "S->") { // Exception
		file >> door; password = "";
		nextDoor = make_pair(door, validation);
		doorMap_.insert(make_pair(password, nextDoor));
		file.close();
		return true;
	}
	
	while (!file.eof()) { //Cas normal
		file >> password >> door;
		nextDoor = make_pair(door, validation);
		doorMap_.insert(make_pair(password, nextDoor));
	}
	cout << *this;
	file.close();
	return true;
}

ostream& operator<<(ostream& out, const Door& door)
{
	for (auto it = door.doorMap_.begin(); it != door.doorMap_.end(); ++it) {
		cout << "{" << it->first << " , " << it->second.first << " , "; door.isValid(it->second); cout << "}";
		if (it != door.doorMap_.end())
			cout << ",";
	}
	cout << endl;
	return out;
}


