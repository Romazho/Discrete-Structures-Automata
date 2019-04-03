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
	Node * nullElem = new Node('E', true);	 

	for (size_t i = 0; i < rules.size(); ++i) 
	{
		auto it = find_if(nodeTree_.begin(), nodeTree_.end(), [rules, i](pair<Node*, vector<Edge*>> itNode) -> bool // Find 
		{
			return itNode.first->id_ == rules[i][0];
		});

		Node* node = nullptr;

		if (it == nodeTree_.end()) // If no node has that name
		{
			node = new Node(rules[i][0], true);
		}

		else // If this node already exist
		{
			node = it->first;
		}

		switch(rules[i].size())
		{
		case 3: // _->
			{
				Edge * edge = new Edge(node, nullElem, '0'); // In ASCII 00 is null caracter
				nodeTree_.insert(node, edge);
				break;
			}
		case 4: // _->_
			{
				Edge * edge = new Edge(node, nullElem, rules[i][3]); 
				nodeTree_.insert(node, edge);
				break;
			}
		case 5: // _->_ _
			{
				auto childIt = find_if(nodeTree_.begin(), nodeTree_.end(), [rules, i](pair<Node*, vector<Edge*>> itNode)-> bool
				{
					return itNode.first->id_ == rules[i][4];
				});
				Node* child = nullptr;

				if (childIt == nodeTree_.end())
				{
					child = new Node(rules[i][4], true);
				}

				else
				{
					child = childIt->first;
				}

				Edge * edge = new Edge(node, child, rules[i][3]); 

				node->isFinal_ = false;	
				node->childs_.push_back(child);
				nodeTree_.insert(node, edge);
				break;
			}
		}
	}

	for (size_t i = 0; i < door_->getPasswords().size(); i++) 
	{
		toValidate_.push_back(door_->getPasswords()[i]);
	}

	validatePasswords();
}

void Automate::validatePasswords() 
{
	if(door_->getDoorName() != "Boss")
	{
		for (size_t i = 0; i < toValidate_.size(); i++) 
		{
			validatePassword(toValidate_[i]);
		}
	}

	else
	{
		validatePassword(door_->getPasswords().front());
	}
}

void Automate::validatePassword(const string& password)
{
	//Password already validated when the door was built
	if (password.empty())
		return;

	vector<Edge*> startEdges = nodeTree_.at('S'); // Always start from 'S'
	char actualState = 'S';
	char precedentState = 'S';

	int pathLength = 0;
	for (size_t i = 0; i < password.size(); i++) {

		bool trouvee = findLetter(password[i], pathLength, startEdges, actualState, precedentState);

		// If letter found find next
		if (trouvee == true) {
			//Give id of next state
			if (actualState != 'E') {
				startEdges = nodeTree_.at(actualState);
			}
		}
		// If not found exit; 
		else {
			break;
		}

	}

	// If everything ok validate password
	// Verify if there is a path to final state 

	if ( (pathLength == password.size())  && ((actualState == 'E') || (actualState == 'S')) ) {

		if (actualState == 'S') {
			vector<Edge*> Edges = nodeTree_.at('S');
			auto it = find_if(Edges.begin(), Edges.end(), [](Edge* edge) {return edge->value_ == '0'; });
			if (it != Edges.end()) {
				door_->getDoorName() == "Boss" ? door_->validateBossDoor() : door_->validate(password);
				lastNode_ = actualState;
			}

		}
		else {
			
			// Return node before 'E'
			door_->getDoorName() == "Boss" ? door_->validateBossDoor() : door_->validate(password);
			lastNode_ = precedentState;
		
		}
	}

	
}

bool Automate::findLetter(const char& lettre, int& pathLength, vector<Edge*>& startEdges, char& actualState, char& precedentState) {

	// Iteration on all edges from start node
	for (size_t i = 0; i < startEdges.size(); i++) {

		// If good path is found
		// Verification is destination is different from actual state
		if ( (startEdges[i]->value_ == lettre) && (startEdges[i]->src_->id_ == actualState) ) {

			precedentState = startEdges[i]->src_->id_;
			actualState = startEdges[i]->dest_->id_;
			pathLength++;
			return true;
		}
	}
	return false;
}
