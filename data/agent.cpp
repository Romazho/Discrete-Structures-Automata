/****************************************************************************
 * Fichier:			agent.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Agent
 ****************************************************************************/

#include "agent.h"

Agent::Agent(void)
{
	path_.push_back(new Door(1)); // On doit toujours commencer avec la porte 1.
	// Faire quelque chose avec les automates
	cout << path_.front();
}

Agent::~Agent(void)
{
	for (auto it : path_)
		delete it;
}
