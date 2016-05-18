#include <iostream>
#include "List.h"

using namespace std;

int main()
{
	List<int> l;
	cout << l.empty() << "\n";
	l.push_back(3);
	cout << l.front() << "\n";
	l.erase(0);
	l.push_back(4);
	l.push_front(2);
	l.erase(1);
	l.insert(0, 3);
	cout << l.empty() << "\n";
	//l.printList();
	cout << l;
	cout << l.back() << "\n";
	l.push_back(4);
	iter<int> it;
	it = l.first();
	cout << l;
	cout << *it << "\n";
	++it;
	cout << *it << "\n";
	++it;
	cout << *it << "\n";
	return 0;
}