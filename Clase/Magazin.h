#pragma once

#include <iostream>
#include <cmath>

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
	struct zi *zile;
	AVLnode <T> *root;

	// TODO -> de pus functie de cmp pt heap
	Heap <int> *discount;
	double storeX, storeY;

	// TODO -> de pus functie de cmp pt heap
	Heap <double> *distante;

public:
	Magazin();
	Magazin(int storeId, double storeX, double storeY);
	Magazin(const Magazin <T> &other);
	~Magazin();

	int getId();
	double getX();
	double getY();
	void setId(int newId);
	void setX(double newX);
	void setY(double newY);
	Array < int > topKdays(int K);
	Array < int > topKdiscounts(int K);
	Array < double > topKdistances(int K);
	void visit(int timestamp, User client, int discount);
	void quickSort(int pinitial, int pfinal);
};

template < typename T >
Array < int > Magazin <T> :: topKdays(int K) {
	Array < int > result;
	quicksort(1, 365);

	for (int i = 365; i > 0 && K > 0; --i) {
		if (zile[i].nrVizite > 0) {
			result.push_back(zile[i].nrZi);
			--K;
		}
	}

	return result;
}

template <typename T>
Array < int > Magazin <T> :: topKdiscounts(int K) {
	Array < int > result;
	Heap < int > aux(discount);
	while (K > 0 && aux.size() > 0) {
		result.push_back(aux.extract());
		--K;
	}

	return result;
}

template < typename T>
Array < double > Magazin <T> :: topKdistances(int K) {
	Array < double > result;
	Heap < double > aux(distante);
	while (K > 0 && aux.size() > 0) {
		result.push_back(aux.extract());
		--K;
	}

	return result;
}

template <typename T>
void Magazin <T> :: visit(int timestamp, User client, int discount) {
	// TODO -> transformat timestamp in zi
	double distance = sqrt( (client.getX() - storeX) * (client.getX() - storeX)
						+ (client.getY() - storeY) * (client.getY() - storeY));

	distante.insert(distance);

	if (discount != -1) {
		this->discount.insert(discount);
	}
}

template<typename T>
Magazin <T> :: Magazin() {
	this->storeX = 0;
	this->storeY = 0;
	this->storeId = 0;
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
Magazin <T> :: Magazin(int storeId, double storeX, double storeY) {
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
Magazin <T> :: ~Magazin() {
	// Mai nevoie daca AVL-ul are destructorul lui ?
	this->root = NULL;
	delete[] zile;
	delete distante;
	delete discount;
}

template<typename T>
void Magazin <T> :: quickSort(int pinitial, int pfinal) {
	int m = (pinitial + pfinal) >> 1;
	zi pivot = zile[m];
	int i = pinitial;
	int j = pfinal;

	while (i <= j) {
		while (zile[i].nrVizite < pivot.nrVizite)
			i++;
		while (pivot.nrVizite < zile[j].nrVizite)
			j--;

		if (i <= j) {
			zi temp = zile[i];
			zile[i] = zile[j];
			zile[j] = temp;
			i++;
			j--;
		}
	}
	if (pinitial < j) {
		quicksort(pinitial, j);
	}
	if (i < pfinal) {
		quicksort(i, pfinal);
	}
}

template<typename T>
int Magazin <T> :: getId() {
	return storeId;
}

template<typename T>
void Magazin <T> :: setId(int newId) {
	this->storeId = newId;
}

template<typename T>
double Magazin <T> :: getX() {
	return storeX;
}

template<typename T>
double Magazin <T> :: getY() {
	return sotreY;
}

template<typename T>
void Magazin <T> :: setX(double newX) {
	this->storeX = newX;
}

template<typename T>
void Magazin <T> :: setY(double newY) {
	this->storeY = newY;
}