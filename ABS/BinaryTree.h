#pragma once
#include <stdexcept>
#include <functional>
#include <stack>
#include "Node.h"
#include "IComparable.h"


template<typename T>
class BinaryTree
{
private:
	Node<T>* m_root;
	size_t m_depth;

	Node<T>* findNode(IComparable* item)
	{
		if (m_root == nullptr)
		{
			return nullptr;
		}

		Node<T>* currentNode = m_root;
		while (true)
		{
			int cmp = currentNode->getData()->compare(item);

			if (cmp == 0)
			{
				return currentNode;
			}
			else if (cmp == -1)
			{
				if (currentNode->leftChild() == nullptr)
				{
					return nullptr;
				}
				currentNode = currentNode->leftChild();
			}
			else if (cmp == 1)
			{
				if (currentNode->rightChild() == nullptr)
				{
					return nullptr;
				}
				currentNode = currentNode->rightChild();
			}
		}
	}

	void postOrderTraversal(std::function<void(Node<T>*)> process)
	{
		if (m_root == nullptr)
		{
			throw std::runtime_error("Trying to process empty tree");
		}

		std::stack<Node<T>*> stack;
		Node<T>* lastNode = nullptr;
		Node<T>* currentNode = m_root;

		while (!stack.empty() || currentNode != nullptr)
		{
			if (currentNode != nullptr)
			{
				stack.push(currentNode);
				currentNode = currentNode->leftChild();
			}
			else
			{
				Node<T>* topNode = stack.top();

				if (topNode->rightChild() != nullptr && lastNode != topNode->rightChild())
				{
					currentNode = topNode->rightChild();
				}
				else
				{
					process(topNode);
					lastNode = topNode;
					stack.pop();
				}
			}
		}
	}

public:
	BinaryTree() = default;

	void insert(IComparable* data)
	{
		if (m_root == nullptr)
		{
			m_root = new Node<T>(data, nullptr);
			return;
		}

		Node<T>* currentNode = m_root;
		while (true)
		{
			int cmp = currentNode->getData()->compare(data);
			if (cmp == 0)
			{
				throw std::runtime_error("Item is already inside the tree");
			}
			else if (cmp == -1)
			{
				if (currentNode->leftChild() == nullptr)
				{
					currentNode->setLeftChild(new Node<T>(data, currentNode));
					break;
				}
				currentNode = currentNode->leftChild();
			}
			else
			{
				if (currentNode->rightChild() == nullptr)
				{
					currentNode->setRightChild(new Node<T>(data, currentNode));
					break;
				}
				currentNode = currentNode->rightChild();
			}
		}
	}

	IComparable* find(IComparable* item)
	{
		return findNode(item)->getData();
	}

	void remove(IComparable* item)
	{
		Node<T>* currentNode = findNode(item);
		if (currentNode == nullptr)
		{
			throw std::runtime_error("Item is not in the tree");
		}

		/////////////////////////TODO//////////////////////////
	}

	void processInOrder(std::function<void(IComparable*)> process)
	{
		if (m_root == nullptr)
		{
			throw std::runtime_error("Trying to process empty tree");
		}

		Node<T>* currentNode = m_root;
		while (currentNode != nullptr)
		{
			if (currentNode->leftChild() == nullptr)
			{
				process(currentNode->getData());
				currentNode = currentNode->rightChild();
			}
			else
			{
				Node<T>* predecessor = currentNode->leftChild();
				while (predecessor->rightChild() != nullptr && predecessor->rightChild() != currentNode)
				{
					predecessor = predecessor->rightChild();
				}

				if (predecessor->rightChild() == nullptr)
				{
					predecessor->setRightChild(currentNode);
					currentNode = currentNode->leftChild();
				}
				else
				{
					predecessor->setRightChild(nullptr);
					process(currentNode->getData());
					currentNode = currentNode->rightChild();
				}
			}
		}
	}

	void processPostOrder(std::function<void(IComparable*)> process)
	{
		postOrderTraversal([&](Node<T>* node) {
			process(node->getData());
		});
	}

	void clear()
	{
		postOrderTraversal([&](Node<T>* node) {
			delete node;
		});

		m_root = nullptr;
		m_depth = 0;
	}

	~BinaryTree()
	{
		clear();
	}
};