#include <bits/stdc++.h>

using namespace std;

#include "pair.h"
#include "Array.h"
#include "hash.h"

ofstream g("out");

int a[500005];

int main() {
    Hash H;
    srand(time(NULL));
    for (int i = 1; i <= 500000; ++i) {
        a[i] = rand();
        H.insert(a[i], i);
    }

    for (int i = 1; i <= 500000; ++i) {
        g << i << ' ' << a[i] << '\n';
    }

    for (int i = 1; i <= 500000; ++i) {
        g << a[i] << ' ' << H.getValue(a[i]) << '\n';
    }
    return 0;
}