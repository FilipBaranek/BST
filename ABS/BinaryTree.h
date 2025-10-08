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
				return currentNode->getData();
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
					process(topNode->getData());
					lastNode = stack.top();
					stack.pop();
				}
			}
		}
	}

	void clear()
	{
		if (m_root == nullptr)
		{
			return;
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
					stack.pop();
					lastNode = topNode;
					delete topNode;
					currentNode = nullptr;
				}
			}
		}

		m_root = nullptr;
		m_depth = 0;
	}

	~BinaryTree()
	{
		clear();
	}
};