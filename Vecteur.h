#pragma once
#include <iostream>
#include "MonInterface.h"
#include "VisiTest.h"

using namespace std;

template <typename T>
class Vecteur {
public:
	Vecteur();
	~Vecteur();
	int getTaille() { return taille; }
	int getCapacite() { return capacite; }
	bool estVide() { return (taille == 0); }
	void vider();
	T & operator [] (int i) { return(data[i]); }
	void operator += (T ajout); 
	Vecteur & operator ++ ();
	Vecteur & operator -- ();
	ostream & afficher(int index, ostream & s) { return s;  }
	//friend ostream & operator << <T>(ostream & s, const Vecteur<T>& vct);

	int courant;
	bool mode; //0 = pile, 1 = file

private:
	T* data;
	int taille;
	int capacite;
	void doubler();
};

template <typename T>
Vecteur<T>::Vecteur() {
	capacite = 1;
	taille = 0;
	courant = 0;
	data = new T[capacite];
	//(*this)[0] = 0;
}

template <typename T>
Vecteur<T>::~Vecteur() {
	delete[] data;
}

template <typename T>
void Vecteur<T>::vider() {
	capacite = 1;
	taille = 0;
	courant = 0;
	delete [] data;
	data = new T[capacite];
}

template <typename T>
void Vecteur<T>::operator+=(T ajout) {
	if (taille >= capacite) {
		doubler();
	}
	//(*this)[taille++] = ajout;
	if (mode) {
		data[taille++] = ajout;
	}
	else {
		for (int i = taille; i > 0; i--) {
			data[i - 1] = data[i];
		}
		data[0] = ajout;
	}
}

template <typename T>
void Vecteur<T>::doubler() {
	capacite = capacite * 2;
	T* buffer = new T[capacite];
	for (int i = 0; i <= taille; i++) {
		*(buffer + i) = *(data + i);
	}
	data = buffer;
}

template <typename T>
Vecteur<T>& Vecteur<T>::operator ++ () {
	if (courant < taille - 1)
		++courant;
	return *this;
}

template <typename T>
Vecteur<T>&  Vecteur<T>::operator -- () {
	if (courant > 0)
		--courant;
	return *this;
}


template <>
ostream & Vecteur<DonneesTest>::afficher(int index, ostream & s) {
	
	s << "Type test: " << (*this)[index].typeTest << endl
		<< "Adresse switches: " << (*this)[index].registreSW << endl
		<< "Retour switches: " << dec << (*this)[index].retourSW << "(" << hex << (*this)[index].retourSW << ")" << endl
		<< "Etat switches: " << dec << (*this)[index].etatSW << "(" << hex << (*this)[index].etatSW << ")" << endl
		<< "Adresse leds: " << (*this)[index].registreLD << endl
		<< "Valeur leds: " << dec << (*this)[index].valeurLD << "(" << hex << (*this)[index].valeurLD << ")" << endl
		<< "Etat leds: " << dec << (*this)[index].etatLD << "(" << hex << (*this)[index].etatLD << ")\n" << endl;
	
	
	return s;
	
}



template <typename T>
ostream & operator << (ostream & s, const Vecteur<T>& vct) {
	for (int i = 0; i <= taille; i++) {
		vct.afficher(i, &s);
	}
	return s;
}
