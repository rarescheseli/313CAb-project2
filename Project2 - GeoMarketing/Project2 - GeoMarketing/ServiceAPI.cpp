#include <iostream>
#include "./SD/Array.h"
#include "./SD/hash.h"
#include "./Clase/User.h"
#include "./SD/heap.h"
#include "./Clase/Magazin.h"
#include "./Clase/User.h"
#include "./SD/disjointset.h"
#include "./SD/AVL.h"
#include "Taskuri/NewMag.h"

using namespace std;

// template<typename T>
// struct Array {
//     int resultSize;
//     T* resultData;

//     Array(int resultSize, T* resultData) :
//         resultSize(resultSize), resultData(resultData) {}
// };

#define MAX_CAPACITY 300005
#define MAX_CLIENTS 200002

class Service {
private:
	// bag userii in ordine cronologica
	Array <User> users;

	AVLnode <long long> *discountAVL = NULL;

	// bag magazinele in ordine cronologica
	Array <Magazin> magazine;

	// hash care ma duce din idUser -> al catelea a fost adaugat in ordine cronologica
	Hash hashClienti;

	// hash care ma duce din idMagazin -> al catelea a fost adaugat in ordine cronologica
	Hash hashMagazine;

	//paduri
	DisjointSet disjointSet;

	//Pentru ultimul Task
	NewMag *newMag;

	int idUserMostInv;
	bool firstDiscount;
	int longestChainSize;
	Heap <User> ratioHeap;
	Array <int> longestChain;

	// graf orientat in care pun invitatiile
	Array <int> *ClientsGraph;
public:

	Service();
	~Service();

	void createUser(int id, double homeX, double homeY);

	void createStore(int id, double storeX, double storeY);

	// discount = -1 daca userul nu a cumparat nimic si, astfel nu s-a acordat discount
	void visit(int timestamp, int clientId, int storeId, int discount);

	void invite(int userWhichInvites, int invitedUser);

	// numar de vizite in intervalul (startTime, endTime)
	int visitsInTimeframe(int startTime, int endTime);

	// discount total in intervalul (startTime, endTime)
	int totalDiscountInTimeframe(int startTime, int endTime);

	// Returneaza un Array de k elemente cu id-urile user-ilor
	Array<int> usersWithBestBuyToDiscountRate(int K);

	// numar de vizite in intervalul (startTime, endTime) pentru magazinul storeId
	int visitsInTimeframeOfStore(int startTime, int endTime, int storeId);

	// cele mai mari discount-uri acordate in magazinul storeId
	Array<int> biggestKDiscounts(int K, int storeId);

	// cele mai mari distante de la care vin clientii la magazinul storeId
	Array<double> biggestKClientDistances(int K, int storeId);

	// Returneaza un array cu index-ul zilelor cele mai aglomerate
	Array<int> mostCrowdedKDays(int K, int storeId);

	// Returneaza un array cu dimensiunile grupurilor de utilizatori
	Array<int> distinctGroupsOfUsers();

	// Id-ul userului care a invitat cei mai multi utilizatori
	// Daca sunt doi cu aceeasi valoare, se va intoarce id-ul minim
	int userWithMostInvites();

	// Lungimea celui mai lung lant de invitatii
	int longestInvitesChainSize();

	// Id-urile grupurilor cu cele mai multe invitatii overall
	// Id-ul unui grup se considera minimul id-urilor utilizatorilor din acel grup
	Array<int> topKGroupsWithMostVisitsOverall(int K);

	// O lista de perechi de forma (idGrup, numarMediuDeVizite)
	// Id-ul unui grup se considera minimul id-urilor utilizatorilor din acel grup
	Array< pair<int, double> > averageVisitsPerUser();

	// Returneaza latitudine si longitudine pentru locatia recomandata pentru un nou magazin
	pair<double, double> newStoreCoordinates();
};

Service::Service() {
	User aux;
	Magazin aux2;
	users.push_back(aux);
	firstDiscount = false;
	magazine.push_back(aux2);
	ClientsGraph = new Array <int>[MAX_CLIENTS];

	idUserMostInv = 0;
	longestChainSize = 0;
	longestChain.push_back(0);
}

Service::~Service() {
	delete discountAVL;
	delete[] ClientsGraph;
}

int Service::visitsInTimeframe(int startTime, int endTime) {
	int result = 0;
	int limit = magazine.size() - 1;
	for (int i = 1; i < limit; ++i) {
		result += magazine[i].visitsInTimeframe(startTime, endTime);
	}

	return result;
}

int Service::totalDiscountInTimeframe(int startTime, int endTime) {
	return (int)discountAVL->getIntervalData(startTime, endTime);
}

int Service::visitsInTimeframeOfStore(int startTime, int endTime, int storeId) {
	int indexMagazin = hashMagazine.getValue(storeId).second;
	return magazine[indexMagazin].visitsInTimeframe(startTime, endTime);
}

Array<int> Service::biggestKDiscounts(int K, int storeId) {
	int indexMagazin = hashMagazine.getValue(storeId).second;
	return magazine[indexMagazin].topKdiscounts(K);
}

Array<int> Service::mostCrowdedKDays(int K, int storeId) {
	int indexMagazin = hashMagazine.getValue(storeId).second;
	return magazine[indexMagazin].topKdays(K);
}

Array<double> Service::biggestKClientDistances(int K, int storeId) {
	int indexMagazin = hashMagazine.getValue(storeId).second;
	return magazine[indexMagazin].topKdistances(K);
}

void Service::createUser(int id, double homeX, double homeY) {
	longestChain.push_back(0);
	users.push_back(User(id, homeX, homeY));
	hashClienti.insert(id, users.size() - 1);

	disjointSet.addSet(users.size() - 1, id);
}

void Service::createStore(int id, double storeX, double storeY) {
	magazine.push_back(Magazin(id, storeX, storeY, MAX_CAPACITY));
	hashMagazine.insert(id, magazine.size() - 1);
}

void Service::invite(int userWhichInvites, int invitedUser) {
	int nodeWhichInvites = hashClienti.getValue(userWhichInvites).second;
	int invitedNode = hashClienti.getValue(invitedUser).second;

	ClientsGraph[nodeWhichInvites].push_back(invitedNode);

	if (ClientsGraph[nodeWhichInvites].size() > ClientsGraph[idUserMostInv].size()) {
		idUserMostInv = nodeWhichInvites;
	}
	else if (ClientsGraph[nodeWhichInvites].size() == ClientsGraph[idUserMostInv].size()
		&& nodeWhichInvites < idUserMostInv) {
		idUserMostInv = nodeWhichInvites;
	}

	//pentru longestChain (un fel de dp)
	longestChain[invitedNode] = longestChain[nodeWhichInvites] + 1;

	if (longestChain[invitedNode] > longestChainSize) {
		longestChainSize = longestChain[invitedNode];
	}

	//paduri
	disjointSet.unite(nodeWhichInvites, invitedNode);
}

void Service::visit(int timestamp, int clientId, int storeId, int discount) {
	int node = hashClienti.getValue(clientId).second;
	disjointSet.addVisit(node);

	int mag = hashMagazine.getValue(storeId).second;
	magazine[mag].visit(timestamp, users[node], discount);

	if (discount != -1) {
		if (firstDiscount == false) {
			firstDiscount = true;
			discountAVL = new AVLnode<long long>(timestamp, discount);
		}
		else {
			discountAVL->insert(timestamp, discount);
		}
	}
}

Array <int> Service::usersWithBestBuyToDiscountRate(int K) {
	Array <int> array;
	Heap <User> auxHeap(ratioHeap);

	for (int i = 0; i < K && auxHeap.size() > 1; i++) {
		User top = auxHeap.extract();
		array.push_back(top.getId());
	}

	return array;
}

int Service::userWithMostInvites() {
	if (idUserMostInv == 0) {
		return -1;
	}
	return idUserMostInv;
}

int Service::longestInvitesChainSize() {
	return longestChainSize;
}

Array<int> Service::distinctGroupsOfUsers() {
	return disjointSet.setsDimensions();
}

Array<int> Service::topKGroupsWithMostVisitsOverall(int K) {
	return disjointSet.topKGroups(K);
}

Array< pair<int, double> > Service::averageVisitsPerUser() {
	return disjointSet.setsAverage();
}

pair<double, double> Service::newStoreCoordinates() {
	Point p;
	newMag = new NewMag(users, magazine, magazine.size() - 1);
	return make_pair(p.x, p.y);
}