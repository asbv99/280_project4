#ifndef LIST_H
#define LIST_H
/* List.h
*
* doubly-linked, double-ended list with Iterator interface
* EECS 280 Project 4
*/

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
	//OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

	//EFFECTS:  returns true if the list is empty
	bool empty() const {
		return first == nullptr;
	}

	//EFFECTS: returns the number of elements in this List
	int size() const {
		if (empty()) return 0;
		int count = 0;

		Node * current = first;
		while (current != last) {
			++count;
			current = current->next;
		}
		++count;
		return count;
	}

	//REQUIRES: list is not empty
	//EFFECTS: Returns the first element in the list by reference
	T & front() {
		assert(!empty());
		return first->datum;
	}

	//REQUIRES: list is not empty
	//EFFECTS: Returns the last element in the list by reference
	T & back() {
		assert(!empty());
		return last->datum;
	}

	//EFFECTS:  inserts datum into the front of the list
	void push_front(const T &datum) {
		Node * newNode = new Node;
		newNode->datum = datum;
		newNode->next = nullptr;
		newNode->prev = nullptr;

		if (empty()) {
			first = last = newNode;
		}

		else {
			first->prev = newNode;
			newNode->next = first;
			first = newNode;
		}
	}

	//EFFECTS:  inserts datum into the back of the list
	void push_back(const T &datum) {
		Node * newNode = new Node;
		newNode->datum = datum;
		newNode->next = nullptr;
		newNode->prev = nullptr;

		if (empty()) {
			first = newNode;
			last = newNode;
		}

		else {
			last->next = newNode;
			newNode->prev = last;
			last = newNode;
		}
	}

	//REQUIRES: list is not empty
	//MODIFIES: may invalidate list iterators
	//EFFECTS:  removes the item at the front of the list
	void pop_front() {
		assert(!empty());
		Node * victim = first;

		if (size() > 1) {
			first = first->next;
			first->prev = nullptr;
			delete victim;
		}
		else {
			last = nullptr;
			first = nullptr;
			delete victim;
		}
	}

	//REQUIRES: list is not empty
	//MODIFIES: may invalidate list iterators
	//EFFECTS:  removes the item at the back of the list
	void pop_back() {
		assert(!empty());
		Node * victim = last;

		if (size() > 1) {
			last = last->prev;
			last->next = nullptr;
			delete victim;
		}
		else {
			last = nullptr;
			first = nullptr;
			delete victim;
		}
	}

	// You should add in a default constructor, destructor, copy constructor,
	// and overloaded assignment operator, if appropriate. If these operations
	// will work correctly without defining these, you can omit them. A user
	// of the class must be able to create, copy, assign, and destroy Lists
	List()
		: first(nullptr), last(nullptr) {
	}

	~List() {
		pop_all();
	}

	List(const List<T> &other) {
		first = nullptr;
		last = nullptr;
		copy_all(other);
	}

	List & operator=(const List<T> &rhs) {
		if (this == &rhs) return *this;
		pop_all();
		copy_all(rhs);
		return *this;
	}

private:
	//a private type
	struct Node {
		Node *next;
		Node *prev;
		T datum;
	};

	//REQUIRES: list is empty
	//EFFECTS:  copies all nodes from other to this
	void copy_all(const List<T> &other) {
		assert(empty());

		//for (int i = 0; i < (int)other.size(); ++i) {
		//	Node *p = other.first;
		//	push_back(p->datum);
		//	p = p->next;
		//}

		for (Node * newNode = other.first; newNode != nullptr; newNode = newNode->next) {
			push_back(newNode->datum);
		}
	}

	//MODIFIES: may invalidate list iterators
	//EFFECTS:  removes all nodes
	void pop_all() {
		while (!empty()) {
			pop_front();
		}
	}

	Node *first;   // points to first Node in list, or nullptr if list is empty
	Node *last;    // points to last Node in list, or nullptr if list is empty

public:
	////////////////////////////////////////
	class Iterator {
		//OVERVIEW: Iterator interface to List

		// You should add in a default constructor, destructor, copy constructor,
		// and overloaded assignment operator, if appropriate. If these operations
		// will work correctly without defining these, you can omit them. A user
		// of the class must be able to create, copy, assign, and destroy Iterators.

		// Your iterator should implement the following public operators: *,
		// ++ (prefix), default constructor, == and !=.

	public:
		// This operator will be used to test your code. Do not modify it.
		// Requires that the current element is dereferenceable.
		Iterator & operator--() {
			assert(node_ptr);
			node_ptr = node_ptr->prev;
			return *this;
		}

		Iterator& operator++() {
			assert(node_ptr);
			node_ptr = node_ptr->next;
			return *this;
		}

		T& operator*() const {
			return node_ptr->datum;
		}

		bool operator==(Iterator rhs) const {
			return node_ptr == rhs.node_ptr;
		}

		bool operator!=(Iterator rhs) const {
			return node_ptr != rhs.node_ptr;
		}

		Iterator()
			: node_ptr(nullptr) {
		}

	private:
		Node * node_ptr; //current Iterator position is a List node
						 // add any additional necessary member variables here

						 // add any friend declarations here
		friend class List;

		// construct an Iterator at a specific position
		Iterator(Node *p)
			: node_ptr(p) {
		}

	};//List::Iterator
	  ////////////////////////////////////////

	  // return an Iterator pointing to the first element
	Iterator begin() const {
		return Iterator(first);
	}

	// return an Iterator pointing to "past the end"
	Iterator end() const {
		return Iterator();
	}

	//REQUIRES: i is a valid, dereferenceable iterator associated with this list
	//MODIFIES: may invalidate other list iterators
	//EFFECTS: Removes a single element from the list container
	void erase(Iterator i) {
		//assert(i.node_ptr);
		if (size() == 1) {
			first = nullptr;
			last = nullptr;
			delete i.node_ptr;;
		}
		else if (i.node_ptr == first) {
			pop_front();
		}
		else if (i.node_ptr == last) {
			pop_back();
		}
		else {
			Node *next = i.node_ptr->next;
			Node *prev = i.node_ptr->prev;

			next->prev = prev;
			prev->next = next;

			delete i.node_ptr;
			i.node_ptr = nullptr;
		}
	}

	//REQUIRES: i is a valid iterator associated with this list
	//EFFECTS: inserts datum before the element at the specified position.
	void insert(Iterator i, const T &datum) {
		//assert(i.node_ptr);
		//if (i.node_ptr == nullptr) {
		//	push_back(datum);
		//}
		if (i == first) {
			push_front(datum);
		}
		else {
			Node * newNode = new Node;

			newNode->datum = datum;
			newNode->next = i.node_ptr;
			i.node_ptr->prev->next = newNode;
			newNode->prev = i.node_ptr->prev;
			i.node_ptr->prev = newNode; 
		}
	}

};//List


  ////////////////////////////////////////////////////////////////////////////////
  // Add your member function implementations below or in the class above
  // (your choice). Do not change the public interface of List, although you
  // may add the Big Three if needed.  Do add the public member functions for
  // Iterator.


#endif
