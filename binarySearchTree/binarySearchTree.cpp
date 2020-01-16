#include <algorithm>
#include <iostream>
#include <cassert>

template <typename T>
class BinarySearchTree
{
private:
	int node_count_ = 0;

	class Node
	{
	private:
		T data_;
		Node *left_;
		Node *right_;

		Node* findMin(Node *node)
		{
			while (node->left_ != nullptr) {
				node = node->left_;
			}

			return node;
		}

		Node* findMax(Node *node)
		{
			while (node->right_ != nullptr) {
				node = node->right;
			}

			return node;
		}

		void removeChild(Node **child)
		{
			if ((*child)->left_ == nullptr) {
				// node to remove has right subtree or no sub tree
				Node *tmp = *child;
				*child = (*child)->right_;
				delete tmp;
			} else if ((*child)->right_ == nullptr) {
				// node to remove has left subtree or no sub tree
				Node *tmp = *child;
				*child = (*child)->left_;
				delete tmp;
			} else {
				// node has both left and right child; pick either
				// the largest value in the left subtree or the
				// smallest value in the right subtree

				// Get the smallest node in the right subtree
				Node *successor = findMin((*child)->right_);

				// swap the data
				(*child)->data_ = successor->data_;

				// remove the copied node
				(*child)->right_->remove(successor->data_);
			}
		}

	public:
		Node(T data, Node *left, Node *right):
			data_{data}, left_{left}, right_{right}
		{
		}

		void add(Node *node)
		{
			if (node->data_ < this->data_) { // add to the left sub tree
				if (this->left_ != nullptr) {
					this->left_->add(node);
				} else {
					this->left_ = node;
				}
			} else { // add to the right sub tree
				if (this->right_ != nullptr) {
					this->right_->add(node);
				} else {
					this->right_ = node;
				}
			}
		}

		void remove(T ele)
		{
			// to do: Refactor from using the this ptr in the current manner
			if (ele < this->data_) {
				if (ele == this->left_->data_) {
					// left child is the element to delete
					Node **ptr_to_left_ptr = &(this->left_);
					removeChild(ptr_to_left_ptr);
				} else {
					// check in left subtree
					this->left_->remove(ele);
				}
			} else if (ele > this->data_) {
				if (ele == this->right_->data_) {
					// right child is the element to delete
					Node **ptr_to_right_ptr = &(this->right_);
					removeChild(ptr_to_right_ptr);
				} else {
					// check in right subtree
					this->right_->remove(ele);
				}
			} else {
				// when root is the node to remove
				Node *tmp = this;
				removeChild(&tmp);
			}
		}

		bool contains_element(T ele)
		{
			if (this == nullptr) {
				// reached bottom and value not found
				// or no elements in tree
				return false;
			}

			if (ele < this->data_) {
				// check the left subtree
				this->left_->contains_element(ele);
			} else if (ele > this->data_) {
				// check the right subtree
				this->right_->contains_element(ele);
			} else {
				// element found
				return true;
			}
		}

		static int height(Node *node)
		{
			if (node == nullptr) {
				return 0;
			}

			return std::max(
				Node::height(node->left_),
				Node::height(node->right_)
				) + 1;
		}
	};

	Node *root_ = nullptr;

public:
	int size();
	int height();

	bool isEmpty();
	bool add(T);
	bool contains(T);
	bool remove(T);
};

template <typename T>
bool BinarySearchTree<T>::remove(T ele)
{
	if (!(BinarySearchTree<T>::contains(ele))) { // does not contain the element
		return false;
	}

	root_->remove(ele);
	--node_count_;
	return true;

}

template <typename T>
bool BinarySearchTree<T>::add(T ele)
{
	if (BinarySearchTree<T>::contains(ele)) {
		return false;
	} else {
		BinarySearchTree<T>::Node *node =
			new BinarySearchTree<T>::Node(ele, nullptr, nullptr);
		if (BinarySearchTree<T>::isEmpty()) {
			root_ = node;
		} else {
			root_->add(node);
		}
		++node_count_;
		return true;
	}
}

template <typename T>
bool BinarySearchTree<T>::contains(T ele)
{
	return root_->contains_element(ele);
}

template <typename T>
int BinarySearchTree<T>::size()
{
	return node_count_;
}

template <typename T>
bool BinarySearchTree<T>::isEmpty()
{
	return BinarySearchTree<T>::size() == 0;
}

template <typename T>
int BinarySearchTree<T>::height()
{
	return Node::height(root_);
}

int main()
{
	BinarySearchTree<int> a;
	a.add(10);
	a.add(100);
	a.add(9);
	a.add(11);
	a.add(2);

	a.remove(10);
	assert(3 == a.height());
	a.remove(2);
	assert(2 == a.height());
	a.remove(7);
	assert(2 == a.height());

}