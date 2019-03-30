/****************************************************************************
 * Fichier:			NodeTree.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			29 mars 2019
 * Description:		Implémentation de la classe NodeTree 
 ****************************************************************************/

#include"nodeTree.h"
using namespace std;
map<Node*,vector<Edge*>>::iterator NodeTree::find(Node* node)
{
	return nodeTree_.find(node);
}

/**
 * \brief Find a Node by id
 * \return std::map<Node*, Edge*>::iterator on the Node if found
 */
map<Node*, vector<Edge*>>::iterator NodeTree::find(const char& id)
{
	return find_if(nodeTree_.begin(), nodeTree_.end(), [id](pair<Node*, vector<Edge*>> pair)
	{
		return pair.first->id_ == id;
	});
}

vector<Edge*> NodeTree::at(const char& id)
{
	//ca ne marche pas.
	auto it = find(id);
	if (it != nodeTree_.end())
	{
		return it->second;
	}
	/// Declarer autre chose pour un autre return
}

std::vector<Edge*> NodeTree::at(Node* node)
{
	return nodeTree_.at(node);
}

void NodeTree::insert(Node* node, Edge* edge)
{
	auto it = find(node);

	if (it == nodeTree_.end()) // First time inserting
	{
		vector<Edge*> vector;
		vector.push_back(edge);
		nodeTree_.insert(make_pair(node, vector));
	}

	else // Key exist. Insert at key
	{
		it->second.push_back(edge);
	}
}

std::map<Node*, std::vector<Edge*>>::iterator NodeTree::begin()
{
	return nodeTree_.begin();
}

std::map<Node*, std::vector<Edge*>>::iterator NodeTree::end()
{
	return nodeTree_.end();
}

