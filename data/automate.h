/****************************************************************************
 * Fichier:			automate.h
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Definition de la classe Automate
 ****************************************************************************/

#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "door.h"
#include "nodeTree.h"


class Automate
{
  public:
	Automate(void) = default;
	Automate(Door* door) : door_(door) { generateAutomate(); };
	void generateAutomate();

	void validatePasswords();
	void validatePassword(const string& password);
	bool trouverLettre(const char& lettre, int& longueur, vector<Edge*>& startEdges, char& etatActuel);

  private:
	/*Attributes*/
	Door* door_; // Door associated with the automate
	std::vector<std::string> toValidate_; //
	NodeTree nodeTree_;
	/*Private functions*/
	
};

#endif // !AUTOMATE_H