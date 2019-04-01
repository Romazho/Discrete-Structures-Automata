/****************************************************************************
 * Fichier:			agent.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Agent
 ****************************************************************************/

#include "agent.h"
#include <mutex> /// C'est quoi ça ???
using namespace std;

Agent::~Agent(void)
{
	password_ = "";

	for (Door * it : path_)
	{
		delete it;
		it = nullptr;
	}
	path_.clear();

	for (Automate * it : automates_)
	{
		delete it;
		it = nullptr;
	}
	automates_.clear();
}

/**
 * \brief Let the player enter in the maze
 */
void Agent::enterMaze()
{
	inMaze_ = true;
	openDoor("Porte1.txt");
}

/**
 * \brief Open the door if it is valid, create the associated automate, store them and print the door
 * \param fileName [const-ref] Name of the file
 * \return If the door can't be opened throw exception
 */
void Agent::openDoor(const string& fileName)
{
	if (!path_.empty() && !path_.back()->canOpen(fileName))
	{
		throw invalid_argument("\nCette porte n'est pas valide. Veuillez recommencer : "); // if can't open, exception
	}
	if (fileName != "Boss.txt")
	{
		Door * door = new Door(fileName); // if exception, never constructed
		path_.push_back(door);
		event_.push_back(door);
		automates_.push_back(new Automate(door));

		if (door->isPit())
		{
			cout << *door;
			clearPath();
			return;
		}

		cout << *door;

		string chosenDoor = fileName.substr(0, fileName.size() - 4);	//on enleve le ".txt"
		if ((path_.size() != 0) && (chosenDoor != "Porte1")) { /// Pas de .txt ? Ou chosen door?
			password_ += path_[path_.size()-2]->getPassMap()[chosenDoor];
		}
	}
	else
	{
		Door * door = new Door(fileName);
		event_.push_back(door);

		password_ += path_.back()->getPassMap()[door->getDoorName()];
		challengeBoss();
		printBoss();
		clearPath();
	}
	
}

void Agent::challengeBoss() {

	fstream file("Boss.txt", ios::in);

	//virifying if the path is right
	for (size_t i = 0; i < path_.size() && !file.eof(); i++) {

		string doorName;
		file >> doorName;
		if (path_[i]->getDoorName() != doorName)
		{
			cout << " Le path n'est pas le bon";
			return;
		}
	}

	concatenateAutomate();
}

void Agent::concatenateAutomate()
{
	char newStarter = 'F';
	bool hasChanged = false;

	vector<string> newRule = path_[0]->getRules(); // First door rules are
	vector<Door*> tmpPath;

	for (auto door : path_)
	{
		tmpPath.push_back(new Door(*door));
	}


	for (size_t i = 1; i < tmpPath.size(); ++i) // For each door
	{
		for (size_t j = 0; j < tmpPath[i]->getRules().size(); ++j) // For each production rule of this door
		{
			for (size_t k = 0; k < tmpPath[i]->getRules()[j].size(); ++k) // For each character of this production rule of this door
			{
				if (tmpPath[i]->getRules()[j][k] == automates_[i - 1]->getLastNode()) // Remove doubles
				{
					tmpPath[i]->getRules()[j][k] = newStarter;
					hasChanged = true;
				}
			}

			for (size_t k = 0; k < tmpPath[i]->getRules()[j].size(); ++k) // Last node (final state) of precedent automate is the new starter of current automate
			{
				if (tmpPath[i]->getRules()[j][k] == 'S')
				{
					tmpPath[i]->getRules()[j][k] = automates_[i - 1]->getLastNode();
				}
			}
		}

		if (hasChanged) // Change value if there was a doublon
		{
			newStarter++; 
			hasChanged = false;
		}

		for (size_t j = 0; j < tmpPath[i]->getRules().size(); ++j) // For each production rule of this door
		{
			newRule.push_back(tmpPath[i]->getRules()[j]); // Add to the tmp rule vector
		}
			
	}
	{ // Clear memory from the tmp path
		for (auto door : tmpPath) 
		{
			delete door;
			door = nullptr;
		}
		tmpPath.clear();
	}
	{ // Build the Boss Door 
		event_.back()->setRules(newRule);
		vector<string> uniqueConcatenatedPassword;
		uniqueConcatenatedPassword.push_back(password_);
		event_.back()->setPassword(uniqueConcatenatedPassword);
		automates_.push_back(new Automate(event_.back())); // Add Boss Door
	}
}

/**
 * \brief delete the Automates, clear Door::path_ and exit the maze
 */
void Agent::clearPath()
{
	for (Automate * it : automates_)
	{
		delete it;
		it = nullptr;
	}
	automates_.clear();
	path_.clear(); // Remove ptr but the ptr are shared with event_
	password_.clear();
	inMaze_ = false;
}

//à completer////////////////////////////////////////////////////////////////////////////////
void Agent::printEvent()
{
	if (event_.empty() == true)
		cout << "Vous devez d'abord ouvrir une porte.";

	else
	{
		for (auto it = event_.begin(), last = event_.begin(); it != event_.end(); ++it)
		{
			if ((*it)->getDoorName() != "Boss")
				cout << *(*it);

			else if ((*it)->getDoorName() == "Boss")
			{
				printBoss(it, last);
			}
			++last; /// Pour pas qu'on soit sur le boss
		}
	}
}

void Agent::printBoss()
{
	cout << "Evenement Boss\na.";

	for (auto it = path_.begin(); it != path_.end(); ++it)
	{
		cout << (*it)->getDoorName() << " ";
	}

	cout << endl << *event_.back();
}

void Agent::printBoss(vector<Door*>::iterator& present, vector<Door*>::iterator& last)
{
	cout << "Evenement Boss\na.";

	for (; last != present; ++last)
	{
		cout << (*last)->getDoorName() << " ";
	}

	cout << endl << **present;

}

void Agent::concatenatePassword() 
{
/*
	for (int i = 0; i < path_.size(); i++)
	{

		string doorName = path_[i]->getChosenDoor();

		//password_ += path_[i]->getDoorMap().find(doorName).nextDoorName;

		//fuck je me suis trompé, ca doit etre doorPassword...
		auto it = path_[i]->getDoorMap().find(doorName);
		if (it != path_[i]->getDoorMap().end())
		{
			password_ += it->second->nextDoorName;
			//wait mais ca doit prendre seulement une fois le mot de pass meme s'il y a deux portes
		}
	}
	*/
	/*
	for(size_t i = 0; i < path_.size();++i)
	{
		if (i != path_.size() path_[i] != "Porte1")
		{
			password_ += door->getPassMap().find()
		}
	}
	*/
}
