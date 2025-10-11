#pragma once
#include <stdexcept>
#include <functional>
#include <stack>
#include <queue>
#include "Node.h"
#include "IComparable.h"


template<typename T>
class BinaryTree
{
private:
	Node<T>* m_root;
	unsigned int m_depth;

	Node<T>* findNode(T item)
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

	bool insert(T data)
	{
		if (m_root == nullptr)
		{
			m_root = new Node<T>(data, nullptr);
			m_depth = 1;
			return true;
		}

		int depth = 1;
		Node<T>* currentNode = m_root;
		while (true)
		{
			int cmp = currentNode->getData()->compare(data);
			if (cmp == 0)
			{
				return false;
			}
			else if (cmp == -1)
			{
				++depth;
				if (currentNode->leftChild() == nullptr)
				{
					currentNode->setLeftChild(new Node<T>(data, currentNode));
					break;
				}
				currentNode = currentNode->leftChild();
			}
			else
			{
				++depth;
				if (currentNode->rightChild() == nullptr)
				{
					currentNode->setRightChild(new Node<T>(data, currentNode));
					break;
				}
				currentNode = currentNode->rightChild();
			}
		}

		if (depth > m_depth)
		{
			m_depth = depth;
		}

		return true;
	}

	int depth()
	{
		return m_depth;
	}

	T find(T item)
	{
		return findNode(item)->getData();
	}

	T remove(T item)
	{
		Node<T>* currentNode = findNode(item);
		if (currentNode == nullptr)
		{
			return nullptr;
		}

		if (currentNode->leftChild() != nullptr && currentNode->rightChild() != nullptr)
		{
			Node<T>* successor = currentNode->rightChild();

			while (successor->leftChild() != nullptr)
			{
				successor = successor->leftChild();
			}

			currentNode->setData(successor->getData());
			currentNode = successor;
		}

		Node<T>* child = currentNode->leftChild() != nullptr ? currentNode->leftChild() : currentNode->rightChild();
		if (child != nullptr)
		{
			child->setAncestor(currentNode->getAncestor());
		}

		if (currentNode->getAncestor() == nullptr)
		{
			m_root = child;
		}
		else if (currentNode == currentNode->getAncestor()->leftChild())
		{
			currentNode->getAncestor()->setLeftChild(child);
		}
		else
		{
			currentNode->getAncestor()->setRightChild(child);
		}

		T data = currentNode->getData();
		delete currentNode;
		return data;
	}

	void processInOrder(std::function<void(T)> process)
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

	void processPostOrder(std::function<void(T)> process)
	{
		postOrderTraversal([&](Node<T>* node) {
			process(node->getData());
		});
	}

	void processPreOrder(std::function<void(T)> process)
	{
		if (m_root == nullptr)
		{
			throw std::runtime_error("Trying to process empty tree");
		}

		std::stack<Node<T>*> stack;
		stack.push(m_root);

		while (!stack.empty())
		{
			Node<T>* currentNode = stack.top();
			stack.pop();

			process(currentNode->getData());

			if (currentNode->rightChild() != nullptr)
			{
				stack.push(currentNode->rightChild());
			}
			if (currentNode->leftChild() != nullptr)
			{
				stack.push(currentNode->leftChild());
			}
		}
	}

	void processLevelOrder(std::function<void(T)> process)
	{
		if (m_root == nullptr)
		{
			throw std::runtime_error("Trying to process empty tree");
		}

		std::queue<Node<T>*> queue;
		queue.push(m_root);

		while (!queue.empty())
		{
			Node<T>* currentNode = queue.front();
			queue.pop();

			process(currentNode->getData());

			if (currentNode->leftChild() != nullptr)
			{
				queue.push(currentNode->leftChild());
			}
			if (currentNode->rightChild() != nullptr)
			{
				queue.push(currentNode->rightChild());
			}
		}
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