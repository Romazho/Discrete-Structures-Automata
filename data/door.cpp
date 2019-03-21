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

string Door::getNextDoorByPassword(string password) const
{
	for (pair<string, string> door : doorMap_) {
		if (door.first == password)
			return door.first;
	}
	return "null";
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
	string password, nextDoor;

	if (rules_.size() == 1 && rules_.front() == "S->") { // Exception
		file >> nextDoor; password = "";
		doorMap_.insert(make_pair(password, nextDoor));
		file.close();
		return true;
	}
	
	while (!file.eof()) { //Cas normal
		file >> password >> nextDoor;
		doorMap_.insert(make_pair(password, nextDoor));
	}
	for (auto it = doorMap_.begin(); it != doorMap_.end(); it++) {
		cout << " Password : " << it->first << " Door : " << it->second << endl;
	}
	file.close();
	return true;
}


