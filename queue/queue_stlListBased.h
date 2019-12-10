#pragma once

#include <list>
#include <stdexcept>

template <typename T>
class Queue
{
private:
	std::list<T> q;

public:
	Queue() {}

	Queue(T ele)
	{
		q.push_back(ele);
	}

	T dequeue();
	T peek();
	
	void enqueue(T);

	int size();

	bool isEmpty();
};

template <typename T>
void Queue<T>::enqueue(T ele)
{
	q.push_back(ele);
}

template <typename T>
T Queue<T>::dequeue()
{
	if (Queue<T>::isEmpty()) {
		throw std::underflow_error("Queue empty");
	}

	T front_ele = q.front();
	q.pop_front();
	return front_ele;
}

template <typename T>
T Queue<T>::peek()
{
	if (Queue<T>::isEmpty()) {
		throw std::underflow_error("Queue empty");
	}

	return q.front();
}

template <typename T>
bool Queue<T>::isEmpty()
{
	return q.empty();
}

template <typename T>
int Queue<T>::size()
{
	return q.size();
}