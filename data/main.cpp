
#include <iostream>
#include "agent.h"
#include "door.h" // A Enlever

void printMenu(void);

int main() {

	setlocale(LC_CTYPE, "fra"); //Afficher les caract�res francais
	char selection = '0';

	cout << "BIENVENUE DANS LE JEUX 'Dont vous �tes le h�ros' ! \n \n>>> Faite votre s�lection parmis le menu suivant. \n";
	Door fooDoor(2);
	while (selection != 'd') {

		printMenu();
		cout << "\nChoix : ";
		cin >> selection;



		switch (selection) {

			
		case 'a':

			
			break;

		case 'b':

			
			break;

		case 'c':

			break;

		case 'd':


			break;

		default:
			cout << "\n ATTENTION : Mauvaise s�lection.Aucune autre selection que{ a,b,c,d } ne sera valide pour ce menu \n";
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