/****************************************************************************
 * Fichier:			door.h
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Definition de la classe Door
 ****************************************************************************/

#ifndef DOOR_H
#define DOOR_H
#include <fstream>

#include <vector>
#include <string>

using namespace std;

class Door {

public:
	Door(void) = default;
	Door(unsigned doorNumber);
	~Door() { file_.close(); };

	bool readFile();
	string getDoorName() { return doorName_; };

private:
	string doorName_;
	vector<string> rules_;
	vector<string> passwords_;
	vector<string> nextDoors_;
	fstream file_;


};


#endif // !DOOR_H