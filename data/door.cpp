/****************************************************************************
 * Fichier:			door.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Door
 ****************************************************************************/

#include "door.h"
using namespace std;

Door::Door(string doorName, bool isPit): doorName_(doorName), isPit_(isPit)
{
	readFile();
}

Door::~Door()
{
	for (pair<string, NextDoor*> it : doorMap_)
	{
		delete (it.second);
		it.second = nullptr;
	}
}

bool Door::canOpen(const std::string& fileName)
{
	if (fileName == "Porte1.txt")
		return true;
	else
	{
		for (const auto& it : doorMap_)
			if (fileName.find(it.second->nextDoorName) != std::string::npos)
				return it.second->validity; // Validity
	}

	throw invalid_argument("\nCette porte n'est pas dans l'ensemble des portes présentées. Veuillez recommencer : ");
}


/**
 * \brief Find and print if NextDoor is valid
 * \param nextDoor const reference 
 * \return bool if next door is valid
 */
bool Door::isValid(const NextDoor& nextDoor) const
{
	(nextDoor.validity) ? cout << "valide" : cout << "non valide";
	return nextDoor.validity;
}

void Door::validate(std::string& password)
{
	auto it = doorMap_.find(password);
		if (it != doorMap_.end())
		{
			it->second->validity = true;
			isPit_ = false;
		}
			
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
	string password;
	string doorName;
	bool validation = false;

	if (rules_.size() == 1 && rules_.front() == "S->") { // Exception
		file >> doorName; password = ""; // Demander si la structure des fichier peut changer ex : "" Porte10 ; "ea" Porte5
		doorMap_.insert(make_pair(password, new NextDoor(doorName)));
		file.close();
		return true;
	}
	
	while (!file.eof()) { //Cas normal
		file >> password >> doorName;
		doorMap_.insert(make_pair(password, new NextDoor(doorName)));
	}
	file.close();
	return true;
}

ostream& operator<<(ostream& out, const Door& door)
{
	
	cout << "\na. " << door.doorName_ << endl << "b. ";
	for (auto it = door.doorMap_.begin(); it != door.doorMap_.end(); ++it) {
		cout << "{" << it->first << " , " << it->second->nextDoorName << " , "; door.isValid(*it->second); cout << "}";
		if (it != door.doorMap_.end())
			cout << ",";
	}
	cout << "\nc. " << ((door.isPit_) ? "Cette porte est un gouffre, retour à la Porte1\n" : "Cette porte n'est pas un gouffre\n");
	return out;
}


