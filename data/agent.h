/****************************************************************************
 * Fichier:			agent.h
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Definition de la classe Agent
 ****************************************************************************/
#ifndef AGENT_H
#define AGENT
#include "automate.h"

class Agent {

public:
	Agent(bool inMaze=false):inMaze_(inMaze){};
	~Agent(void);

	void enterMaze();
	bool isInMaze() { return inMaze_; };
	void openDoor(const std::string& fileName);

	void clearPath();
	void printEvent();


private:
	std::vector<Door*>path_;
	std::vector<Automate*> automates_;
	std::string password_; // Concatenated password
	std::vector<Door*> event_;
	bool inMaze_;
};

#endif // ! AGENT_H