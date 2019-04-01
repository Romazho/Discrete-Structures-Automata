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
	Door* getDoor() { return door_; };

	void validatePasswords();
	char getLastNode() const { return lastNode_; };
	void validatePassword(const std::string& password);
	bool trouverLettre(const char& lettre, int& longueur, std::vector<Edge*>& startEdges, char& etatActuel, char& etatPrecedent);
	


  private:
	/*Attributes*/
	Door* door_; // Door associated with the automate
	std::vector<std::string> toValidate_; //était vide
	NodeTree nodeTree_;
	char lastNode_;
	/*Private functions*/
	
};

#endif // !AUTOMATE_H