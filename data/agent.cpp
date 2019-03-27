/****************************************************************************
 * Fichier:			agent.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Agent
 ****************************************************************************/

#include "agent.h"
#include <mutex>
using namespace std;

Agent::~Agent(void)
{
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

void Agent::enterMaze()
{
	inMaze_ = true;
	openDoor("Porte1.txt");
}

void Agent::openDoor(const string& fileName)
{
	if (!path_.empty() && !path_.back()->canOpen(fileName))
	{
		throw invalid_argument("\nCette porte n'est pas valide. Veuillez recommencer : ");; // if can't open, lunch exception
	}
	Door * door = new Door(fileName); // if there is an exception, will never be constructed catch at main

	path_.push_back(door);
	event_.push_back(door);
	automates_.push_back(new Automate(door));

	if(door->isPit())
	{
		cout << *door;
		clearPath();
		return;
	}

	cout << *door;
}

void Agent::clearPath()
{
	for (Automate * it : automates_)
	{
		delete it;
		it = nullptr;
	}
	automates_.clear();

	path_.clear(); // Remove ptr but the ptr are shared with event_
	inMaze_ = false;
}

void Agent::printEvent()
{
	if (event_.empty() == true)
	{
		cout << "Vous devez d'abord ouvrir une porte.";
	}
	else {

	}
}
