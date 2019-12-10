#include <iostream>
#include <list>

template <typename T>
class Stack
{
private:
	std::list<T> l;

public:
	Stack(){}

	Stack(T first_elem)
	{
		Stack<T>::push(first_elem);
	}

	T pop();
	T peek();

	int size();

	bool isEmpty();

	void push(T);
};

template <typename T>
int Stack<T>::size()
{
	return l.size();
}

template <typename T>
bool Stack<T>::isEmpty()
{
	return l.empty();
}

template <typename T>
void Stack<T>::push(T ele)
{
	l.push_back(ele);
}

template <typename T>
T Stack<T>::pop()
{
	if (isEmtpy()) {
		throw std::underflow_error("Stack Empty!");
	}

	T top_ele = l.back();
	l.pop_back();
	return top_ele;
}

template <typename T>
T Stack<T>::peek()
{
	if (isEmtpy()) {
		throw std::underflow_error("Stack Empty!");
	}

	return l.back();
}