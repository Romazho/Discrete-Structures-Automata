/****************************************************************************
 * Fichier:			agent.h
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Definition de la classe Agent
 ****************************************************************************/
#ifndef AGENT_H
#define AGENT
#include "door.h"

class Agent {

public:
	Agent(void);
	~Agent(void);

	void openDoor(string fileName);
	

private:
	vector<Door*> path_;


};

#endif // ! AGENT_H