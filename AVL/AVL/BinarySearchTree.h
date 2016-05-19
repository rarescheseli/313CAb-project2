#ifndef __BINARY_SEARCH_TREE__H
#define __BINARY_SEARCH_TREE__H

#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class BinarySearchTree
{
private:
  BinarySearchTree<T> *leftNode;
  BinarySearchTree<T> *rightNode;
  BinarySearchTree<T> *parent;
  T *pData;

public:
	BinarySearchTree() 
	{
		leftNode = rightNode = NULL;
		parent = NULL;
		pData = NULL;
	}
	~BinarySearchTree() 
	{
		delete pData;
	}

	bool IsEmpty() 
	{
		return (pData == NULL);
	}
	


	void InsertKey(T x) 
	{
		if (IsEmpty())
		{
			pData = new T;
			*pData = x;
			return;
		}

		BinarySearchTree *newNode = new BinarySearchTree;
		BinarySearchTree *currentNode;
		newNode->pData = new T;
		(*newNode->pData) = x;

		currentNode = this;
		while ((currentNode->leftNode != NULL && (*newNode->pData) < (*currentNode->pData))
			|| (currentNode->rightNode != NULL && (*newNode->pData) > (*currentNode->pData)))
			if ((*newNode->pData) < (*currentNode->pData))
				currentNode = currentNode->leftNode;
			else
				currentNode = currentNode->rightNode;

		newNode->parent = currentNode;
		if (currentNode->leftNode == NULL && (*newNode->pData) < (*currentNode->pData))
			currentNode->leftNode = newNode;
		else
			currentNode->rightNode = newNode;

	}

	BinarySearchTree<T>* SearchKey(T x) 
	{
		BinarySearchTree<T> *currentNode = this;

		while (currentNode != NULL && *(currentNode->pData) != x)
			if (*(currentNode->pData) > x)
				currentNode = currentNode->leftNode;
			else
				currentNode = currentNode->rightNode;

		return currentNode;
	}

	void InOrderDisplay(BinarySearchTree<T> *node) 
	{
		if (node != NULL) {
			InOrderDisplay(node->leftNode);
			cout << *(node->pData) << " ";
			InOrderDisplay(node->rightNode);
		}
	}	

	T FindClosest(BinarySearchTree<T> *node)
	{
		BinarySearchTree *currentNode;
		T min = *(node->pData);
		T max = *(node->pData);

		currentNode = node->leftNode;

		while (currentNode->rightNode != NULL)
			currentNode = currentNode->rightNode;
		max = *(currentNode->pData);

		currentNode = node->rightNode;
		while (currentNode->leftNode != NULL)
			currentNode = currentNode->leftNode;
		min = *(currentNode->pData);

		if (abs(min - *(node->pData)) < abs(max - *(node->pData)))
			return min;
		else
			return max;
	}

	BinarySearchTree<T>* RemoveKey(T x) 
	{
		BinarySearchTree<T> *node, *tempRoot;
		BinarySearchTree<T> **parentLink;
		T value;
		node = SearchKey(x);

		// TO DO daca e radinca

		if (node == NULL)
			return this;

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
		
		value = FindClosest(node);
		tempRoot = this;
		tempRoot = RemoveKey(value);
		*(node->pData) = value;

		return tempRoot;
	}
};

#endif // __BINARY_SEARCH_TREE_H