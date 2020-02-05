#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Vecteur {
public:
	Vecteur();
	~Vecteur();
	int getTaille() { return taille; }
	int getCapacite() { return capacite; }
	int getCourant() { return courant; }
	T & operator [] (int i) { return(data[i]); }
	void operator += (T ajout);
	Vecteur & operator ++ ();
	Vecteur & operator -- ();
	ostream & afficher(int index, ostream & s);
	friend ostream & operator <<(ostream & s, const Vecteur<T>& vct);


private:
	T* data;
	int taille;
	int capacite;
	int courant;
	void doubler();
};

template <typename T>
Vecteur<T>::Vecteur() {
	capacite = 1;
	taille = 0;
	courant = 0;
	data = new T[capacite];
	(*this)[0] = 0;
}

template <typename T>
Vecteur<T>::~Vecteur() {
	delete[] data;
}

template <typename T>
void Vecteur<T>::operator+=(T ajout) {
	if (taille >= capacite) {
		doubler();
	}
	(*this)[taille++] = ajout;
}

template <typename T>
void Vecteur<T>::doubler() {
	capacite = capacite * 2;
	T* buffer = new T[capacite];
	for (int i = 0; i <= taille; i++) {
		*(buffer + i) = *(data + i);
	}
	
	for (int i = taille + 1; i <= capacite - 1; i++) {
		*(buffer + i) = 0;
	}
	
	data = buffer;
}

template <typename T>
Vecteur<T>& Vecteur<T>::operator ++ () {
	if (courant < taille)
		++courant;
	return *this;
}

template <typename T>
Vecteur<T>&  Vecteur<T>::operator -- () {
	if (courant > 0)
		--courant;
	return *this;
}

template <typename T>
ostream & Vecteur<T>::afficher(int index, ostream & s) {
	if (T == DonneesTest) {
		s << "Type test: " << T.typeTest << endl
			<< "Adresse switches: " << T.registreSW << endl
			<< "Retour switches: " << dec << T.retourSW << "(" << hex << T.retourSW << ")" << endl
			<< "Etat switches: " << dec << T.etatSW << "(" << hex << T.etatSW << ")" << endl
			<< "Adresse leds: " << T.registreLD << endl
			<< "Valeur leds: " << dec << T.valeurLD << "(" << hex << T.valeurLD << ")" << endl
			<< "Etat leds: " << dec << T.etatLD << "(" << hex << T.etatLD << ")" << endl
	}
	return s;
}

template <typename T>
ostream & operator <<(ostream & s, const Vecteur<T>& vct) {
	for (int i = 0; i <= taille; i++) {
		vct.afficher(i, &s);
	}
	return s;
}