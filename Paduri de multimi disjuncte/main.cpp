#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#include "Array.h"
#include "disjointset.h"

ifstream f("dj.in");

bool adaugat[100];

int main() {
	DisjointSet a;

	int N, M;
	f >> N >> M;

	for (int i = 1; i <= N; ++i) {
		a.addSet(i);
	}

	for (int i = 1; i <= M; ++i) {
		int x, y;
		f >> x >> y;

		/*if (!adaugat[x]) {
			a.addSet(x);
		}
		if (!adaugat[y]) {
			a.addSet(y);
		}*/

		a.unite(x, y);
		a.print();
		cout << '\n';
	}

	a.addSet(11);
	a.print(); cout << '\n';
	a.unite(6, 11);
	a.print();
	return 0;
}