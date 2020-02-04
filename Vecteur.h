#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Vecteur {
public:
	Vecteur();
	~Vecteur();
	void nouveau();
	bool ajouter(T* ajout);
	int getCapacite();
	int getTaille();
	void vider();
	bool estVide();
	void afficher(ostream & s);
	

private:
	T** data;
	int capacite;
	int taille;
};

template <typename T>
Vecteur<T>::Vecteur() {
	nouveau();
}

template <typename T>
Vecteur<T>::~Vecteur() {
	vider();
	delete[] data;
}

template <typename T>
void Vecteur<T>::nouveau()
{
	capacite = 1;
	taille = 0;
	data = new T*[capacite];
	*data = 0;
}

template <typename T>
void Vecteur<T>::vider() {
	for (int i = 0; i <= taille; i++) {
		delete *(data + i);
	}
	delete[] data;
	nouveau();
}

template <typename T>
bool Vecteur<T>::estVide() {
	return (taille == 0);
}

template <typename T>
bool Vecteur<T>::ajouter(T* ajout)
{
	T** buffer;

	if (taille >= capacite) {
		capacite = 2 * capacite;
		buffer = new T*[capacite];
		for (int i = 0; i <= taille; i++) {
			*(buffer + i) = *(data + i);
		}
		for (int i = taille + 1; i <= capacite; i++) {
			*(buffer + i) = 0;
		}
		delete[] data;
		data = buffer;
	}
	*(data + taille++) = data;
	return true;
}