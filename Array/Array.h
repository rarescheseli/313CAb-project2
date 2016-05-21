template<typename T>
struct Array {
    int _capacity;
    int resultSize;
    T* resultData;

    Array(int resultSize, T* resultData) :
        resultSize(resultSize), resultData(resultData) {}

    Array() {
        _capacity = 1;
        resultSize = 0;
        resultData = new T[1];
    }

    // Copy constructor
    Array(const Array &other) {
        _capacity = other._capacity;
        resultSize = other.size();

        if (resultSize > 0) {
            resultData = new T[_capacity];

            for (int i = 0; i < _capacity; ++i) {
                resultData[i] = other.resultData[i];
            }
        }
    }

    // Copy assignement operator
    Array &operator=(const Array &other) {
        if (this != &other) {
            resultSize = other.size();
            _capacity = other.capacity();
            T *tmp = new T[other.capacity()];

            for (int i = 0; i < other.size(); ++i) {
                tmp[i] = other.resultData[i];
            }

            delete[] resultData;
            resultData = tmp;
        }

        return *this;
    }

    ~Array() {
        delete[] resultData;
    }

    int size() const {
        return this->resultSize;
    }

    int capacity() const {
        return this->_capacity;
    }

    // Metoda care redimensioneaza array-ul la dimensiunea "newSize"
    void resize(int newSize);

    // Metoda care adauga un element nou
    void push_back(const T something);

    // Metoda pentru stergerea ultimului element adaugat
    void pop_back();

    // Metoda pentru "Subscripting operator" 
    T &operator[](int position);

    void quickSort(int pinitial, int pfinal);
};

template <typename T>
void Array<T>::resize(int newSize) {
    T *tmp = new T[newSize];

    int limit = (newSize < resultSize) ? newSize : resultSize;
    for (int i = 0; i < limit; ++i) {
        tmp[i] = resultData[i];
    }

    delete[] resultData;

    resultData = tmp;
    _capacity = newSize;
}

template <typename T>
void Array<T>::push_back(const T something) {
    // Verifica daca vectorul e plin
    if (resultSize == _capacity) {
        resize(_capacity << 1);
    }

    resultData[resultSize++] = something;
}

template <typename T>
void Array<T>::pop_back() {
    if (resultSize == 0) {
        cerr << "Array-ul este deja gol!\n";
        return;
    }

    resultSize--;
    /*if (resultSize == _capacity >> 1) {
        resize(_capacity >> 1);
    }*/
}

template <typename T>
T& Array<T>::operator[](int position) {
    if (position > _capacity) {
        cerr << "Pozitie invalida!\n";
        return resultData[0];
    }

    return resultData[position];
}

template <typename T>
void Array<T> :: quickSort(int pinitial, int pfinal) {
    int m = (pinitial + pfinal) >> 1;
    int i = pinitial;
    int j = pfinal;
    T pivot = resultData[m];

    while (i <= j) {
        while (resultData[i] < pivot)
            i++;
        while (pivot < resultData[j])
            j--;

        if (i <= j) {
            T temp = resultData[i];
            resultData[i] = resultData[j];
            resultData[j] = temp;
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