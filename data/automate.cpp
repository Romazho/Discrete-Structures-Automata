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
	//Node * starter = new Node('S', false);
	Node * nullElem = new Node('NE', true);

	for (size_t i = 0; i < rules.size(); ++i) {
		//vérifier si le node existe deja sinon on crée un nouveau node.
		{//il serait plus intelligent de vérifier si S->_A par exemple et si oui alors on crée le node A
		//car si S ne mene pas à A, il est alors inutile de créer le node A. mais je ne pense pas que
		//ca change quelque chose à la fin...
		}
		auto it = find_if(nodeTree_.begin(), nodeTree_.end(), [rules, i](pair<Node*, vector<Edge*>> itNode) -> bool {return itNode.first->id_ == rules[i][0]; }); // Possible erreur ici, si oui mettre une pair
		Node* node = nullptr;

		if (it == nodeTree_.end()) // If no node has that name
		{
			node = new Node(rules[i][0], true);
		}

		else // If this node already exist
		{
			node = it->first;
		}
		
		if (rules[i].size() == 3) // _->
		{
			Edge * edge = new Edge(node, nullElem, 00); // In ASCII 00 is null caracter

			nodeTree_.insert(node,edge);
		}
		
		else if (rules[i].size() == 4) // _->_
		{
			Edge * edge = new Edge(node, nullElem, rules[i][3]); // Verifier si final	//pas besoin car on est sur que c'est vrai tousjour.
			nodeTree_.insert(node,edge);
		}
		
		else // _->_ _
		{
			auto childIt = find_if(nodeTree_.begin(), nodeTree_.end(), [rules, i](pair<Node*,vector<Edge*>> itNode) {return itNode.first->id_ == rules[i][4]; });
			//Node* child = it->first; // marche pas 
			Node* child = nullptr;
			
			if (childIt == nodeTree_.end()) 
			{
				child = new Node(rules[i][4], true);
			}

			else
			{
				child = childIt->first;
			}
			
			Edge * edge = new Edge(node, child, rules[i][3]); // Verifier si final	//pas besoin car on est sur que c'est vrai tousjour.
			node->isFinal_ = false;
			node->childs_.push_back(child);
			nodeTree_.insert(node,edge);
		
		}
	}

	validatePasswords();
}

void Automate::validatePasswords() {

	for (int i = 0; i < toValidate_.size(); i++) {

		validatePassword(toValidate_[i]);

	}


}

/**
 * \brief Validate an confirmed password
 * \param password found by the Automate
 */
//on valide un password
void Automate::validatePassword(const string& password)
{
	//on commence tousjour de S
	vector<Edge*> startEdges = nodeTree_.at('S');

	int longueurChemin = 0;

	//fonction qui parcourt le chemin qui prend en paramètre la première lettre
	//et qui retourne un bool
	//on parcourt le chemin = password
	for (int i = 0; i < password.size(); i++) {

		bool trouvee = trouverLettre(password[i], longueurChemin, startEdges);

		//si on a trouvé la lettre alors on cherche la suivante.
		if (trouvee == true) {
			vector<Edge*> startEdges = nodeTree_.at(password[i]);
		}

	}


	//on valide le password si tout est correct
	//virifier si on se trouve à un état final
	if (longueurChemin == password.size()) {

		door_->validate(password);
	}

	
}


bool Automate::trouverLettre(const char& lettre, int& longueurChemin, vector<Edge*>& startEdges) {

	//on parcourt tous les edges du starter
	for (int i = 0; i < startEdges.size(); i++) {

		//si on a trouvé le bon chemin
		if ( (startEdges[i]->value_ == lettre) && (startEdges[i]->dest_->id_ != lettre) ) {

			longueurChemin++;
			return true;
		}
	}
	return false;
}
