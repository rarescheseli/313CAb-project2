#pragma once
#include <utility>

using namespace std;

#define NMAX 300005

// cmpMax
template <typename T>
int cmpMax(pair<T, int> &elem1,pair<T, int> &elem2) {
    if (elem1.first > elem2.first) {
        return 1;
    }
    return 0;
}

// cmpMin
template <typename T>
int cmpMin(pair<T, int> &elem1,pair<T, int> &elem2) {
    if (elem1.first < elem2.first) {
        return 1;
    }
    return 0;
}

template <typename T>
class Heap {
private:
    int capacity;

    // position[i] = pozitia din heap pe care se afla elementul inserat al i-lea in ordine cronologica
    int *position;
    int dimension, index;
    Array < pair < T, int > > H;

	int parent(int pos) {
		return ((pos) >> 1);
	}

	void pushUp(int pos) {
		while (pos > 1 && cmp(H[pos], H[parent(pos)])) {
			Swap(pos, parent(pos));
			pos = parent(pos);
		}
	}
	void pushDown(int pos) {
		int son = leftSubtree(pos);
		if (son + 1 <= dimension && cmp(H[son + 1], H[son])) {
			++son;
		}

		if (son <= dimension && cmp(H[son], H[pos])) {
			Swap(pos, son);
			pushDown(son);
		}
	}

	int leftSubtree(int pos) {
		return (pos << 1);
	}
	int rightSubtree(int pos) {
		return (pos << 1) + 1;
	}

	void Swap(const int x, const int y) {
		swap(H[x], H[y]);
		swap(position[H[x].second], position[H[y].second]);
	}

    // pointer la o functie care comparara doua elemente
    int (*cmp)(pair <T, int> &, pair <T, int>&);
public:
	Heap() {
		index = 0;
		cmp = cmpMax;
		dimension = 0;
		this->capacity = NMAX;

		// adaug un element pe care nu-l accesez niciodata pentru a avea heapul indexat de la 1
		pair <T, int> aux;
		aux.second = -1;
		H.push_back(aux);
		position = new int[capacity];
	}

	Heap(int capacity, int(*compare)(const pair <T, int>&, const pair <T, int>&)) {
		index = 0;
		cmp = compare;
		dimension = 0;
		this->capacity = capacity + 1;

		// adaug un element pe care nu-l accesez niciodata pentru a avea heapul indexat de la 1
		pair <T, int> aux;
		aux.second = -1;
		H.push_back(aux);
		position = new int[capacity];
	}
	~Heap() {
		delete[] position;
	}

    // Copy constructor
	Heap(const Heap &other) {
		H = other.H;
		cmp = other.cmp;
		index = other.index;
		capacity = other.capacity;
		dimension = other.dimension;

		if (dimension > 0) {
			position = new int[capacity];
			for (int i = 0; i < other.dimension; ++i) {
				position[i] = other.position[i];
			}
		}
	}

	Heap &operator=(const Heap &other) {
		if (this != &other) {
			H = other.H;
			cmp = other.cmp;
			index = other.index;
			capacity = other.capacity;

			dimension = other.dimension;

			if (dimension > 0) {
				int *tmp = new int[other.capacity];
				for (int i = 0; i < other.dimension; ++i) {
					tmp[i] = other.position[i];
				}

				delete[] position;
				position = tmp;
			}
		}

		return *this;
	}

	T peek() {
		if (dimension == 0) {
			std::cerr << "Heapul e gol! \n";
			T x;
			return x;
		}

		return H[1].first;
	}

	int size() {
		return dimension + 1;
	}

	T extract() {
		if (dimension == 0) {
			std::cerr << "Heapul e gol! \n";
			return T();
		}

		T value = H[1].first;
		H[1] = H[dimension--];

		if (dimension > 1) {
			pushDown(1);
		}

		return value;
	}

	void insert(T x) {
		if (capacity == dimension - 1) {
			std::cerr << "Heapul e plin!\n";
			return;
		}

		position[++index] = ++dimension;
		H.push_back(make_pair(x, index));
		pushUp(dimension);
	}

    T getValue(int pos){
		return H[pos].first;
	}

    // updatez elementul care a fost inserat al k-lea in ordine cronologica
	void update(int k, T newData) {
		int pos = position[k];
		H[pos].first = newData;
		if (pos > 1 && cmp(H[pos], H[parent(pos)])) {
			return pushUp(pos);
		}
		else {
			return pushDown(pos);
		}
	}
};