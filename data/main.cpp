/****************************************************************************
 * Fichier:			main.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Execute le programme
 ****************************************************************************/
#include "agent.h"
#include "door.h" // A Enlever
using namespace std;
void printMenu(void);

int main(void) {

	setlocale(LC_CTYPE, "fra"); //Afficher les caract�res francais
	char selection = '0';

	cout << "BIENVENUE DANS LE JEUX 'Dont vous êtes le héros' ! \n \n>>> Faite votre sélection parmis le menu suivant. \n";
	Agent agent;
	while (selection != 'd') {

		printMenu();
		cout << "\nChoix : ";
		cin >> selection;

		switch (selection) {

			
		case 'a': // Entrer dans le lab
			if (agent.isInMaze())
				cout << "Vous êtes déjà dans le labyrinthe";
			else
				agent.enterMaze();
			break;

		case 'b':
			if (!agent.isInMaze())
			{
				cout << "Vous devez tout d'abord entrer dans le labyrinthe";
				break;
			}

			cout << "\t\t\n Ouvrir la porte : ";
			
			while(true){
				string doorSelection;
				cin >> doorSelection;
				try
				{
					if (doorSelection == "boss")
						agent.openDoor(doorSelection + ".txt");
					else
						agent.openDoor("Porte" + doorSelection + ".txt"); // if exception will ask again
					break; // if no exception
				}
				catch (invalid_argument& ia) { cout << ia.what(); }
			}
			break;

		case 'c':
				agent.printEvent();
			break;

		case 'd':


			break;

		default:
			cout << "\n ATTENTION : Mauvaise sélection.Aucune autre selection que{ a,b,c,d } ne sera valide pour ce menu \n";
		}
	}
}

void printMenu(void) {

	cout << endl << "------------------------------------------------------------------------" << endl << endl;
	cout << "(a) Entrer dans le labyrinthe." << endl
		<< "(b) Ouvrir une porte." << endl
		<< "(c) Afficher le chemin parcouru" << endl
		<< "(d) Quitter." << endl;
}