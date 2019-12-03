#include <iostream>
#include <string>

template <typename T>
class DoublyLinkedList
{
private:
	class Node
	{
	private:
		T data;
		Node *next;
		Node *prev;

	public:
		Node(T data, Node *next, Node *prev)
		{
			this->data = data;
			this->next = next;
			this->prev = prev;
		}

		void setNext(Node *next)
		{
			this->next = next;
		}

		void setPrev(Node *prev)
		{
			this->prev = prev;
		}

		void setData(T data)
		{
			this->data = data;
		}

		Node* getNext()
		{
			return next;
		}

		Node* getPrev()
		{
			return prev;
		}

		T getData()
		{
			return data;
		}

		std::string toString()
		{
			return std::to_string(data);
		}
	};

	int len = 0;
	Node *head = nullptr;
	Node *tail = nullptr;

	T remove(Node*);

public:
	T peekFirst();
	T peekLast();
	T removeLast();
	T removeFirst();
	T removeAt(int);


	bool isEmpty();
	bool contains(T);

	int size();
	int indexOf(T);

	std::string toString();

	void clear();
	void add(T);
	void addLast(T);
	void addFirst(T);


};

template <typename T>
void DoublyLinkedList<T>::clear()
{
	Node *trav = head;
	while (trav != nullptr) {
		Node *temp = trav->next;
		delete trav;
		trav = temp;
	}

	head = tail = trav = nullptr;
	len = 0;
}

template <typename T>
int DoublyLinkedList<T>::size()
{
	return len;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty()
{
	return DoublyLinkedList<T>::size() == 0;
}

template <typename T>
void DoublyLinkedList<T>::add(T element)
{
	DoublyLinkedList<T>::addLast(element);
}

template <typename T>
void DoublyLinkedList<T>::addLast(T element)
{
	// Create a new node
	DoublyLinkedList<T>::Node *node = new DoublyLinkedList<T>::Node(element, nullptr, nullptr);

	// Add the node to the end of the linked list
	if (DoublyLinkedList<T>::isEmpty()) {
		head = node;
	} else {
		tail->setNext(node);
		node->setPrev(tail);
	}

	tail = node;

	++len;
}

template <typename T>
void DoublyLinkedList<T>::addFirst(T element)
{
	// Create a new node
	DoublyLinkedList<T>::Node *node = new DoublyLinkedList<T>::Node(element, nullptr, nullptr);

	// Add the node to the start of the linked list
	if (DoublyLinkedList<T>::isEmpty()) {
		DoublyLinkedList<T>::addLast(element);
	} else {
		head->setPrev(node);
		node->setNext(head);
		head = node;
		++len;
	}
}

template <typename T>
T DoublyLinkedList<T>::peekFirst()
{
	if (DoublyLinkedList<T>::isEmpty()) {
		throw std::runtime_error("Empty Linked List");
	} else {
		return head->getData();
	}
}

template <typename T>
T DoublyLinkedList<T>::peekLast()
{
	if (DoublyLinkedList<T>::isEmpty()) {
		throw std::runtime_error("Empty Linked List");
	} else {
		return tail->getData();
	}
}


template <typename T>
T DoublyLinkedList<T>::removeFirst()
{
	if (DoublyLinkedList<T>::isEmpty()) {
		throw std::runtime_error("Empty Linked List");
	}

	// get data of first node
	Node *first = head;
	T first_data = first->getData();

	// move head to next node
	head = head->getNext();
	head->setPrev(nullptr);

	// delete the node
	delete first;
	--len;

	if (DoublyLinkedList<T>::isEmpty()) {
		tail = nullptr;
	}

	return first_data;
}

template <typename T>
T DoublyLinkedList<T>::removeLast()
{
	if (DoublyLinkedList<T>::isEmpty()) {
		throw std::runtime_error("Empty Linked List");
	}

	T data = tail->getData();
	Node *last_node = tail;
	tail = tail->getPrev();

	delete last_node;
	--len;

	if (DoublyLinkedList<T>::isEmpty()) {
		head = nullptr;
	} else {
		tail->setNext(nullptr);
	}

	return data;
}

template <typename T>
T DoublyLinkedList<T>::remove(Node *node)
{
	if (node->getPrev() == nullptr) { // Node to delete is at the head
		DoublyLinkedList<T>::removeFirst();
	} else if (node->getNext() == nullptr) { // Node to delete is at the tail
		DoublyLinkedList<T>::removeLast();
	}

	T data = node->getData();

	(node->getPrev())->setNext(node->getNext());
	(node->getNext())->setPrev(node->getPrev());

	delete node;
	--len;

	return data;
}

template <typename T>
T DoublyLinkedList<T>::removeAt(int index)
{
	if (index < 0 || index >= len) {
		throw std::out_of_range("Invalid Index");
	}

	int i;
	Node *trav;

	if (index < len/2) { // Search from head
		for (i = 0, trav = head; i != index; ++i) {
			trav = trav->getNext();
		}
	} else {
		for (i = len-1, trav = tail; i != index; --i) {
			trav = trav->getPrev();
		}
	}

	return DoublyLinkedList<T>::remove(trav);
}

template <typename T>
int DoublyLinkedList<T>::indexOf(T data)
{
	int i = 0;
	Node *trav;
	for (trav = head; trav != nullptr; trav = trav->getNext()) {
		if (data == trav->getData()) {
			return i;
		}

		++i;
	}

	return -1;
}

template <typename T>
bool DoublyLinkedList<T>::contains(T data)
{
	return (DoublyLinkedList<T>::indexOf(data) != -1);
}

template <typename T>
std::string DoublyLinkedList<T>::toString()
{
	if (DoublyLinkedList<T>::isEmpty()) {
		return "[]";
	} else {
		std::string str;
		str.push_back('[');

		Node *trav;
		for (trav = head; trav != tail; trav = trav->getNext()) {
			str += trav->toString() + ", ";
		}
		str += tail->toString();
		str.push_back(']');

		return str;
	}

}

int main()
{
	DoublyLinkedList<int> a;
	for (int i = 0; i < 30; ++i) {
		a.add(2 * i);
	}

	std::cout << a.indexOf(2) << std::endl;
	std::cout << a.removeAt(1) << std::endl;
	std::cout << a.indexOf(2) << std::endl;
	std::cout << a.toString() << std::endl;


	return 0;
}
