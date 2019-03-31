/****************************************************************************
 * Fichier:			door.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Door
 ****************************************************************************/
#include "door.h"

using namespace std;

/**
 * \brief 
 * \param fileName [const-ref] Name of the file/door to open 
 * \param isPit [const ref]
 */
Door::Door(const string& fileName,const bool& isPit): isPit_(isPit)
{
	for(auto character : fileName)
	{
		if (character == '.')
			break;
		doorName_ += character;
	}
	readFile(fileName);
}

Door::~Door()
{
	for (pair<string, NextDoor*> it : doorMap_)
	{
		delete (it.second);
		it.second = nullptr;
	}
}

/**
 * \brief Tell if the door in param fileName can be opened
 * \param fileName [const-ref] name of the file 
 * \return bool If door can be opened
 * \return If she's not in the set of current NextDoor, throw an exeption
 */
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

/**
 * \brief Find and print if NextDoor is a valid door to open
 * \param nextDoor [const-ref] Any NextDoor
 * \return bool Validity of the NextDoor
 */
bool Door::isValid(const NextDoor& nextDoor) const
{
	(nextDoor.validity) ? cout << "valide" : cout << "non valide";
	return nextDoor.validity;
}

/**
 * \brief Validate the NextDoor with a valid password
 * \param password [const-ref] Valid password given by the Automate 
 */
void Door::validate(const string& password)
{
	//doorMap_.find(password)->validity = true;
	//auto range = doorMap_.equal_range(password);
	//isPit_ = false;

	auto it = doorMap_.find(password);
		if (it != doorMap_.end())
		{
			it->second->validity = true;
			isPit_ = false;
		}
	
}

/**
 * \brief  Read the file and ensure that the file to open is valid
 * \param fileName [const-ref] Name of the file  
 */
void Door::readFile(const string& fileName) 
{
	fstream file(fileName,ios::in);

	if (!file.is_open())
		throw  invalid_argument("Cette porte n'existe pas, veuillez entrez une porte valide : ");

	readRule(file);
}

/**
 * \brief Read rules of the current file and store them in Door::rules_ then call Door::readNextDoors(fstream&)
 * \param file [reference] Valid opened file
 */
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

	throw out_of_range("\n CURRENT FILE IS NOT IN THE OPERABLE RANGE OF FUNCTION Door::readRule ");  // Should never happen
}

/**
 * \brief Read all door's passowords and next doors and store it win Door::doorMap_
 * \param file [reference] Valid opened file
 * \return 
 */
void Door::readNextDoors(fstream & file)
{
	if (file.eof())
		throw out_of_range("\n CURRENT FILE IS NOT IN THE OPERABLE RANGE OF FUNCTION Door::readNextDoors \n Veuillez recommencer : ");
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

/**
 * \brief Print the door's name, NexDoors with their validity and if it is a pit
 * \param out [reference] Output stream for cascaded call
 * \param door [const-ref] Door to print
 * \return Output stream for cascaded call
 */
ostream& operator<<(ostream& out, const Door& door)
{
	cout << "Evenement Porte" << "\na. " << door.doorName_ << endl << "b. ";

	for (auto it = door.doorMap_.begin(); it != door.doorMap_.end(); ++it) 
	{
			cout << "{" << it->first << " , " << it->second->nextDoorName << " , "; door.isValid(*it->second); cout << "}";

			if (it != door.doorMap_.end())
				cout << ",";
	}

	cout << "\nc. " << ((door.isPit_) ? "Cette porte est un gouffre, retour à la Porte1\n" : "Cette porte n'est pas un gouffre\n");
	return out;
}


