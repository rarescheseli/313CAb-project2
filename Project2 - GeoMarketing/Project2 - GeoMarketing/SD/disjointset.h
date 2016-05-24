#pragma once

#include "../Utils/MinMax.h"

class DisjointSet {
private:
	Array <int> parent; /*parent[i] = parintele nodului i*/
	Array <int> setSize; /*setSize[i] = dimensiunea multimii care are radacina in i*/
	Array <int> setVisits; /*setVisits[i] = numarul total de vizite al grupului i*/
	Array <int> setID; /*setID[i] = cel mai mic id din grupul i*/
	Array <int> position; /*position[i] = pozitia pe care se afla radacina i
					in vectorul sets*/
	Array <int> who; /*who[i] = radacina care se afla pe pozitia i 
			in vectorul sets*/
	Array <int> sets;


	int find(int node); /*returneaza radacina(id-ul) multimii din care face parte node*/

public:
	DisjointSet();
	void unite(int x, int y); /*uneste mulimile din care fac parte nodurile x si y*/
	void addSet(int node, int idNode);
	void addVisit(int node);
	void print1();
	void print2();
	void print3();

	Array <int> setsDimensions();
	Array < pair<int, double> > setsAverage();
	Array <int> topKGroups(int K);

};

	Array <int> DisjointSet::topKGroups(int K) {
	Array <int> dimensions = setsDimensions();
	Array <int> result;

	dimensions.quickSort(0, dimensions.size()-1);

	int length = dimensions.size();
	int firstPos = max(0, length-K);
	for (int i = length-1; i >= firstPos; --i) {
		result.push_back(dimensions[i]);
	}

	return result;
}

Array < pair<int, double> > DisjointSet::setsAverage() {
	Array < pair<int, double> > result;

	for (int i = 0; i < sets.size(); ++i) {
		result.push_back(make_pair(setID[sets[i]],
			double(setVisits[sets[i]]) / setSize[sets[i]]));
	}

	return result;
}

void DisjointSet::addVisit(int node) {
	int root = find(node);
	setVisits[root]++;
}

Array <int> DisjointSet::setsDimensions() {
	Array <int> result;

	for (int i = 0; i < sets.size(); ++i) {
		result.push_back(setSize[sets[i]]);
	}

	return result;
}

void DisjointSet::print3() {
	Array < pair<int, double> > res = setsAverage();

	for (int i = 0; i < res.size(); ++i) {
		cout << res[i].first << " " << res[i].second << '\n';
	}
}

void DisjointSet::print2() {
	Array <int> res = topKGroups(5);

	for (int i = 0; i < res.size(); ++i) {
		cout << res[i] << '\n';
	}
}

void DisjointSet::print1() {
	for (int i = 0; i < sets.size(); ++i) {
		cout << sets[i] << " " << setSize[sets[i]] << " " << setID[sets[i]] << '\n';
	}
}

DisjointSet::DisjointSet() {
	parent.push_back(-1);
	setSize.push_back(-1);
	position.push_back(-1);
	who.push_back(-1);
	setVisits.push_back(-1);
	setID.push_back(-1);
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

	/*multimea x a fost scoasa din lista de seturi si adaugata in multimea y*/
	setSize[y] += setSize[x];
	setVisits[y] += setVisits[x];

	setID[y] = min(setID[x], setID[y]);
}

void DisjointSet::addSet(int node, int idNode) {
	parent.push_back(node);
	setSize.push_back(1);
	setVisits.push_back(0);
	setID.push_back(idNode);
	sets.push_back(node);


	int length = sets.size();
	position.push_back(length-1);

	if (who.size() == length-1) {
		who.push_back(node);
	} else {
		who[length - 1] = node;
	}
}