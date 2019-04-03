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
	/*Constructors*/
	Automate(void) = default;
	Automate(Door* door) : door_(door) { generateAutomate(); };
	
	/*Getters*/
	Door* getDoor() { return door_; };
	char getLastNode() const { return lastNode_; };

	/*Others*/
	void validatePasswords();
	void validatePassword(const std::string& password);
	bool findLetter(const char& lettre, int& longueur, std::vector<Edge*>& startEdges, char& actualState, char& precedentState);



  private:
	Door* door_; // Door associated with the automate
	NodeTree nodeTree_;
	char lastNode_;
	std::vector<std::string> toValidate_; 

	void generateAutomate();
};

#endif // !AUTOMATE_H