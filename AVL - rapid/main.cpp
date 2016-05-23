// teste pentru AVL

#include <bits/stdc++.h>
#include "AVL.h"
using namespace std;

ofstream g("out");

int main() {
    srand(time(NULL));

    AVLnode<int> *root = new AVLnode<int>(1), *mn, *key;

    for (int i = 2; i <= 15; ++i){
        root = root->insert(i);
        mn = root->searchKey(i);
        g << mn->getData() << '\n';
    }

    root -> InOrderDisplay(root);
    cout << '\n';
    root->bfs(root);
    cout << root->getSons() << '\n';
    cout << root->getLeftSons() << '\n';
    cout << root->getRightSons() << '\n';
    cout << root->getSumData() <<'\n';
    cout << root->LCA(root->searchKey(7), root->searchKey(1))->getData() <<'\n';
    cout << root->LCA(root->searchKey(12), root->searchKey(1))->getData() <<'\n';
    cout << root->LCA(root->searchKey(9), root->searchKey(10))->getData() <<'\n';
    //cout << root->get
    //cout << root->rightNode->getSons() << '\n';
    delete root;
}
