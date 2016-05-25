#include <iostream>
#include <cstring>
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
#define MAX_AIB 1000005

class Service {
private:
	// bag userii in ordine cronologica
	Array <User> users;
	User users2[MAX_CLIENTS];

	//AVLnode <long long> *discountAVL;

	int *aib;
	long long *aibd;

	// bag magazinele in ordine cronologica
	Array <Magazin> magazine;

	// hash care ma duce din idUser -> al catelea a fost adaugat in ordine cronologica
	Hash hashClienti;

	// hash care ma duce din idMagazin -> al catelea a fost adaugat in ordine cronologica
	Hash hashMagazine;

	bool firstVisit;

	//paduri
	DisjointSet disjointSet;

	//Pentru ultimul Task
	NewMag *newMag;

	// int crtSize;
	// bool viz[MAX_CAPACITY];
	// void dfs(int nod) {
	// 	viz[nod] = 1;
	// 	for (int i = 0; i < ClientsGraph[nod].size(); ++i) {
	// 		if (!viz[ClientsGraph[nod][i]]) {
	// 			dfs(ClientsGraph[nod][i]);
	// 		}
	// 	}

	// 	++crtSize;
	// }

	void updateVizite(int pos) {
		while (pos <= MAX_AIB) {
			++aib[pos];
			pos += -pos & pos;
		}
	}

	int queryVizite(int pos) {
		int res = 0;
		while (pos) {
			res += aib[pos];
			pos -= -pos & pos;
		}

		return res;
	}

	void updated(int pos, long long val) {
		while (pos <= MAX_AIB) {
			aibd[pos] += val;
			pos += -pos & pos;
		}
	}

	long long queryd(int pos) {
		long long res = 0;
		while (pos) {
			res += aibd[pos];
			pos -= -pos & pos;
		}

		return res;
	}

	int minTimestamp;
	int maxTimestamp;
	int idUserMostInv;
	bool firstDiscount;
	int *gradInterior;
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

	aib = new int[MAX_AIB]();
	aibd = new long long[MAX_AIB]();
	Magazin aux2;
	users.push_back(aux);
	//discountAVL = new AVLnode <long long>();
	//gradInterior = new int[MAX_CLIENTS]();

	maxTimestamp = -1;
	minTimestamp = 2147483647;

	firstVisit = false;
	firstDiscount = false;
	magazine.push_back(aux2);
	ClientsGraph = new Array <int>[MAX_CLIENTS];

	idUserMostInv = -1;
	longestChainSize = 0;
	longestChain.push_back(0);
}

Service::~Service() {
	delete[] ClientsGraph;
	delete[] aib;
	delete[] aibd;
}

int Service::visitsInTimeframe(int startTime, int endTime) {
	++startTime;
	++endTime;
	if (maxTimestamp == -1 || startTime > maxTimestamp || endTime < minTimestamp) {
		return 0;
	}

	// int result = 0;
	// int limit = magazine.size() - 1;
	// for (int i = 1; i <= limit; ++i) {
	// 	result += magazine[i].visitsInTimeframe(startTime, endTime);
	// }

	//cout << "visitsInTimeframe\n";

	int final = min(maxTimestamp, endTime);
	int start = max(minTimestamp, startTime);

	// cout << startTime << ' ' << endTime << '\n';
	// cout << start << ' ' << final << '\n';

	// if (final == 2001) {
	// 	viziteAVL->InOrderDisplay(viziteAVL);
	// }

	return queryVizite(final) - queryVizite(start - 1);
}

int Service::totalDiscountInTimeframe(int startTime, int endTime) {
	int final = min(maxTimestamp, endTime + 1);
	int start = max(minTimestamp, startTime + 1);
	int result = queryd(final) - queryd(start - 1);
	return result;
}

int Service::visitsInTimeframeOfStore(int startTime, int endTime, int storeId) {
	int indexMagazin = hashMagazine.getValue(storeId).second;
	return magazine[indexMagazin].visitsInTimeframe(startTime, endTime);
}

Array<int> Service::biggestKDiscounts(int K, int storeId) {
	int indexMagazin = hashMagazine.getValue(storeId).second;
	//cout << storeId << ' ' << indexMagazin << '\n';
	//cout << "biggestKDiscounts\n";
	return magazine[indexMagazin].topKdiscounts(K);

	Array <int> a;

	return a;
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

	users2[id] = User(id, homeX, homeY);
	cout << "create user..................................... " << users.size() -1 << " " << id << '\n';
	disjointSet.addSet(users.size() - 1, id);
}

void Service::createStore(int id, double storeX, double storeY) {
	// cout << "magazine1\n";
	Magazin aux(id, storeX, storeY);
	magazine.push_back(aux);
	/*cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA ";
	cout << id << ' ' << magazine.size() - 1 << '\n';
	cout << storeX << ' ' << storeY << '\n';*/
	hashMagazine.insert(id, magazine.size() - 1);
}

void Service::invite(int userWhichInvites, int invitedUser) {
	//cout << "intvite1\n";
	// int nodeWhichInvites = hashClienti.getValue(userWhichInvites).second;
	// int invitedNode = hashClienti.getValue(invitedUser).second;

	int nodeWhichInvites = userWhichInvites;
	int invitedNode = invitedUser;

	// gradInterior[invitedNode] = 1;
	ClientsGraph[nodeWhichInvites].push_back(invitedNode);

	if (idUserMostInv == -1) {
		idUserMostInv = userWhichInvites;
		longestChainSize = 1;
		return;
	}

	if (ClientsGraph[nodeWhichInvites].size() > ClientsGraph[idUserMostInv].size()) {
		idUserMostInv = nodeWhichInvites;
	} else if (ClientsGraph[nodeWhichInvites].size() == ClientsGraph[idUserMostInv].size()
		&& userWhichInvites < idUserMostInv) {
		idUserMostInv = userWhichInvites;
	}

	//pentru longestChain (un fel de dp)
	longestChain[invitedNode] = longestChain[nodeWhichInvites] + 1;

	if (longestChain[invitedNode] > longestChainSize) {
		longestChainSize = longestChain[invitedNode];
	}

	//paduri
	nodeWhichInvites = hashClienti.getValue(userWhichInvites).second;
	invitedNode = hashClienti.getValue(invitedUser).second;
	disjointSet.unite(nodeWhichInvites, invitedNode);

	cout << "invite................................................ ";
	cout << userWhichInvites << " " << invitedUser << '\n';
	cout << nodeWhichInvites << " " << invitedNode << '\n';

	//cout << "intvite\n";
}

void Service::visit(int timestamp, int clientId, int storeId, int discount) {
	++timestamp;
	int node = hashClienti.getValue(clientId).second;
	disjointSet.addVisit(node);

	minTimestamp = min(timestamp, minTimestamp);
	maxTimestamp = max(timestamp, maxTimestamp);

	// if (firstVisit == false) {
	// 	firstVisit = true;
	// 	viziteAVL = new AVLnode <int>(timestamp, 0);
	// } else {
	// 	viziteAVL->insert(timestamp, 0);
	// }

	updateVizite(timestamp);
	if (discount != -1) {
		updated(timestamp, discount);
	}

	pair <int, int> a = hashMagazine.getValue(storeId);
	// cout << "SDAafffffffffffffffffsdasdS  " << a.first << ' ' << a.second << '\n';
	// cout << storeId << ' ' << magazine[a.second].getId() << '\n';
	magazine[a.second].visit(timestamp, users[node], discount);
}

Array <int> Service::usersWithBestBuyToDiscountRate(int K) {
	cout << "usersWithBestBuyToDiscountRate1\n";
	cout << users.size() << '\n';
	if (ratioHeap.size() <= 1) {
		cout << "ASD\n";
		Array <int> a;
		a.push_back(5);
		return a;
	}

	Array <int> array;
	Heap <User> auxHeap(ratioHeap);

	for (int i = 0; i < K && auxHeap.size() > 1; i++) {
		User top = auxHeap.extract();
		array.push_back(top.getId());
	}
	cout << "usersWithBestBuyToDiscountRate\n";

	return array;
}

int Service::userWithMostInvites() {
	if (users.size() <= 1) {
		return -1;
	}
	return idUserMostInv;

}

int Service::longestInvitesChainSize() {
	cout << "longestInvitesChainSize1\n";
	// crtSize = 0;
	// memset(viz, 0, sizeof(viz));

	// for (int i = 1; i < users.size(); ++i) {
	// 	if (gradInterior[i] == 0 && !viz[i]) {
	// 		dfs(i);
	// 	}
	// }

	// if (crtSize - 1> longestChainSize) {
	// 	longestChainSize = crtSize - 1;
	// }

	cout << "longestInvitesChainSize\n";

	return longestChainSize;
}

Array<int> Service::distinctGroupsOfUsers() {
	cout << "distinctGroupsOfUsers1\n";
	return disjointSet.setsDimensions();
}

Array<int> Service::topKGroupsWithMostVisitsOverall(int K) {
	cout << "topKGroupsWithMostVisitsOverall1\n";
	return disjointSet.topKGroups(K);
}

Array< pair<int, double> > Service::averageVisitsPerUser() {
	cout << "averageVisitsPerUser1\n";
	return disjointSet.setsAverage();
}

pair<double, double> Service::newStoreCoordinates() {
	Point p;
	//newMag = new NewMag(users, magazine, magazine.size() - 1);
	//return make_pair(p.x, p.y);
	return make_pair(0, 0);
}
