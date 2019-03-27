/****************************************************************************
 * Fichier:			automate.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implémentation de la classe Automate
 ****************************************************************************/
#include "automate.h"
using namespace std;

void Automate::generateAutomate()
{
	//Acces aux rules
	vector<string> rules = door_->getRules();
	Node * starter = new Node('S', false);
	Node * nullElem = new Node('NE', true);
	// A continuer avec starter 

	for (size_t i = 1; i < rules.size(); ++i) {
		//vérifier si le node existe deja sinon on crée un nouveau node.
		auto it = find_if(nodeTree.begin(), nodeTree.end(), [rules, i](Node* node) {node->id_ == rules[i][0]; }); // Possible erreur ici, si oui mettre une pair
		Node* node = nullptr; 
		if (it == nodeTree.end()) {
			node = new Node(rules[i][0], true);
		}
		else {
			node = it->first;
		}
		
		if (rules[i].size() == 3) 
		{
			Edge * edge = new Edge(node, nullElem, ' '); // on met un espace pour l'instant ATTTTTTTTTTTTTTTEEEEENNNTIOOOOON ! lol 
			nodeTree.insert({ node,edge });
		}

		else if (rules[i].size() == 4)
		{
			Edge * edge = new Edge(node, nullElem, rules[i][3]); // Verifier si final
			nodeTree.insert({ node,edge });
		}

		else
		{

			auto it = find_if(nodeTree.begin(), nodeTree.end(), [rules, i](Node* node) {node->id_ == rules[i][4]; });
			Node* child = it->first; // marche pas 
			if (it == nodeTree.end()) {
				child = new Node(rules[i][4], true);
			}
			Edge * edge = new Edge(node, child, rules[i][3]); // Verifier si final
			node->isFinal_ = false;
			nodeTree.insert({ node,edge });
		}

	}
	
}

/**
 * \brief 
 * \param door Door to generate password and validate
 */
void Automate::validatePasswords()
{
	//TODO : implement this function
	//string genPassword;
	//genPassword = "c";
	//door->validate(genPassword);
}
