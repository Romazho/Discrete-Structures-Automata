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

	Door * door = new Door(fileName); // if exception, never constructed
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
