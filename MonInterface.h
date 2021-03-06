/*
*   La classe MonInterface teste l'interface usager VisiTest (librairie).
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: MonInterface.h 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2016 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#ifndef MONINTERFACE_H
#define MONINTERFACE_H
#include "Vecteur.h"
#include "VisiTest.h"

class MonInterface : public VisiTest
{
public:
	MonInterface(const char *theName);
	virtual void sauvegarder(char *nomFichier);
public slots:
	virtual	void testSuivant();
	virtual void demarrer();
	virtual void arreter();
	virtual void vider();
	virtual void modeFile();
	virtual void modePile();

	virtual void premier();
	virtual void dernier();
	virtual void precedent();
	virtual void suivant();


private:
	DonneesTest donnee; //Contient le test actif
	Vecteur<DonneesTest> archive; //Contient les test archivées
	bool archiver; //0 = ne pas archiver les tests, 1 = archiver
};

#endif // MONINTERFACE_H