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

	bool isEmtpy();

	void push(T);
};

template <typename T>
int Stack<T>::size()
{
	return l.size();
}

template <typename T>
bool Stack<T>::isEmtpy()
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

int main()
{
	Stack<int> a(10);
	for (int i = 0; i < 30; ++i) {
		a.push(2 * i);
	}

	std::cout << "size(): " << a.size() << std::endl;

	for (int i = 0; i < 30; ++i) {
		std::cout << a.pop() << std::endl;
	}

	std::cout << "size(): " << a.size() << std::endl;
	std::cout << "isEmtpy(): " << a.isEmtpy() << std::endl;
	std::cout << a.peek() << std::endl;

	return 0;
}