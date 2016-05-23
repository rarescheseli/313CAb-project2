#pragma once

#define MOD 100003

class Hash {
private:
    Array < pair < int, int > > *H;
public:
    Hash();
    ~Hash();

    void insert(int key, int value);
    pair <int, int> getValue(int key);
};

Hash::Hash() {
    H = new Array < pair <int, int> >[MOD];
}

Hash::~Hash() {
    delete[] H;
}

void Hash::insert(int key, int value) {
    int bucket = key % MOD;
    H[bucket].push_back(make_pair(key, value));
}

pair <int, int> Hash::getValue(int key) {
    int bucket = key % MOD;
    for (int i = 0; i < H[bucket].size(); ++i) {
        if (H[bucket][i].first == key) {
            return H[bucket][i];
        }
    }

    return make_pair(-1, -1);
}