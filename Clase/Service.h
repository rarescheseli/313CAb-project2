#include <iostream>
#include "Array.h"
#include "hash.h"
#include "User.h"
#include "Heap.h"
#include "Magazin.h"
using namespace std;

// template<typename T>
// struct Array {
//     int resultSize;
//     T* resultData;

//     Array(int resultSize, T* resultData) :
//         resultSize(resultSize), resultData(resultData) {}
// };

#define MAX_CAPACITY 300005

class Service {
private:
    // bag userii in ordine cronologica
    Array <User> users;

    // bag magazinele in ordine cronologica
    Array <Magazin> magazine;

    // hash care ma duce din idUser -> al catelea a fost adaugat in ordine cronologica
    Hash hashClienti;

    // hash care ma duce din idMagazin -> al catelea a fost adaugat in ordine cronologica
    Hash hashMagazine;
    int idUserMostInv;
    int longestChainSize;
    Heap <User> ratioHeap;
    Array <int> longestChain;
public:

    Service();

    void createUser(int id, double homeX, double homeY);

    void createStore(int id, double storeX, double storeY);

    // discount = -1 daca userul nu a cumparat nimic si, astfel nu s-a acordat discount
    void visit(int timestamp, int clientId, int storeId, int discount);
    
    void invite (int userWhichInvites, int invitedUser);

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
    Array<pair<int, double>> averageVisitsPerUser();

    // Returneaza latitudine si longitudine pentru locatia recomandata pentru un nou magazin
    pair<double, double> newStoreCoordinates();
};

Service::Service() {
    User aux;
    Magazin aux2;
    users.push_back(aux);
    magazine.push_back(aux2);

    idUserMostInv = 0;
    longestChainSize = 0;
    longestChain.push_back(0);
}

void Service::createUser(int id, double homeX, double homeY) {
    longestChain.push_back(0);
    users.push_back(User(id, homeX), homeY);
    hashClienti.insert(id, users.size() - 1);
}

void Service::createStore(int id, double storeX, double storeY) {
    magazine.push_back(Magazin(id, store, storeY, MAX_CAPACITY));
    hashMagazine.insert(id, magazine.size() - 1);
}

void Service::invite (int userWhichInvites, int invitedUser) {
	ClientsGraph[userWhichInvites].push_back(invitedUser)

    int nodeWhichInvites = magicFunction(userWhichInvites);
    int invitedNode = magicFunction(invitedUser);

	if ( ClientsGraph[nodeWhichInvites].size() > ClientsGraph[idUserMostInv].size() ){
		idUserMostInv = nodeWhichInvites;
	}
	else if ( ClientsGraph[nodeWhichInvites].size() == ClientsGraph[idUserMostInv].size() 
        && nodeWhichInvites < idUserMostInv){
		idUserMostInv = nodeWhichInvites;
	}

    //pentru longestChain (un fel de dp)
    longestChain[invitedNode] = longestChain[nodeWhichInvites] + 1;

    if (longestChain[invitedNode] > longestChainSize) {
        longestChainSize = longestChain[invitedNode];
    }
}

Array <int> Service::usersWithBestBuyToDiscountRate(int K) {
	Array <int> array; 
	Heap <User> auxHeap(ratioHeap);

	for (int i = 0; i < K && auxHeap.size() > 0; i++){
		User top = auxHeap.extract();
		array.push_back( top.getId() );
	}
	
    return array;
}

int Service::userWithMostInvites() {
    if (idUserMostInv == 0) {
        return -1;
    }
	return idUserMostInv;
}

int Servic::longestInvitesChainSize() {
    return longestChainSize;
}