#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "AVL.h"

#define REMOVE_KEY 0

int main(int argc,char** argv)
{
	if (argc!=2)
	{
		std::cerr<<"Usage: "<<argv[0]<<" inputFile"<<std::endl;
		exit(0);
	}
	//open file
	std::ifstream in(argv[1],std::ios::in);
	if (!in.is_open())
	{
		std::cerr<<"Invalid input file:"<<argv[0]<<std::endl;
		exit(0);
	}

	//read data from file
	int nNumbers,key;
	in>>nNumbers;
	std::vector<int> numbers;
	for (int i=0;i<nNumbers;i++)
	{
		int nReadNumber;
		in>>nReadNumber;
		numbers.push_back(nReadNumber);
	}
	in.close();

	//insert numbers in BST
	std::cout<<"==============[3]Element insert==============="<<std::endl;
	AVLnode<int> *root=new AVLnode<int>();
	for (std::vector<int>::iterator it=numbers.begin();it!=numbers.end();it++)
	{
		root = root->InsertKey(*it);
	}

	//search for ten elements
	std::cout<<"==============[4]Element search==============="<<std::endl;
	srand(time(NULL));
	for (int i=0;i<2;i++)
	{
		int pos=rand()%nNumbers;
		key=numbers[pos];
		if (root->SearchKey(key))
			std::cout<<"Element "<<key<<" found"<<std::endl;
		else
			std::cout<<"[ERROR]Element "<<key<<" not found"<<std::endl;
	}
	key=100;
	if (root->SearchKey(key))
			std::cout<<"Element "<<key<<" found"<<std::endl;
		else
			std::cout<<"Element "<<key<<" not found"<<std::endl;

	//display
	std::cout<<"==============[5]InOrder Display=============="<<std::endl;
	root->InOrderDisplay(root);
	std::cout<<std::endl;

	root->bfs(root);

	//remove two elements
	std::cout<<"================[6]Remove key================="<<std::endl;
	for (int i=0;i<2;i++)
	{
		int pos=rand()%nNumbers;
		key=numbers[pos];
		root=root->RemoveKey(key);
		if (root->SearchKey(key))
			std::cout<<"[ERROR]Element "<<key<<" found. "<<std::endl;
		else
			std::cout<<"Element "<<key<<" not found"<<std::endl;
	}
	

	root->RemoveSelf();
	return 0;
}
