#include <iostream>

#define DEFAULT_SIZE 16

template <typename T>
class Array
{
private:
	T *arr;
	int len = 0;	// User
	int size = 0;	// Actual

public:

	Array();			// Create a dynamic array of size DEFAULT_SIZE
	Array(int size);		// Create a dynamic array of size s
	// Array(T arr[]);
	// Array(T arr[], int s);

	T get(int);
	T removeAt(int);

	bool isEmpty();
	bool remove(T);	// remove element T
	bool contains(T);

	int Size();
	int getIndex(T);

	void set(int, T);
	void clear();
	void add(T);

};

template <typename T>
Array<T>::Array()
{
	this->size = DEFAULT_SIZE;
	arr = new T[DEFAULT_SIZE];
}

template <typename T>
Array<T>::Array(int size)
{
	if (size < 0) {
		std::cout << "Illegal size: " << size;
	}

	this->size = size;
	arr = new T[size];
}

template <typename T>
int Array<T>::Size()
{
	return len;
}

template <typename T>
bool Array<T>::isEmpty()
{
	return Array::Size() == 0;
}


template <typename T>
T Array<T>::get(int index)
{
	if (index >= 0 && index < size) {
		return arr[index];
	}
	// what do we return if index is out of bounds?
	return T(NULL);
}

template <typename T>
void Array<T>::set(int index, T element)
{
	if (index >= 0 && index < size) {
		arr[index] = element;
	}
}

template <typename T>
void Array<T>::clear()
{
	// only the elements are cleared; array is not deallocated
	for (int i = 0; i < len; ++i) {
		arr[i]	= T(NULL);
	}
	len = 0;
}

template <typename T>
void Array<T>::add(T element)
{
	if (len + 1 >= size) {
		if (size == 0) {
			size = 1;
		} else {
			size *= 2;
		}

		T *tmp_arr = new T[size];
		for (int i = 0; i < len; ++i) {	// move all the elements into the new array
			tmp_arr[i] = arr[i];
		}
		delete[] arr;	// dealocate the space used by the old array
		arr = tmp_arr;
	}

	arr[len++] = element;
}

template <typename T>
int Array<T>::getIndex(T element)
{
	for (int i = 0; i < len; ++i) {
		if (element == arr[i]) {
			return i;
		}
	}

	return -1;
}


template <typename T>
T Array<T>::removeAt(int index)
{
	if (index < 0 || index >= len) {
		// throw exception
	}

	T ele = arr[index];

	--len;

	// shift all the elements after the index
	for (int i = index; i < len; ++i) {
		arr[i] = arr[i+1];
	}

	return ele;
}

template <typename T>
bool Array<T>::remove(T element)
{
	int index = getIndex(element);
	if (index == -1) {
		return false;
	}

	removeAt(index);
	return true;
}

template <typename T>
bool Array<T>::contains(T element)
{
	return (Array::getIndex(element) != -1);
}

int main()
{
	Array<int> def;
	Array<int> a(10);

	// std::cout << "size of def: " << def.Size() << std::endl;
	// std::cout << "size of a: " << a.Size() << std::endl;

	// if (def.isEmpty()) {
	// 	std::cout << "def arr empty" << std::endl;
	// } else {
	// 	std::cout << "def arr not empty" << std::endl;
	// }

	// a.set(8, 20);
	// std::cout << "a[10]: " << a.get(8) << std::endl;

	// a.clear();
	// if (a.isEmpty()) {
	// 	std::cout << "a arr empty" << std::endl;
	// } else {
	// 	std::cout << "a arr not empty" << std::endl;
	// }

	for (int i = 0; i < 100; ++i) {
		a.add(i*2);
	}

	for (int i = 0; i < 50; ++i) {
		a.removeAt(i);
	}

	a.remove(6);
	// for (int i = 0; i < 50; ++i) {
	// 	std::cout << "a[" << i << "]: " << a.get(i) << std::endl;
	// }
	std::cout << a.contains(6) << std::endl;


	return 0;
}
