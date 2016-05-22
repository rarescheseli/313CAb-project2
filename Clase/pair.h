#pragma once

template <typename Tkey, typename Tvalue>
struct Pair {
    Tkey first;
    Tvalue second;
    Pair makePair(Tkey val1, Tvalue val2) {
        this->first = val1;
        this->second = val2;
        return *this;
    }

    // Constructor
    Pair() {
        first = Tkey();
        second = Tvalue();
    }

    Pair(Tkey key, Tvalue value) {
        first = key;
        second = value;
    }

    // Copy-constructor
    Pair(const Pair &other) {
        this->first = other.first;
        this->second = other.second; 
    }

    Pair<Tkey, Tvalue> &operator=(const Pair<Tkey, Tvalue> &other) {
        this->first = other.first;
        this->second = other.second;
        return *this;
    }

    bool operator==(const Pair<Tkey, Tvalue> &other) const {
        if ( (this->first == other.first) && (this->second == other.second) ) {
            return true;
        }
        if ( (this->first == other.second) && (this->second == other.first) ) {
            return true;
        }
        return false;
    }
};