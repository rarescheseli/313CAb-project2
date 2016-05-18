//Clasa list

#pragma once

using namespace std;

template<class T>
struct Node{
	T value;
	Node<T> *next;
	Node(T value) {
		this->value = value;
		next = NULL;
	}
	Node() {
		next = NULL;
	}
};

template <class T>
class iter
{
private:
	Node<T>* myNode;

public:
 	iter() {
  		myNode = NULL;
  	}
  	iter(Node<T> *node) {
  		myNode = node;
  	}
  	iter(const iter<T> &other) {
  		setIter(other.getIter());
  	}
  	iter &operator=(Node<T> *other) {
  		myNode = other;
  		//myNode = other.getIter();
  		//setIter(other.getIter());
  		return *this;
  	}

  	Node<T> *getIter() {
  		return myNode;
  	}

  	void setIter(Node<T> *node) {
  		myNode = node;
  	}

	iter<T> operator++() { 
		myNode = myNode->next;
	} 
	T operator*() {
		return myNode->value;
	}
};

template <class T>
class List {
private:
	Node<T> *begin, *end;
public:
	List();
	~List();
	List(const List &other);

	List<T> &operator=(const List<T> &other);

	bool empty() const;

	T front() const;
	T back() const;

	Node <T> *first() const;
	Node <T> *last() const;

	int getpos(T value) const;

	void push_back(T value);
	void push_front(T value);
	void insert(int pos, T value);

	void pop();
	void erase(int pos);
	void remove(T value);
	void remove_next(Node<T> *);

	int length() const;

	void clear();

	template<class Y>
	friend ostream& operator<<(ostream& out, const List<Y> &list);
};

//CONSTRUCTOR

template <class T>
List<T>::List() {
	begin = end = NULL;
}

//DESTRUCTOR

template<class T>
List<T>::~List() {
	clear();
}

//COPY-CONSTRUCTOR

template <class T>
List<T>::List(const List<T> &other) {
	Node<T> *current;
	begin = NULL;
	end = NULL;
	current = other.begin;
	while (current != NULL) {
		this->push_back(current->value);
		current = current->next;
	}
}

//COPY-ASSIGNMENT

template <class T>
List<T> & List<T>::operator=(const List<T> &other) {
	Node<T> *current;
	begin = NULL;
	end = NULL;
	current = other.begin;
	while (current != NULL) {
		this->push_back(current->value);
		current = current->next;
	}
	return *this;
}

//functions

template <class T>
bool List<T>::empty() const {
	if (begin == NULL) return true;
	else return false;
}

/*
presupun ca tipul de date T primit are un constructor default
daca T ar fi pointer, ar trebui returnat NULL
dar echivalentul lui NULL nu exista pentru tipuri de date
primitive, cum ar fi int
*/
template <class T>
T List<T>::front() const {
	if (begin) return begin->value;
	else return T();
}

template <class T>
T List<T>::back() const {
	if (end) return end->value;
	else return T();
}

template <class T>
Node <T> * List<T>::first() const {
	return begin;
}

template <class T>
Node <T> * List<T>::last() const {
	return end;
}

template <class T>
int List<T>::getpos(T value) const {
	if (empty()) return -1;
	Node<T> *current = begin;
	int pos = 0;
	while (current) {
		if (value == current->value) {
			return pos;
		}
		pos++;
		current = current->next;
	}
	return -1;
}

template <class T>
void List<T>::push_back(T value) {
	Node<T> *newNode = new Node<T>;
	newNode->value = value;
	newNode->next = NULL;
	if (!begin) {
		begin = end = newNode;
	}
	else {
		end->next = newNode;
		end = newNode;
	}
}
template <class T>
void List<T>::push_front(T value) {
	Node<T> *newNode = new Node<T>;
	newNode->value = value;
	newNode->next = NULL;
	if (!end) {
		begin = end = newNode;
	}
	else {
		newNode->next = begin;
		begin = newNode;
	}
}

template <class T>
void List<T>::insert(int pos, T value) {
	Node<T> *newNode, *current;
	current = begin;
	int poscrt;
	newNode = new Node<T>(value);
	while (current) {
		if (pos == poscrt) {
			newNode->next = current->next;
			current->next = newNode;
			break;
		}
		current = current->next;
		poscrt++;
	}
	if (newNode->next == NULL) {
		end = newNode;
	}
}

template <class T>
void List <T>::erase(int pos) {
	Node<T> *current = begin, *elemToRemove;
	int poscrt = 0;
	if (!current) return;
	if (pos == 0) {
		if (begin) {
			elemToRemove = begin;
			begin = begin->next;
			delete elemToRemove;
		}
		return;
	}
	while (current->next) {
		if (poscrt == pos - 1) { //delete elem
			elemToRemove = current->next;
			current->next = current->next->next;
			if (elemToRemove == end) {
				end = current;
			}
			delete elemToRemove;
			break;
		}
		current = current->next;
		poscrt++;
	}
}

template <class T>
void List<T>::remove(T value) {
	if (empty()) return;
	Node<T> *current = begin, *elemToRemove;
	if (value == begin->value)
	{
		elemToRemove = begin;
		begin = begin->next;
		delete elemToRemove;
	}
	while (current->next) {
		if (value == current->next->value) { //delete elem
			elemToRemove = current->next;
			current->next = current->next->next;
			if (elemToRemove == end) {
				end = current;
			}
			delete elemToRemove;
			return;
		}
		current = current->next;
	}
}

template <class T>
void List<T>::remove_next(Node<T> *node)
{
	if (!node->next) return;
	Node<T> *elemToRemove = node->next;
	if (elemToRemove == end) end = node;
	node->next = node->next->next;
	delete elemToRemove;
}

template <class T>
void List<T>::pop() {
	if (empty()) return;
	Node<T> *elemToRemove = begin;
	begin = begin->next;
	delete elemToRemove;
}

template <class T>
int List<T>::length() const {
	Node<T> *current = begin;
	int nr_elem = 0;
	while (current)
	{
		nr_elem++;
		current = current->next;
	}
	return nr_elem;
}
template <class T>
void List<T>::clear() {
	end = begin;
	while (end != NULL) {
		begin = end;
		end = end->next;
		delete begin;
	}
	begin = end = NULL;
}

template<class T>
ostream& operator<<(ostream& out, const List<T>& list) {
	Node<T> *current = list.begin;
	while (current) {
		out << current->value << " ";
		current = current->next;
	}
	out << "\n";
	return out;
}