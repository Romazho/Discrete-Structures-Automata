/****************************************************************************
 * Fichier:			automate.h
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Definition de la classe Automate
 ****************************************************************************/

#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "door.h"
#include <algorithm>

class Automate
{
  public:
	Automate(const std::vector<std::string>& rule) : rule_(rule) {};
	void validateDoors(Door* door, Password password);

	void generatePasswords(Door* door);

  private:
	std::vector<std::string> rule_;


};
#endif // !AUTOMATE_H