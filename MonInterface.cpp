/*
*   Voir fichier d'entête pour informations.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: MonInterface.cpp 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2013 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#include <QStyleFactory>
#include "MonInterface.h"
#include "CommunicationFPGA.h"

MonInterface::MonInterface(const char * theName) : VisiTest(theName)
{
	donnee.typeTest = 0;
	donnee.registreSW = 8;
	donnee.retourSW = 1;

	donnee.registreLD = 10;
	donnee.valeurLD = 1;

	donnee.etatLD = 1;
	donnee.etatSW = 1;

	resetTest();
	resetArchive();

	archiver = 0;
	mode = 1;
}

void MonInterface::testSuivant()
{
	CommunicationFPGA fpga;
	int nbSW = 0;
	int nlc;
	int buffer;

	donnee.typeTest += 1;
	if (donnee.typeTest > 3)
		donnee.typeTest = 1;
	
	fpga.lireRegistre(donnee.registreSW , donnee.retourSW);
	donnee.etatSW = donnee.retourSW;

	switch (donnee.typeTest)
	{
	case 1 : 
		donnee.valeurLD = donnee.retourSW;
		break;
	case 2 : 
		buffer = donnee.retourSW;
		
		while (buffer > 0)
		{
			nbSW += buffer & 1;
			buffer >>= 1;
		}
		if (nbSW % 2)
		{
			donnee.valeurLD = 0;
		}
		else
		{
			donnee.valeurLD = 0xFF;
		}
		
		break;
	case 3 :
		donnee.valeurLD = 0;

		nlc = round(log2(donnee.retourSW + 1));
		for (nlc; nlc > 0; nlc--) {
			donnee.valeurLD <<= 1;
			donnee.valeurLD |= 1;
		}
		
		break;
	default:
		break;

	}
	fpga.ecrireRegistre(donnee.registreLD, donnee.valeurLD);
	donnee.etatLD = donnee.valeurLD;
	setTest(donnee);
	//Gestion archive
	if (archiver)
	{
		archive += donnee;
		setArchive(donnee);
		if (mode){
			archive.courant = archive.getTaille();
		}
		else{
			archive.courant = 1;
		}
		setArchive(archive.courant, archive.getTaille());
		message("Test archivé");
	}
		
}


void MonInterface::demarrer() {
	archiver = 1;
	message("Archive activée");
}


void MonInterface::arreter() {
	archiver = 0;
	message("Archive désactivée");
}
void MonInterface::vider(){
}
void MonInterface::modeFile(){
	if (archive.estVide()) {
		mode = 1;
		message("Mode file");
	}
	else{
		message("Le mode peut seulement être changé si l'archive est vide.");
	}
}
void MonInterface::modePile(){
	if (archive.estVide()) {
		mode = 0;
		message("Mode Pile");
	}
	else {
		message("Le mode peut seulement être changé si l'archive est vide.");
	}
}

void MonInterface::premier() {
	if (mode) {
		archive.courant = 0;
		setArchive(archive[archive.courant]);
		setArchive(archive.courant + 1, archive.getTaille() + 1);
	}
	else {
		archive.courant = archive.getTaille();
		setArchive(archive[archive.courant]);
		setArchive(1, archive.getTaille());
	}
}

void MonInterface::dernier(){
	if (mode) {
		archive.courant = archive.getTaille();
		setArchive(archive[archive.courant]);
		setArchive(archive.courant + 1, archive.getTaille() + 1);
	}
	else {

	}
}

void MonInterface::precedent(){
	if (mode) {
		--archive;
		setArchive(archive[archive.courant]);
		setArchive(archive.courant + 1, archive.getTaille() + 1);
	}
	else {

	}
}

void MonInterface::suivant(){
	if (mode) {
		++archive;
		setArchive(archive[archive.courant]);
		setArchive(archive.courant + 1, archive.getTaille() + 1);
	}
	else {

	}
}

void MonInterface::sauvegarder(char *nomFichier) {

}
