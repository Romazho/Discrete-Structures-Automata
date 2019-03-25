/****************************************************************************
 * Fichier:			door.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Door
 ****************************************************************************/

#include "door.h"
using namespace std;

Door::Door(string doorName, bool isPit): doorName_(doorName), isPit_(isPit) {
	readFile();
}

bool Door::isValid(const NextDoor& nextDoorPair) const
{
	(nextDoorPair.second) ? cout << "valide" : cout << "non valide";
	return nextDoorPair.second;
}

bool Door::readFile() {
	fstream file(doorName_,ios::in);
	if (!file.is_open())
		throw  invalid_argument("Cette porte n'existe pas, veuillez entrez une porte valide : ");
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
		file >> door; password = ""; // Demander si la structure des fichier peut changer ex : "" Porte10 ; "ea" Porte5
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
	file.close();
	return true;
}

ostream& operator<<(ostream& out, const Door& door)
{
	
	cout << "a. " << door.doorName_ << endl << "b. ";
	for (auto it = door.doorMap_.begin(); it != door.doorMap_.end(); ++it) {
		cout << "{" << it->first << " , " << it->second.first << " , "; door.isValid(it->second); cout << "}";
		if (it != door.doorMap_.end())
			cout << ",";
	}
	cout << "\nc. " << (door.isPit_) ? "Cette porte est un gouffre, retour à la Porte1\n" : "Cette porte n'est pas un gouffre\n";
	return out;
}


