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

class Automate
{
  public:
	Automate(void) = default;
	Automate(Door* door) : door_(door) { generateAutomate(); };
	void generateAutomate();
	void validatePasswords();

  private:
	  
	 Door* door_;
	 std::vector<std::string> toValidate;
	 std::multimap<Node*,Edge*> nodeTree;

};

struct Node {
	Node(const char& id, bool isFinal) : id_(id), isFinal_(isFinal) {};
	char id_;
	bool isFinal_;
	std::vector<Node*> childs_;
};

struct Edge{
	Edge(Node* src, Node* dest, char value) :src_(src), dest_(dest), value_(value) {};
	Node* src_;
	Node* dest_;
	char value_; //traiter le cas du char vers string
};

#endif // !AUTOMATE_H