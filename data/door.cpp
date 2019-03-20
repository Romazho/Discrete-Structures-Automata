/****************************************************************************
 * Fichier:			door.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Door
 ****************************************************************************/

#include "door.h"

Door::Door(unsigned doorNumber) {
	doorName_ = "Porte" + std::to_string(doorNumber) + ".txt";
}

bool Door::readFile() {
	file_.open(doorName_,ios::in);
	string line;
	
	while (!file_.eof()){
		getline(file_, line);

		if (line == "{") { // Ajouter des règles
		
			while (true){
				file_ >> line;
				if (line.back() == ',')
					line.erase(line.size() - 1);
				if (line.back() == '}')
					break;
				rules_.push_back(line);
				
			}
		}
	}

	return file_.is_open();
}

