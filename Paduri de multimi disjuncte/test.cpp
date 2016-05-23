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

	int n = 1<<20;

	for (int i = 1;  i <= n; ++i )
	{
		a.addSet(i, i+1000000000);
	}

	//a.print1();

	int power = 1;
	/*while(power <= n) {
		for(int i = 1; i+power<=n; i+=2*power ){
			a.unite(i, i+power);
		}
		power*=2;
	}*/

	while(power <= n) {
		for(int i = n; i-power>=1; i-=2*power ){
			a.unite(i, i-power);
		}
		power*=2;
	}

	a.print1();
	
	return 0;
}