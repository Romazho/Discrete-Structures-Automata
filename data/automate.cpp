/****************************************************************************
 * Fichier:			automate.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Impl�mentation de la classe Automate
 ****************************************************************************/
#include "automate.h"
using namespace std;


void Automate::validateDoors(Door* door, Password password)
{
	auto it = door->getDoorMap().begin();
	auto end = door->getDoorMap().end();
	if (find(it, end, password) != end)
		door->validate(it->second);
}

void Automate::generatePasswords(Door* door)
{
	//TODO : implement this function
	Password genPassword;
	validateDoors(door, genPassword);
}
