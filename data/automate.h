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
#include <map>

struct Node {
	Node(const char& id, bool isFinal) : id_(id), isFinal_(isFinal) {};
	char id_;
	bool isFinal_;
	std::vector<Node*> childs_;
};

struct Edge {
	Edge(Node* src, Node* dest, char value) :src_(src), dest_(dest), value_(value) {};
	Node* src_;
	Node* dest_;
	char value_; ///traiter le cas du char vers string
};

class Automate
{
  public:
	Automate(void) = default;
	Automate(Door* door) : door_(door) { generateAutomate(); };
	void generateAutomate();
	void validatePasswords();

  private:
	/*Attributes*/
	Door* door_; // Door associated with the automate
	std::vector<std::string> toValidate_; //
	std::multimap<Node*,Edge*> nodeTree_;
	/*Private functions*/
	auto findStartIterator(); 
};

#endif // !AUTOMATE_H