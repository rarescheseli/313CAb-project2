#pragma once

#define MOD 100003

class Hash {
private:
    Array < Pair < int, int > > *H;
public:
    Hash();
    ~Hash();

    void insert(int key, int value);
    Pair <int, int> getValue(int key);
};

Hash::Hash() {
    H = new Array < Pair <int, int> >[MOD];
}

Hash::~Hash() {
    delete[] H;
}

void Hash::insert(int key, int value) {
    int bucket = key % MOD;
    Pair <int, int> data(key, value);
    H[bucket].push_back(data);
}

Pair <int, int> Hash::getValue(int key) {
    int bucket = key % MOD;
    for (int i = 0; i < H[bucket].size(); ++i) {
        if (H[bucket][i].first == key) {
            return H[bucket][i];
        }
    }

    return Pair <int, int>(-1, -1);
}