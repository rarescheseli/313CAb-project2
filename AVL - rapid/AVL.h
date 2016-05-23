#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class AVLnode
{
	T data, sumData;//, sumData;
	int sons;
	AVLnode<T> *leftNode;
	AVLnode<T> *rightNode;
	unsigned int h; //height

public:
	AVLnode() {
		leftNode = rightNode = NULL;
        h = 0;
        sons = 0;
	}

	AVLnode(T data) {
		this->data = data;
		h = 1;
		leftNode = rightNode = NULL;
		sons = 0;
		sumData = data;
	}

	~AVLnode() {
        if (leftNode)
            delete leftNode;

        if (rightNode)
            delete rightNode;
	}

    T getSumData() {
        return sumData - data;
    }

	T getData(){
        return data;
    }

    T setData(T newData){
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
        if (node1 -> data <= current -> data && node2 -> data <= current -> data)
            return current -> leftNode -> LCA(node1, node2);
        if (node1 -> data > current -> data && node2 -> data > current -> data)
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
        if (this) return this->leftNode->getSons();
            else return 0;
	}

	int getRightSons(){
        if (this) return this->rightNode->getSons();
            else return 0;
	}

	AVLnode* rotateLeft(){
		AVLnode *toGoUp, *current = this;

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

	AVLnode* rotateRight() {
		AVLnode *toGoUp, *current = this;

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
	AVLnode* balance(){
        AVLnode* current = this;
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


	 // insert data key in a tree with "current" root
	AVLnode* insert(T data){
		// cand e radacina sau s-a ajuns la frunza unde trebuie adaugat
		AVLnode *current = this;
	    if( !current )
	    	return new AVLnode(data);

	    if( data < current->data )
	        current->leftNode = current->leftNode->insert(data);
	    else
	        current->rightNode = current->rightNode->insert(data);

        sumData += data;
        sons++;

	    return current->balance();
	}

    AVLnode<T>* searchKey(T x){
        if (this && this->data != x){
            if (this->data > x)
                return this->leftNode->searchKey(x);
            return this->rightNode->searchKey(x);
        }

        return this;
    }

	void InOrderDisplay(AVLnode<T> *node)
	{
		if (node != NULL) {
			InOrderDisplay(node->leftNode);
			cout << node->data << " ";
			InOrderDisplay(node->rightNode);
		}
	}

//debug
	void bfs(AVLnode *nod) {
		AVLnode *c;

		queue <AVLnode*> q;
		q.push(nod);
		int nrNoduri = 0;
		int nrNivel = 1;
		while (!q.empty()) {
			c = q.front();
			q.pop();

			if (c) {
				nrNoduri++;
				cout << (c->data) << ' ';
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
	}

};
