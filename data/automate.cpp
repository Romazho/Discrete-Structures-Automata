/****************************************************************************
 * Fichier:			automate.cpp
 * Auteurs: 		Kevin Ciliento, Gabriel Tagliabracci et Roman Zhornytskiy
 * Date:			20 mars 2019
 * Description:		Implémentation de la classe Automate
 ****************************************************************************/
#include "automate.h"
using namespace std;

/**
 * \brief 
 * \param door Door to generate password and validate
 */
void Automate::generatePasswords(Door* door)
{
	//TODO : implement this function
	string genPassword;
	genPassword = "c";
	door->validate(genPassword);
}
