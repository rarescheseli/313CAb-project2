#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class AVLnode
{
private:
	AVLnode<T> *leftNode;
	AVLnode<T> *rightNode;
	AVLnode<T> *parent;
	T *data;
	int balanceFactor;

public:
	AVLnode()
	{
		leftNode = rightNode = NULL;
		parent = NULL;
		data = NULL;
		balanceFactor = 0;
	}
	~AVLnode()
	{
		delete data;
	}

	bool IsEmpty()
	{
		return (data == NULL);
	}

	AVLnode* RotateLeft(AVLnode *currentNode)
	{
		AVLnode *toGoUp, *parentNode;
		
		toGoUp = currentNode->rightNode;
		parentNode = currentNode->parent;

		currentNode->rightNode = toGoUp->leftNode;
		if (currentNode->rightNode != NULL)
			currentNode->rightNode->parent = currentNode;
		currentNode->parent = toGoUp;
		toGoUp->leftNode = currentNode;

		if (parentNode != NULL) {
			//cout << "left " << *(currentNode->data) << ' ' << *(toGoUp->data) << ' ' << *(parentNode->data) << '\n';
			toGoUp->parent = parentNode;
			// schimb legatura cu parintele
			if (parentNode->leftNode == currentNode) // verific daca e fiul din stanga sau dreapta
				parentNode->leftNode = toGoUp;
			else
				parentNode->rightNode = toGoUp;
		}
		else
		{
			toGoUp->parent = NULL;
			return toGoUp;
		}
		return NULL;
	}

	AVLnode* RotateRight(AVLnode *currentNode) {
		AVLnode *toGoUp, *parentNode;

		toGoUp = currentNode->leftNode;
		parentNode = currentNode->parent;

		currentNode->leftNode = toGoUp->rightNode;
		if (currentNode->leftNode != NULL)
			currentNode->leftNode->parent = currentNode;
		currentNode->parent = toGoUp;
		toGoUp->rightNode = currentNode;

		//cout << "right " << *(currentNode->data) << ' ' << *(toGoUp->data) << ' ' << *(parentNode->data) << '\n';
		toGoUp->parent = parentNode;
		if (parentNode != NULL) {// schimb legatura cu parintele
			if (parentNode->leftNode == currentNode) // verific daca e fiul din stanga sau dreapta
				parentNode->leftNode = toGoUp;
			else
				parentNode->rightNode = toGoUp;
		}
		else
		{
			toGoUp->parent = NULL;
			return toGoUp;
		}
		return NULL;		
	}

	/* Debug
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
				cout << *(c->data) << ' ';
				if (nrNoduri == nrNivel) {
					nrNivel <<= 1;
					nrNoduri = 0;
					cout << "\n";
				}
				q.push(c->leftNode);
				q.push(c->rightNode);
				//if (c->leftNode) nrNoduri++;
				//if (c->rightNode) nrNoduri++;
			}
		}
		cout << "\n";
	}
	*/

	// https://en.wikipedia.org/wiki/AVL_tree
	AVLnode* Retracing(AVLnode *N) {
		// N is the child of P whose height increases by 1.
		AVLnode *P = N->parent, *root = NULL;

		if (!P) 
			return NULL;
		do {

			// P->balanceFactor has not yet been updated!
			if (N == P->leftNode) 
			{ // the left subtree increases
				if (P->balanceFactor == 1)
				{
					// ==> the temporary P->balanceFactor == 2 ==> rebalancing is required.
					if (N->balanceFactor == -1) { // Left Right Case
						//cout << "left right\n";
						root = RotateLeft(N); // Reduce to Left Left Case
						
					}
					// Left Left Case
					//cout << "left left\n";
					root = RotateRight(P);

					N->balanceFactor = 0;

					break; // Leave the loop
				}
				if (P->balanceFactor == -1) {
					P->balanceFactor = 0; // N’s height increase is absorbed at P.
					break; // Leave the loop
				}
				P->balanceFactor = 1; // Height increases at P
			}
			else { // N == right_child(P), the child whose height increases by 1.
				if (P->balanceFactor == -1)
				{
					// ==> the temporary P->balanceFactor == -2 ==> rebalancing is required.
					
					// Right Left Case
					if (N->balanceFactor == 1) 
					{ 
						//cout << "right left\n";
						root = RotateRight(N); // Reduce to Right Right Case

					}
					// Right Right Case
					//cout << "right right\n";
					root = RotateLeft(P);

					N->balanceFactor = 0;
					
					break; // Leave the loop
				}
				if (P->balanceFactor == 1) 
				{
					P->balanceFactor = 0; // N’s height increase is absorbed at P.

					break; // Leave the loop
				}
				P->balanceFactor = -1; // Height increases at P
			}
			N = P;
			P = P->parent;
		} while (P != NULL); // Possibly up to the root

		return root;
	}

	AVLnode* InsertKey(T x)
	{
		AVLnode *root = NULL;
		if (IsEmpty())
		{
			data = new T;
			*data = x;
			return this;
		}

		AVLnode *newNode = new AVLnode;
		AVLnode *currentNode;
		newNode->data = new T;
		(*newNode->data) = x;

		currentNode = this;
		while ((currentNode->leftNode != NULL && (*newNode->data) < (*currentNode->data))
			|| (currentNode->rightNode != NULL && (*newNode->data) > (*currentNode->data)))
			if ((*newNode->data) < (*currentNode->data))
				currentNode = currentNode->leftNode;
			else
				currentNode = currentNode->rightNode;

		newNode->parent = currentNode;
		if (currentNode->leftNode == NULL && (*newNode->data) < (*currentNode->data))
		{
			currentNode->leftNode = newNode;
			if (currentNode->rightNode == NULL) 
			{ // a crescut inaltimea
				currentNode->balanceFactor = 1;

					root= Retracing(currentNode);
			}
			else currentNode->balanceFactor = 0;
		}
		else 
		{
			currentNode->rightNode = newNode;
			if (currentNode->leftNode == NULL) 
			{ // a crescut inaltimea
				currentNode->balanceFactor = -1;

					root = Retracing(currentNode);
			}
			else currentNode->balanceFactor = 0;
		}

		if (root != NULL)
			return root;
		return this;
	}

	AVLnode<T>* SearchKey(T x)
	{
		AVLnode<T> *currentNode = this;

		while (currentNode != NULL && *(currentNode->data) != x)
			if (*(currentNode->data) > x)
				currentNode = currentNode->leftNode;
			else
				currentNode = currentNode->rightNode;

		return currentNode;
	}

	void InOrderDisplay(AVLnode<T> *node)
	{
		if (node != NULL) {
			InOrderDisplay(node->leftNode);
			cout << *(node->data) << " ";
			InOrderDisplay(node->rightNode);
		}
	}

	T FindClosest(AVLnode<T> *node)
	{
		AVLnode *currentNode;
		T min = *(node->data);
		T max = *(node->data);

		currentNode = node->leftNode;

		while (currentNode->rightNode != NULL)
			currentNode = currentNode->rightNode;
		max = *(currentNode->data);

		currentNode = node->rightNode;
		while (currentNode->leftNode != NULL)
			currentNode = currentNode->leftNode;
		min = *(currentNode->data);

		if (abs(min - *(node->data)) < abs(max - *(node->data)))
			return min;
		else
			return max;
	}

	AVLnode<T>* RemoveKey(T x)
	{
		AVLnode<T> *node, *tempRoot;
		AVLnode<T> **parentLink;
		T value;
		node = SearchKey(x);

		if (node == NULL)
			return this;

		if (node->parent != NULL)
		{
			if (node == node->parent->leftNode)
				parentLink = &(node->parent->leftNode);
			else
				parentLink = &(node->parent->rightNode);

			if (node->leftNode == NULL && node->rightNode == NULL)
			{
				*parentLink = NULL;
				delete node;
				return this;
			}
			if (node->leftNode != NULL && node->rightNode == NULL)
			{
				*parentLink = node->leftNode;
				delete node;
				return this;
			}
			if (node->leftNode == NULL && node->rightNode != NULL)
			{
				*parentLink = node->rightNode;
				delete node;
				return this;
			}
		}
		value = FindClosest(node);
		tempRoot = this;
		tempRoot = RemoveKey(value);
		*(node->data) = value;

		return tempRoot;
	}

	int RemoveSelf()
	{
		AVLnode<T> *p;
		if (leftNode == NULL && rightNode == NULL) {
			if (parent == NULL) { // this == root
				delete this;
				return 1;
			}
			else {
				if (parent->leftNode == this)
					parent->leftNode = NULL;
				else
					parent->rightNode = NULL;
				delete this;
				return 0;
			}
		}
		else {
			if (leftNode != NULL) {
				// Gaseste nodul cu cea mai mare valoare din subarborele stang.
				p = leftNode;
				while (p->rightNode != NULL)
					p = p->rightNode;
			}
			else { // right_son != NULL
				   // Gaseste nodul cu cea mai mica valoare din subarborele drept.
				p = rightNode;
				while (p->leftNode != NULL)
					p = p->leftNode;
			}

			memcpy(&data, &(p->data), sizeof(T));
			return p->RemoveSelf();
		}
	}

};