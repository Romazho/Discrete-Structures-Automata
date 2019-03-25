/****************************************************************************
 * Fichier:			agent.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Agent
 ****************************************************************************/

#include "agent.h"
#include <mutex>
using namespace std;
Agent::Agent(void)
{
	//path_.push_back(new Door("Porte1.txt")); // On doit toujours commencer avec la porte 1.
	// Faire quelque chose avec les automates
	//
}

Agent::~Agent(void)
{
	for (auto it : path_)
		delete it;
}

void Agent::openDoor(const string& fileName)
{
	Door * newDoor = new Door(fileName); // if there is an exeption, will never be constructed;
	path_.push_back(newDoor);
	cout << *path_.back();
}
