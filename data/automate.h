/****************************************************************************
 * Fichier:			automate.h
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Definition de la classe Automate
 ****************************************************************************/

#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "door.h"


class Automate {
public:
	Automate(Door * door = nullptr);

private:
	Door* door_; // Agrégation
};
#endif // !AUTOMATE_H