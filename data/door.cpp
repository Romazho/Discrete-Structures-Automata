/****************************************************************************
 * Fichier:			door.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implementation de la classe Door
 ****************************************************************************/

#include "door.h"

Door::Door(unsigned doorNumber) {
	doorName_ = "\\text_files\\" + std::to_string(doorNumber) + ".txt";
}