#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Vecteur {
public:
	Vecteur();
	~Vecteur();
	T& operator [] (int i) { return(data[i]); }
	void operator += (T ajout);
	int taille;
	int capacite;


private:
	T* data;

	void doubler();
};

template <typename T>
Vecteur<T>::Vecteur() {
	capacite = 1;
	taille = 0;
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