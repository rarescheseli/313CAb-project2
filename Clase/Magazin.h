#pragma once

struct zi {
	int nrZi;
	int nrVizite;
};

class Magazin {
	int storeId;
	double storeX;
	double storeY;
	struct zi *zile;
	int heapCapacity;
	// AVLnode <int> *root;

	Heap <int> discount;
	Heap <double> distante;

public:
	Magazin();
	Magazin(int storeId, double storeX, double storeY, int heapCapacity);
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
	void visit(int timestamp, User client, int discount);
	void quickSort(int pinitial, int pfinal);
};

Array <int> Magazin::topKdays(int K) {
	Array < int > result;
	quickSort(1, 365);

	for (int i = 365; i > 0 && K > 0; --i) {
		if (zile[i].nrVizite > 0) {
			result.push_back(zile[i].nrZi);
			--K;
		}
	}

	return result;
}

Array <int> Magazin::topKdiscounts(int K) {
	Array <int> result;
	Heap < int > aux(discount);
	while (K > 0 && aux.size() > 1) {
		result.push_back(aux.extract());
		--K;
	}

	return result;
}

Array <double> Magazin::topKdistances(int K) {
	Array < double > result;
	Heap < double > aux(distante);
	while (K > 0 && aux.size() > 1) {
		result.push_back(aux.extract());
		--K;
	}

	return result;
}

void Magazin::visit(int timestamp, User client, int discount) {
	// TODO -> transformat timestamp in zi + bagat date in AVL
	double distance = sqrt( (client.getX() - storeX) * (client.getX() - storeX)
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
	//this->root = new AVLnode<T>();
	// this->distante = new Heap<double>(maxNr, cmpMax);
	// this->discount = new Heap<int>(maxNr, cmpMax);

	this->zile = new zi[366];
	for (int i = 1; i <= 365; i++) {
		this->zile[i].nrVizite = 0;
		this->zile[i].nrZi = i;
	}
}

Magazin::Magazin(int storeId, double storeX, double storeY, int heapCapacity) {
	this->storeId = storeId;
	this->storeX = storeX;
	this->storeY = storeY;
	this->heapCapacity = heapCapacity;
	
	//this->root = new AVLnode<int>();
	/*this->distante = new Heap<double>(maxNr, cmp);
	this->discount = new Heap<int>(maxNr, cmp);*/

	this->zile = new zi[366];
	for (int i = 1; i <= 365; i++) {
		this->zile[i].nrVizite = 0;
		this->zile[i].nrZi = i;
	}
}

Magazin::Magazin(const Magazin &other) {
	this->storeId = other.getId();
	this->storeX = other.getX();
	this->storeY = other.getY();
	this->distante = other.distante;
	this->discount = other.discount;
	this->heapCapacity = other.heapCapacity;
	// this->root = other->root;

	for (int i = 1; i <= 365; i++) {
		this->zile[i].nrVizite = other.zile[i].nrVizite;
		this->zile[i].nrZi = other.zile[i].nrZi;
	}
}

Magazin::~Magazin() {
	// if (root != NULL) {
	// 	delete root;
	// }
	delete[] zile;
	// delete distante;
	// delete discount;
}

void Magazin::quickSort(int pinitial, int pfinal) {
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
		quickSort(pinitial, j);
	}
	if (i < pfinal) {
		quickSort(i, pfinal);
	}
}

int Magazin::getId() const{
	return storeId;
}

double Magazin::getX() const{
	return storeX;
}

double Magazin::getY() const{
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