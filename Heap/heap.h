#pragma once

#include <iostream>

template <typename T>
class Heap {
private:
    T* H;
    int dimension;
    int capacity;

    // pointer la o functie care comparara doua elemente
    int (*cmp)(const T&, const T&);
    int parent(int pos);
    int leftSubtree(int pos);
    int rightSubtree(int pos);
    int pushUp(int pos);
    int pushDown(int pos);
public:
    Heap(int capacity, int (*compare)(const T&, const T&));
    ~Heap();

    int size();
    T getValue(int pos);

    // returneaza pozitia pe care se afla elementul in heap dupa ce a fost inserat
    int insert(T x);

    T peek();
    T extractMax();

    // updatez valoarea de pe pozitia pos (pastrand proprietatea de heap)
    // si intoarece noua pozitie din heap
    int update(int pos, T newData);
};

template <typename T>
int Heap <T> :: update(int pos, T newData) {
    H[pos] = newData;
    if (pos > 1 && cmp(H[pos], H[parent(pos)])) {
        return pushUp(pos);
    } else {
        return pushDown(pos);
    }
}

template <typename T>
T Heap <T> :: getValue(int pos) {
    return H[pos];
}

template <typename T>
int Heap <T> :: size() {
    return dimension;
}

template <typename T>
Heap <T> :: Heap(int capacity, int (*compare)(const T&, const T&)) {
    cmp = compare;
    dimension = 0;
    H = new T[capacity];
    this->capacity = capacity;
}

template <typename T>
Heap <T> :: ~Heap() {
    delete[] H;
}

template <typename T>
int Heap <T> :: parent(int pos) {
    return ((pos - 1) >> 1);
}

template <typename T>
int Heap <T> :: leftSubtree(int pos) {
    return (pos << 1) + 1;
}

template <typename T>
int Heap <T> :: rightSubtree(int pos) {
    return (pos << 1) + 2;
}

template <typename T>
int Heap <T> :: pushUp(int pos) {
    while ( pos > 0 && cmp(H[pos], H[parent(pos)]) ) {
        T aux = H[pos];
        H[pos] = H[parent(pos)];
        H[parent(pos)] = aux;
        pos = parent(pos);
    }

    return pos;
}

template <typename T>
int Heap <T> :: pushDown(int pos) {
    while (1) {
        int rightSon = rightSubtree(pos);
        int leftSon = leftSubtree(pos);
        if (rightSon > dimension) { // daca nu am fiu dreapta
            if (leftSon > dimension) { // daca nu am fiu stanga
                break;
            } else if ( cmp(H[leftSon], H[pos]) ) {
                T aux = H[pos];
                H[pos] = H[leftSon];
                H[leftSon] = aux;
                pos = leftSon;
            } else {
                break;
            }
        } else {
            if (H[leftSon] <= H[rightSon] && cmp(H[leftSon], H[pos])) {
                T aux = H[pos];
                H[pos] = H[leftSon];
                H[leftSon] = aux;
                pos = leftSon;
            } else if (H[rightSon] <= H[leftSon] && cmp(H[rightSon], H[pos])) {
                T aux = H[pos];
                H[pos] = H[rightSon];
                H[rightSon] = aux;
                pos = rightSon;
            }
        }
    }

    return pos;
}

template <typename T>
int Heap <T> :: insert(T x) {
    if (capacity == dimension) {
        std::cerr << "Heapul e plin!\n";
        return -1;
    }

    H[dimension++] = x;
    return pushUp(dimension - 1);
}

template <typename T>
T Heap <T> :: peek() {
    if (dimension == 0) {
        std::cerr << "Heapul e gol! \n";
        T x;
        return x;
    }

    return H[0];
}

template <typename T>
T Heap <T> :: extractMax() {
    if (dimension == 0) {
        std::cerr << "Heapul e gol! \n";
        T x;
        return x;
    }

    T maxim = H[0];
    H[0] = H[--dimension];

    if (dimension > 0) {
        pushDown(0);
    }

    return maxim;
}
