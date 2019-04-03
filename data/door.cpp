/****************************************************************************
 * Fichier:			door.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Door
 ****************************************************************************/
#include "door.h"

using namespace std;

Door::Door(const string& fileName, const bool& isPit, const bool& bossDefeated) : isPit_(isPit), bossDefeated_(bossDefeated)
{
	if (fileName != "Boss.txt") {
		for (auto character : fileName)
		{
			if (character == '.')
				break;
			doorName_ += character;
		}
		readFile(fileName);
	}
	else if (fileName == "Boss.txt") {
		doorName_ = "Boss";
	}
}

Door::Door(const Door& door) : doorName_(door.doorName_), isPit_(door.isPit_), bossDefeated_(door.bossDefeated_)
{
	rules_ = door.rules_;
	for (auto it = door.doorMap_.begin(); it != door.doorMap_.end(); ++it)
	{
		doorMap_.insert(make_pair(it->first, new NextDoor(*(it->second))));
	}
	passMap_ = door.passMap_;
	passwords_ = door.passwords_;

}

Door::~Door()
{
	for (pair<string, NextDoor*> it : doorMap_)
	{
		delete it.second;
		it.second = nullptr;
	}
	doorMap_.clear();
}

bool Door::canOpen(const string& fileName) const
{
	if (fileName == "Porte1.txt")
		return true;

	for (const auto& it : doorMap_)
	{
		if (fileName.find(it.second->nextDoorName) != std::string::npos)
			return it.second->validity; // Validity
	}

	throw invalid_argument("\nCette porte n'est pas dans l'ensemble des portes présentées. Veuillez recommencer : ");
}

bool Door::isValid(const NextDoor& nextDoor) const
{
	(nextDoor.validity) ? cout << "valide" : cout << "non valide";
	return nextDoor.validity;
}

void Door::validate(const string& password)
{
	auto range = doorMap_.equal_range(password);
	for (range.first; range.first != range.second; range.first++)
	{
		range.first->second->validity = true;
		isPit_ = false;
	}

}

void Door::readFile(const string& fileName)
{
	fstream file(fileName, ios::in);

	if (!file.is_open())
		throw  invalid_argument("Cette porte n'existe pas, veuillez entrez une porte valide : ");

	readRule(file);
}

void Door::readRule(fstream & file)
{
	string line;
	file >> line;
	if (line == "{")
	{
		while (!file.eof())
		{
			file >> line;
			if (line.back() == ',')
				line.erase(line.size() - 1);

			if (line.back() == '}')
				break;

			rules_.push_back(line);
		}

		readNextDoors(file);
		return;
	}

	throw invalid_argument("\n CURRENT FILE IS NOT IN THE OPERABLE RANGE OF FUNCTION Door::readRule ");  // Should never happen
}

void Door::readNextDoors(fstream & file)
{
	if (file.eof())
		throw invalid_argument("\n CURRENT FILE IS NOT IN THE OPERABLE RANGE OF FUNCTION Door::readNextDoors \n Veuillez recommencer : "); // Should never happen
	string password;
	string doorName;
	bool validation = false;

	int pos = file.tellg();
	pos++;
	pos++;
	file.seekg(pos);

	while (!file.eof())
	{
		char test = file.peek();

		if (file.peek() == ' ') {
			file >> doorName; password = "";
			if (rules_.front() == "S->") {
				doorMap_.insert(make_pair(password, new NextDoor(doorName, true)));
				isPit_ = false;
				passMap_.insert(make_pair(doorName, password));
			}
			else {
				doorMap_.insert(make_pair(password, new NextDoor(doorName, false)));
				passMap_.insert(make_pair(doorName, password));
			}
		}
		else
		{
			file >> password >> doorName;
			passwords_.push_back(password);

			doorMap_.insert(make_pair(password, new NextDoor(doorName)));
			passMap_.insert(make_pair(doorName, password));
		}
	}

	file.close();
}

ostream& operator<<(ostream& out, const Door& door)
{

	if (door.getDoorName() != "Boss") {
		cout << "Evenement Porte" << "\na. " << door.doorName_ << endl << "b. ";
		for (auto it = door.doorMap_.begin(); it != door.doorMap_.end(); ++it)
		{
			cout << "{" << it->first << " , " << it->second->nextDoorName << " , "; door.isValid(*it->second); cout << "}";

			if (it != door.doorMap_.end())
				cout << ",";
		}

		cout << "\nc. " << ((door.isPit_) ? "Cette porte est un gouffre, retour à la Porte1\n" : "Cette porte n'est pas un gouffre\n");
	}

	else
	{
		cout << door.doorName_ << endl << "b. " << door.getPasswords().front() << " P = {"; // Concatenate password
		for (size_t i = 0; i < door.getRules().size(); ++i)
		{
			cout << (door.getRules()[i]);
			if (i != (door.getRules().size() - 1))
				cout << ", ";
		}
		cout << "}";
		cout << "\nc. " << ((door.bossDefeated_) ? "L'agent vainc le Boss\n" : "Le Boss vainc l'agent. Retour à la Porte1\n");
	}
	return out;
}


