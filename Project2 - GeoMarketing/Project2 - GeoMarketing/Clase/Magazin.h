#pragma once

#include "../SD//AVL.h"
#include "../SD/Array.h"
#include "../SD/heap.h"
#include "User.h"
#include <iostream>
#include <algorithm>

#define MAX_AIB2 10005

using namespace std;

struct zi {
	int nrZi;
	int nrVizite;
};

class Magazin {
	int *aib;
	bool firstVisit;
	int storeId;
	double storeX;
	double storeY;
	struct zi zile[366], aux[366];
	int minTimestamp;
	int maxTimestamp;

	Heap <int> discount;
	Heap <double> distante;

	void updateVizite(int pos) {
		while (pos <= MAX_AIB2) {
			++aib[pos];
			pos += -pos & pos;
		}
	}

	int queryVizite(int pos) {
		int res = 0;
		while (pos) {
			res += aib[pos];
			pos -= -pos & pos;
		}

		return res;
	}

public:
	Magazin();
	Magazin(int storeId, double storeX, double storeY);
	Magazin(const Magazin &other);
	~Magazin();

	int getId() const;
	double getX() const;
	double getY() const;
	void setId(int newId);
	void setX(double newX);
	void setY(double newY);
	Array < int > topKdays(int K);
	Array < int > topKdiscounts(int K);
	Array < double > topKdistances(int K);
	int visitsInTimeframe(int start, int final);
	void visit(int timestamp, User client, int discount);
	void quickSort(int pinitial, int pfinal);
};

int Magazin::visitsInTimeframe(int start, int final) {
	++start; ++final;
	if (firstVisit == false || start > maxTimestamp || final < minTimestamp) {
		return 0;
	}

	int st = max(minTimestamp, start);
	int dr = min(maxTimestamp, final);

	return queryVizite(dr) - queryVizite(st - 1);
	return 0;
}

Array <int> Magazin::topKdays(int K) {
	Array < int > result;
	for (int i = 0; i < 366; ++i) {
		aux[i] = zile[i];
	}
	quickSort(1, 365);

	for (int i = 365; i > 0 && K > 0; --i) {
		if (zile[i].nrVizite > 0) {
			result.push_back(zile[i].nrZi - 1);
			--K;
		}
	}

	return result;
}

Array <int> Magazin::topKdiscounts(int K) {
	Array <int> result;
	if (discount.size() <= 1) {
		return result;
	}
	Heap < int > aux=discount;
	while (K > 0 && aux.size() > 1) {
		result.push_back(aux.extract());
		--K;
	}

	return result;
}

Array <double> Magazin::topKdistances(int K) {
	Array < double > result;
	if (distante.size() <= 1) {
		return result;
	}
	Heap < double > aux=distante;
	while (K > 0 && aux.size() > 1) {
		result.push_back(aux.extract());
		--K;
	}

	return result;
}

void Magazin::visit(int timestamp, User client, int discount) {
	int zi = timestamp / 86400;
	if (timestamp % 86400 > 0) {
		++zi;
	}

	++zile[zi].nrVizite;
	if (firstVisit == false) {
		firstVisit = true;
	}

	updateVizite(timestamp);
	minTimestamp = min(minTimestamp, timestamp);
	maxTimestamp = max(maxTimestamp, timestamp);
	double distance = sqrt((client.getX() - storeX) * (client.getX() - storeX)
		+ (client.getY() - storeY) * (client.getY() - storeY));
	distante.insert(distance);

	if (discount != -1) {
		this->discount.insert(discount);
	}
}

Magazin::Magazin() {
	this->storeX = 0;
	this->storeY = 0;
	this->storeId = 0;
	firstVisit = false;
	aib = new int[MAX_AIB2]();

	maxTimestamp = -1;
	minTimestamp = 2147483647;

	for (int i = 1; i <= 365; i++) {
		this->zile[i].nrVizite = 0;
		this->zile[i].nrZi = i;
	}
}

Magazin::Magazin(int storeId, double storeX, double storeY) {
	this->storeId = storeId;
	this->storeX = storeX;
	this->storeY = storeY;
	firstVisit = false;
	aib = new int[MAX_AIB2]();

	maxTimestamp = -1;
	minTimestamp = 2147483647;

	for (int i = 1; i <= 365; i++) {
		this->zile[i].nrVizite = 0;
		this->zile[i].nrZi = i;
	}
}

Magazin::Magazin(const Magazin &other) {
	this->storeId = other.getId();
	this->storeX = other.getX();
	this->storeY = other.getY();
	this->minTimestamp = other.minTimestamp;
	this->maxTimestamp = other.maxTimestamp;
	this->distante = other.distante;
	this->discount = other.discount;

	for (int i = 1; i <= 365; i++) {
		this->zile[i].nrVizite = other.zile[i].nrVizite;
		this->zile[i].nrZi = other.zile[i].nrZi;
	}

	for (int i = 0; i < MAX_AIB2; ++i) {
		this->aib[i] = other.aib[i];
	}
}

Magazin::~Magazin() {
	//delete[] aib;
}

void Magazin::quickSort(int pinitial, int pfinal) {
	int m = (pinitial + pfinal) >> 1;
	zi pivot = aux[m];
	int i = pinitial;
	int j = pfinal;

	while (i <= j) {
		while (aux[i].nrVizite < pivot.nrVizite)
			i++;
		while (pivot.nrVizite < aux[j].nrVizite)
			j--;

		if (i <= j) {
			zi temp = aux[i];
			aux[i] = aux[j];
			aux[j] = temp;
			i++;
			j--;
		}
	}
	if (pinitial < j) {
		quickSort(pinitial, j);
	}
	if (i < pfinal) {
		quickSort(i, pfinal);
	}
}

int Magazin::getId() const {
	return storeId;
}

double Magazin::getX() const {
	return storeX;
}

double Magazin::getY() const {
	return storeY;
}

void Magazin::setId(int newId) {
	this->storeId = newId;
}

void Magazin::setX(double newX) {
	this->storeX = newX;
}

void Magazin::setY(double newY) {
	this->storeY = newY;
}