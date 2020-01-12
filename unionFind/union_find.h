#pragma once

#include <vector>
#include <numeric> // std::iota
#include <stdexcept>

class UnionFind
{
private:
	int size;		// no of eles in union find
	std::vector<int> sz;	// size of each component
	std::vector<int> id;	// id[i] points to the parent of i, if id[i] == i then i is a root node
	int num_components;
public:
	UnionFind(int size)
	{
		if (size <= 0) {
			throw std::length_error("Invalid size");
		}

		this->size = size;
		this->num_components = size;

		(this->id).resize(size);
		(this->sz).resize(size);
		std::iota((this->id).begin(), (this->id).end(), 0); // Link to itself (self root)
		std::iota((this->sz).begin(), (this->sz).end(), 0); // Each component is initially of size one

	}

	int find(int p);	// find which component/set 'p' belongs to
	int componentSize(int p);
	int Size();
	int components();

	void unify(int p, int q);

	bool connected(int p, int q);	// returns whether 'p' and 'q' belong to the same component
};

int UnionFind::find(int p)
{
	// Get the root of p
	int root = p;
	while (root != (this->id)[root]) {
		root = (this->id)[root];
	}

	// perform path compression
	while (p != root) {
		int next = (this->id)[p];
		(this->id)[p] = root;
		p = next;
	}

	return root;
}

bool UnionFind::connected(int p, int q)
{
	return UnionFind::find(p) == UnionFind::find(q);
}

int UnionFind::componentSize(int p)
{
	return (this->sz)[UnionFind::find(p)];
}

int UnionFind::Size()
{
	return this->size;
}

int UnionFind::components()
{
	return this->num_components;
}

void UnionFind::unify(int p, int q)
{
	int root1 = UnionFind::find(p);
	int root2 = UnionFind::find(q);

	if (root1 == root2) {
		return;
	}

	// Merge smaller component into the larger one
	if ((this->sz)[root1] < (this->sz)[root1]) {
		(this->sz)[root2] += (this->sz)[root1];
		(this->id)[root1] = root2;
	} else {
		(this->sz)[root1] += (this->sz)[root2];
		(this->id)[root2] = root1;
	}

	--(this->num_components);
}
