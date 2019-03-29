/****************************************************************************
 * Fichier:			NodeTree.h
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			29 mars 2019
 * Description:		Definition de la classe NodeTree et de ses composantes
 ****************************************************************************/

#ifndef NODE_TREE_H
#define NODE_TREE_H

#include <map>
#include <vector>
#include <algorithm>

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


class NodeTree
{
public:
	std::map<Node*, std::vector<Edge*>>::iterator find(const char& id);
	std::map<Node*, std::vector<Edge*>>::iterator find(Node* node);

	std::vector<Edge*> at(const char& id);
	std::vector<Edge*> at(Node* node);
	void insert(Node* node, Edge* edge);
	std::map<Node*, std::vector<Edge*>>::iterator begin();
	std::map<Node*, std::vector<Edge*>>::iterator end();

private:
	std::map<Node*, std::vector<Edge*>> nodeTree_;
};

#endif // !NODE_TREE_H