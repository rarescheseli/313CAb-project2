#include <iostream>
#include <fstream>

using namespace std;

#include "Array.h"

ofstream g("out");

int main() {
    Array <int> a;
    for (int i = 1; i < 2000000; ++i) {
        a.push_back(i);
    }

    
    Array <int> a2 = a;
    Array <int> a3;
    a3 = a;

    cout << a2.size() << ' ' << a3.size() << '\n';
    return 0;
}