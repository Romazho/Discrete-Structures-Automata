/****************************************************************************
 * Fichier:			agent.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Agent
 ****************************************************************************/

#include "agent.h"
#include <mutex>
using namespace std;
Agent::Agent(void){}

Agent::~Agent(void)
{
	for (pair<Door*,Automate*> it : path_){
		delete it.second; //Automate*
	}
	for(Door* it : event_)
	{
		delete it; // Door *
	}
}

void Agent::openDoor(const string& fileName)
{
	Door * door = new Door(fileName); // if there is an exception, will never be constructed catch at main
	Automate * automate = generateAutomate(door->getRules());
	path_.insert(make_pair(door, automate));
	event_.push_back(door);

	automate->generatePasswords(door);

	cout << *door;
}

Automate* Agent::generateAutomate(const vector<string>& rule)
{
	return new Automate(rule);
}

void Agent::clearPath()
{
	for (auto it : path_) {
		delete it.second; //Automate*
	}
	path_.clear(); // Remove ptr but the ptr are shared with event_
}
