#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

#include "pair.h"
#include "resizablearray.h"
#include "heap.h"

int cmpMax(const Pair<int, int> &elem1, const Pair<int, int> &elem2) {
    if (elem1.first > elem2.first) {
        return 1;
    }
    return 0;
}

int main(void)
{
    srand(time(NULL));
    Heap<int> heap(100, cmpMax);

    // v[i] = al catelea element a fost inserat elementul cu id-ul i
    int v[1000];
    for (int i = 0; i < 1000; ++i) {
        v[i] = 0;
    }

    for (int i = 1; i <= 10; ++i) {
        int x = rand() % 1000;

        v[x] = i;
        heap.insert(x);
        for (int j = 0; j < heap.size(); ++j) {
            std::cout << heap.getValue(j) << ' ';
        }
        std::cout << '\n';
    }

    for (int i = 1; i < 1000; ++i) {
        if (v[i] != 0) {
            cout << i << ' ' << v[i] << '\n';

            heap.update(v[i], 1000);
            break;
        }
    }

    for (int j = 0; j < heap.size(); ++j) {
        std::cout << heap.getValue(j) << ' ';
    }
    std::cout << '\n';

    heap.peek();
    return 0;
}
