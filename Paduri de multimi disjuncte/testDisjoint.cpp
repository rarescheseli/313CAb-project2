#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


#include "Array.h"
#include "heap.h"
#include "disjointset.h"

ifstream f("dj.in");

bool adaugat[100];

int main() {
	DisjointSet a;

	int N, M;
	f >> N >> M;

	for (int i = 1; i <= N; ++i) {
		a.addSet(i,i+100);
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= 1; ++j) {
			a.addVisit(i);
		}
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
		a.print2();

		cout << '\n';
	}

	a.addSet(11,11+100);
	a.print2(); cout << '\n';
	a.unite(6, 11);
	a.print2();

	cout << '\n';

	Array <int> test = a.setsDimensions();

	for (int i = 0; i < test.size(); ++i) {
		cout << test[i] << " ";
	}
	cout << '\n';

	return 0;
}