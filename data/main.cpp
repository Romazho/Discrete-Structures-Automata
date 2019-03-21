/****************************************************************************
 * Fichier:			main.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Execute le programme
 ****************************************************************************/
#include "agent.h"
#include "door.h" // A Enlever

void printMenu(void);

int main(void) {

	setlocale(LC_CTYPE, "fra"); //Afficher les caractères francais
	char selection = '0';

	cout << "BIENVENUE DANS LE JEUX 'Dont vous êtes le héros' ! \n \n>>> Faite votre sélection parmis le menu suivant. \n";
	Agent agent;
	while (selection != 'd') {

		printMenu();
		cout << "\nChoix : ";
		cin >> selection;



		switch (selection) {

			
		case 'a': // Entrer dans le lab
			agent.openDoor("Porte1.txt");
			break;

		case 'b':
			cout << "\t\t\n Ouvrir la porte : ";
			
			while(true){
				int doorSelection;
				cin >> doorSelection;
				try
				{
					agent.openDoor("Porte" + to_string(doorSelection) + ".txt"); // if exception will ask again
					break; // if no exception
				}
				catch (invalid_argument& ia) { cout << ia.what(); }
			}
			break;

		case 'c':

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