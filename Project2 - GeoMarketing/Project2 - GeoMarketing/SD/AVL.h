#include <iostream>
#include <cmath>

using namespace std;

#pragma once
template <typename T>
class AVLnode
{
	T data, sumData;//, sumData;
	int sons, key;
	AVLnode<T> *leftNode;
	AVLnode<T> *rightNode;
	unsigned int h; //height

public:
	AVLnode() {
		leftNode = rightNode = NULL;
        h = 0;
        sons = 0;
	}

	AVLnode(int key, T data) {
		this->data = data;
		this->key = key;
		h = 1;
		leftNode = rightNode = NULL;
		sons = 0;
		sumData = data;
	}

	~AVLnode() {
       /* if (leftNode)
            delete leftNode;

        if (rightNode)
            delete rightNode;*/
	}

    T getSumData() {
        return sumData - data;
    }

	T getData(){
        return data;
    }

    T getLeftData(){
    	if (leftNode)
    		return leftNode->sumData;
    	else
    		return 0;
    }

    T getRightData(){
    	if (rightNode)
    		return rightNode->sumData;
    	else
    		return 0;
    }

    int getKey(){
    	return key;
    }

    void setData(T newData){
        data = newData;
    }

    int getSonsLeft(){
        return leftNode->getSons();
    }

	unsigned int height(){
    	if(this) return this->h;
    		else return 0;
	}

	AVLnode<T>* LCA(AVLnode<T>* node1, AVLnode<T>* node2) {
        AVLnode<T>* current = this;

        if (node1 == current || node2 == current)
            return current;
        if (node1 -> key <= current -> key && node2 -> key <= current -> key)
            return current -> leftNode -> LCA(node1, node2);
        if (node1 -> key > current -> key && node2 -> key > current -> key)
            return current -> rightNode -> LCA(node1, node2);
        return current;
	}

	// returneaza intaltimea arborelui
	// e nevoie de functia asta pentru a putea accesa intaltimea si daca nodul accesat nu exista
	int balanceFactor(){
	    return rightNode->height() - leftNode->height();
	}

	void fixHeight(){
	    if (leftNode->height() > rightNode->height())
	    	h = leftNode->height() + 1;
	    else
	    	h = rightNode->height() + 1;
	}

	int getSons(){
        if (this) return sons;
            else return -1;
	}

	int getLeftSons(){
        if (this) return this->leftNode->getSons() + 1;
            else return 0;
	}

	int getRightSons(){
        if (this) return this->rightNode->getSons() + 1;
            else return 0;
	}

	int getIntervalSons(int key1, int key2){
		if (key1 > key2) swap(key1, key2);

		AVLnode<T> *left = searchKey(key1);
		AVLnode<T> *right = searchKey(key2);
		AVLnode<T> *lca = LCA(left, right);

		if (lca == left){
			return 1 + left->getRightSons() - right->getRightSons();
		}

		if (lca == right){
			return 1 + right->getLeftSons() - left->getLeftSons();
		}

		int result = lca->sons;
		AVLnode<T> *current = lca;
		// scadem ce nu ne trebuie pe drumul de la lca la left
		while(current != left){
			if (current->key <= left->key ){
				result -= current->getLeftSons() + 1;
				current = current->rightNode;
			}
			else current = current->leftNode;
		}
		result -= current->getLeftSons();

		current = lca;
		// scadem ce nu ne trebuie pe drumul de la lca la right
		while(current != right){
			if (current->key >= right->key ){
				result -= current->getRightSons() + 1;
				current = current->leftNode;
			}
			else current = current->rightNode;
		}
		result -= current->getRightSons();

		return result;
	}

	T getIntervalData(int key1, int key2){
		if (key1 > key2) swap(key1, key2);

		AVLnode<T> *left = searchKey(key1);
		AVLnode<T> *right = searchKey(key2);
		AVLnode<T> *lca = LCA(left, right);

		if (lca == left){
			return lca->sumData - left->getLeftData() - right->getRightData();
		}

		if (lca == right){
			return lca->sumData - right->getRightData() - left->getLeftData();
		}

		T result = lca->sumData;
		AVLnode<T> *current = lca;
		// scadem ce nu ne trebuie pe drumul de la lca la left
		while(current != left){
			if (current->key <= left->key ){
				result -= current->getLeftData();
				current = current->rightNode;
			}
			else current = current->leftNode;
		}
		result -= current->getLeftData();

		current = lca;
		// scadem ce nu ne trebuie pe drumul de la lca la right
		while(current != right){
			if (current->key >= right->key ){
				result -= current->getRightData();
				current = current->leftNode;
			}
			else current = current->rightNode;
		}
		result -= current->getRightData();

		return result;
	}

	AVLnode<T>* rotateLeft(){
		AVLnode<T> *toGoUp, *current = this;

		toGoUp = current->rightNode;

        current->sons -= toGoUp->sons + 1;
		current->sumData -= toGoUp->sumData;
		if(toGoUp->leftNode) {
            current->sons += toGoUp->leftNode->sons + 1;
            current->sumData += toGoUp->leftNode->sumData;
        }

		if(toGoUp->leftNode) {
            toGoUp->sons -= toGoUp->leftNode->sons + 1;
            toGoUp->sumData -= toGoUp->leftNode->sumData;
		}
		toGoUp->sons += current->sons + 1;
		toGoUp->sumData += current->sumData;

        /*if (toGoUp->rightNode)
            current->sons = current->sons - toGoUp->rightNode->sons - 2;
        else
            current->sons--;

        if (current->leftNode)
            toGoUp->sons += current->leftNode->sons + 2;
        else
            toGoUp->sons++;
        */

        current->rightNode = toGoUp->leftNode;
		toGoUp->leftNode = current;

		current->fixHeight();
		toGoUp->fixHeight();

		return toGoUp;
	}

	AVLnode<T>* rotateRight() {
		AVLnode<T> *toGoUp, *current = this;

		toGoUp = current->leftNode;

		current->sons -= toGoUp->sons + 1;
		current->sumData -= toGoUp->sumData;
		if(toGoUp->rightNode) {
            current->sons += toGoUp->rightNode->sons + 1;
            current->sumData += toGoUp->rightNode->sumData;
        }

		if(toGoUp->rightNode) {
            toGoUp->sons -= toGoUp->rightNode->sons + 1;
            toGoUp->sumData -= toGoUp->rightNode->sumData;
		}
		toGoUp->sons += current->sons + 1;
		toGoUp->sumData += current->sumData;

        /*if (toGoUp->leftNode){
            current->sons = current->sons - toGoUp->leftNode->sons - 2;
            current->sumData = current->sumData - toGoUp->leftNode->sumData - toGoUp->data - ;
        else
            current->sons--;

        if (current->rightNode)
            toGoUp->sons += current->rightNode->sons + 2;
        else
            toGoUp->sons++;
*/

        current->leftNode = toGoUp->rightNode;
		toGoUp->rightNode = current;

		current->fixHeight();
		toGoUp->fixHeight();

		return toGoUp;
	}

	 // balancing the current node
	AVLnode<T>* balance(){
        AVLnode<T>* current = this;
	    current->fixHeight();

	    if( current->balanceFactor() == 2 ){
	        if( current->rightNode->balanceFactor() < 0 ) // right left case -> reduce to right right
	            current->rightNode = current->rightNode->rotateRight();
	        return current->rotateLeft(); // right case
	    }

	    if( current->balanceFactor() == -2 ){ // left right case -> reduce to left left
	        if( current->leftNode->balanceFactor() > 0  )
	            current->leftNode = current->leftNode->rotateLeft();
	        return current->rotateRight(); // left case
	    }
	    // else balancing is not required
	    return current;
	}


	 // insert key and data in a tree with "current" root
	 // AVL is sorted by key
	AVLnode<T>* insert(int key, T data){
		// cand e radacina sau s-a ajuns la frunza unde trebuie adaugat
		AVLnode<T> *current = this;
	    if( !current )
	    	return new AVLnode(key, data);

	    if( key < current->key )
	        current->leftNode = current->leftNode->insert(key, data);
	    else
	        current->rightNode = current->rightNode->insert(key, data);

        sumData += data;
        sons++;

	    return current->balance();
	}

    AVLnode<T>* searchKey(int x){
        if (this && this->key != x){
            if (this->key > x)
                return this->leftNode->searchKey(x);
            return this->rightNode->searchKey(x);
        }

        return this;
    }
/*
	void InOrderDisplay(AVLnode<T> *node)
	{
		if (node != NULL) {
			InOrderDisplay(node->leftNode);
			cout << node->key << " ";
			InOrderDisplay(node->rightNode);
		}
	}
*/
//debug
/*	void bfs(AVLnode<T> *nod) {
		AVLnode<T> *c;

		queue <AVLnode<T>*> q;
		q.push(nod);
		int nrNoduri = 0;
		int nrNivel = 1;
		while (!q.empty()) {
			c = q.front();
			q.pop();

			if (c) {
				nrNoduri++;
				cout << (c->key) << ' ';
				if (nrNoduri == nrNivel) {
					nrNivel <<= 1;
					nrNoduri = 0;
					cout << "\n";
				}
				q.push(c->leftNode);
				q.push(c->rightNode);
			}
		}
		cout << "\n";
	}*/

};
