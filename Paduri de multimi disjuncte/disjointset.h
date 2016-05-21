#pragma once

class DisjointSet {
private:
	Array <int> parent; /*parent[i] = parintele nodului i*/
	Array <int> setSize; /*setSize[i] = dimensiunea multimii care are radacina in i*/
	Array <int> position; /*position[i] = pozitia pe care se afla radacina i
					in vectorul sets*/
	Array <int> who; /*who[i] = radacina care se afla pe pozitia i 
			in vectorul sets*/
	Array <int> sets;

	int find(int node); /*returneaza radacina(id-ul) multimii din care face parte node*/

public:
	DisjointSet();
	void unite(int x, int y); /*uneste mulimile din care fac parte nodurile x si y*/
	void addSet(int node);
	void print();

	Array <int> setsDimensions();
};

Array <int> DisjointSet::setsDimensions() {
	Array <int> result;

	for (int i = 0; i < sets.size(); ++i) {
		result.push_back(setSize[sets[i]]);
	}

	return result;
}

void DisjointSet::print() {
	for (int i = 0; i < sets.size(); ++i) {
		cout << sets[i] << " " << setSize[sets[i]] << '\n';
	}
}

DisjointSet::DisjointSet() {
	parent.push_back(-1);
	setSize.push_back(-1);
	position.push_back(-1);
	who.push_back(-1);
}

int DisjointSet::find(int node) {
	if (parent[node] == node) {
		return node;
	}

	parent[node] = find(parent[node]); /*euristica 1: compresia drumurilor*/
	return parent[node];
}

void DisjointSet::unite(int x, int y) {
	x = find(x); /*se muta in radacina*/
	y = find(y);

	if (x < y) {
		swap(x, y);
	}
	parent[x] = y;

	int posX = position[x]; /*pozitia lui x in vectorul sets*/
	int length = sets.size(); /*numarul de componente conexe*/
	swap(sets[posX], sets[length-1]);
	sets.pop_back(); /*pune multimea scoasa (radacina lui x) pe ultima pozitie in sets
						si apoi o elimina*/

	int lastSet = who[length-1]; /*indicele ultimei multimi*/
	position[lastSet] = posX;
	who[posX] = lastSet;

	/*multimea x a fost scoasa din lista de seturi si adauga in multimea y*/
	setSize[y] += setSize[x];
}

void DisjointSet::addSet(int node) {
	parent.push_back(node);
	setSize.push_back(1);
	sets.push_back(node);

	int length = sets.size();
	position.push_back(length-1);

	if (who.size() == length) {
		who.push_back(node);
	} else {
		who[length - 1] = node;
	}
}