#pragma once
#ifndef _MAGAZIN_
#define _MAGAZIN_

#include<iostream>
#include "heap.h"
#include "AVL.h"
#define maxNr 200000


struct zi {
	int nrZi;
	int nrVizite;
};

template<typename T>
class Magazin {
	int storeId;
	double storeX, storeY;
	AVLnode<T> *root;
	struct zi *zile;
	Heap<double> *distante;
	Heap<int> *discount;

public:
	Magazin();
	Magazin(int storeId, double storeX, double storeY);
	Magazin(const Magazin<T> &other);
	~Magazin();

	int getId();
	int setId(int newId);
	double getX();
	double getY();
	void setX(double newX);
	void setY(double newY);
	void quickSort(zi vector[365], int pinitial, int pfinal);


};

template<typename T>
Magazin<T>::Magazin() {
	this->storeId = 0;
	this->storeX = 0;
	this->storeY = 0;
	this->root = new AVLnode<T>();
	this->distante = new Heap<double>(maxNr, cmp);
	this->discount = new Heap<int>(maxNr, cmp);

	this->zile = new zi[366];
	for (int i = 1; i <= 365; i++) {
		this->zile[i].nrVizite = 0;
		this->zile[i].nrZi = i;
	}
}

template<typename T>
Magazin<T>::Magazin(int storeId, double storeX, double storeY) {
	this->storeId = storeId;
	this->storeX = storeX;
	this->storeY = storeY;
	this->root = new AVLnode<T>();
	this->distante = new Heap<double>(maxNr, cmp);
	this->discount = new Heap<int>(maxNr, cmp);

	this->zile = new zi[366];
	for (int i = 1; i <= 365; i++) {
		this->zile[i].nrVizite = 0;
		this->zile[i].nrZi = i;
	}
}

template<typename T>
Magazin<T>::Magazin(const Magazin<T> &other) {
	this->storeId = other->getId();
	this->storeX = other->getX();
	this->storeY = other->storeY();
	this->root = other->root;
	this->distante = other->distante;
	this->discount = other->discount;

	for (int i = 1; i <= 365; i++) {
		this->zile[i].nrVizite = other->zile[i].nrVizite;
		this->zile[i].nrZi = other->zile[i].nrZi;
	}
}

template<typename T>
Magazin<T>::~Magazin() {
	this->storeId = 0;
	this->storeX = 0;
	this->storeY = 0;
	this->root = NULL;
	delete[] zile;
	delete[] discount->H;
	delete[] distante->H;
}

template<typename T>
int Magazin<T>::getId() {
	return storeId;
}

template<typename T>
int Magazin<T>::setId(int newId) {
	this->storeId = newId;
}

template<typename T>
double Magazin<T>::getX() {
	return storeX;
}

template<typename T>
double Magazin<T>::getY() {
	return sotreY;
}

template<typename T>
void Magazin<T>::setX(double newX) {
	this->storeX = newX;
}

template<typename T>
void Magazin<T>::setY(double newY) {
	this->storeY = newY;
}

template<typename T>
void Magazin<T>::quickSort(zi vector[365], int pinitial, int pfinal) {
	int m = (pinitial + pfinal) >> 1;
	int i = pinitial;
	int j = pfinal;
	zi pivot = vector[m];

	while (i <= j)
	{
		while (vector[i].nrVizite<pivot.nrVizite)
			i++;
		while (pivot.nrVizite<vector[j].nrVizite)
			j--;

		if (i <= j)
		{
			zi temp = vector[i];
			vector[i] = vector[j];
			vector[j] = temp;
			i++;
			j--;
		}
	}
	if (pinitial<j)
	{
		quicksort(vector, pinitial, j);
	}
	if (i<pfinal)
	{
		quicksort(vector, i, pfinal);
	}
}
#endif
