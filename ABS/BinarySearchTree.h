#pragma once
#include <stdexcept>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include "BSTNode.h"
#include "IComparable.h"

template<typename T, typename Node = BSTNode<T>>
class BinarySearchTree
{
private:
	unsigned int m_depth;

	Node* findNode(T key)
	{
		if (m_root == nullptr)
		{
			return nullptr;
		}

		Node* currentNode = m_root;
		while (true)
		{
			int cmp = currentNode->getData()->compare(key);

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

	Node* findMinKeyNode(Node* startingNode)
	{
		Node* currentNode = startingNode;
		while (currentNode->leftChild() != nullptr)
		{
			currentNode = currentNode->leftChild();
		}

		return currentNode;
	}

	Node* findMaxKeyNode(Node* startingNode)
	{
		Node* currentNode = startingNode;
		while (currentNode->rightChild() != nullptr)
		{
			currentNode = currentNode->rightChild();
		}

		return currentNode;
	}

	void postOrderTraversal(std::function<void(Node*)> process)
	{
		if (m_root == nullptr)
		{
			throw std::runtime_error("Trying to process empty tree");
		}

		std::stack<BSTNode<T>*> stack;
		BSTNode<T>* lastNode = nullptr;
		BSTNode<T>* currentNode = m_root;

		while (!stack.empty() || currentNode != nullptr)
		{
			if (currentNode != nullptr)
			{
				stack.push(currentNode);
				currentNode = currentNode->leftChild();
			}
			else
			{
				BSTNode<T>* topNode = stack.top();

				if (topNode->rightChild() != nullptr && lastNode != topNode->rightChild())
				{
					currentNode = topNode->rightChild();
				}
				else
				{
					process(static_cast<Node*>(topNode));
					lastNode = topNode;
					stack.pop();
				}
			}
		}
	}

protected:
	Node* m_root;

	BSTNode<T>* insertNode(T data)
	{
		if (m_root == nullptr)
		{
			m_root = new Node(data, nullptr);
			m_depth = 1;
			return m_root;
		}

		int depth = 1;
		BSTNode<T>* currentNode = m_root;
		BSTNode<T>* newNode;
		while (true)
		{
			int cmp = currentNode->getData()->compare(data);
			if (cmp == 0)
			{
				return nullptr;
			}
			else if (cmp == -1)
			{
				++depth;
				if (currentNode->leftChild() == nullptr)
				{
					newNode = new Node(data, currentNode);
					currentNode->setLeftChild(newNode);
					break;
				}
				currentNode = currentNode->leftChild();
			}
			else
			{
				++depth;
				if (currentNode->rightChild() == nullptr)
				{
					newNode = new Node(data, currentNode);
					currentNode->setRightChild(newNode);
					break;
				}
				currentNode = currentNode->rightChild();
			}
		}

		if (depth > m_depth)
		{
			m_depth = depth;
		}

		return newNode;
	}

public:
	BinarySearchTree()
	{
		m_root = nullptr;
		m_depth = 0;
	}

	virtual bool insert(T data)
	{
		return insertNode(data) != nullptr;
	}

	virtual unsigned int depth()
	{
		return m_depth;
	}

	T find(T& key)
	{
		return findNode(key)->getData();
	}

	bool find(T lowestKey, T highestKey, std::vector<T>& outputInterval)
	{
		//TODO///////

		if (m_root == nullptr)
		{
			return false;
		}


		return true;
	}

	T findMinKey()
	{
		return findMinKeyNode(m_root)->getData();
	}

	T findMaxKey()
	{
		return findMaxKeyNode(m_root)->getData();
	}

	virtual T remove(T& key)
	{
		Node* currentNode = findNode(key);
		if (currentNode == nullptr)
		{
			return nullptr;
		}

		T data = currentNode->getData();
		Node* ancestor = currentNode->getAncestor();
		int childCount = currentNode->childCount();
		
		if (childCount == 0)
		{
			if (ancestor == nullptr)
			{
				m_root = nullptr;
			}
			else if (ancestor->leftChild() == currentNode)
			{
				ancestor->setLeftChild(nullptr);
			}
			else
			{
				ancestor->setRightChild(nullptr);
			}
			delete currentNode;
		}
		else if (childCount == 1)
		{
			Node* child = currentNode->leftChild() != nullptr ? currentNode->leftChild() : currentNode->rightChild(); //Might be intentionaly nullptr if has no child
			if (ancestor == nullptr)
			{
				m_root = child;
				child->setAncestor(nullptr);
			}
			else
			{
				if (ancestor->leftChild() == currentNode)
				{
					ancestor->setLeftChild(child);
				}
				else
				{
					ancestor->setRightChild(child);
				}
				child->setAncestor(ancestor);
			}
			delete currentNode;
		}
		else
		{
			Node* swapNode = findMinKeyNode(currentNode->rightChild());
			currentNode->setData(swapNode->getData());
			Node* swapNodeAncestor = swapNode->getAncestor();
			Node* swapNodeChild = swapNode->rightChild();	//Only possible child

			if (swapNodeAncestor->leftChild() == swapNode)
			{
				swapNodeAncestor->setLeftChild(swapNodeChild);
			}
			else
			{
				swapNodeAncestor->setRightChild(swapNodeChild);
			}


			if (swapNodeChild != nullptr)
			{
				swapNodeChild->setAncestor(swapNodeAncestor);
			}
			delete swapNode;
		}

		return data;
	}

	void processInOrder(std::function<void(T)> process)
	{
		if (m_root == nullptr)
		{
			throw std::runtime_error("Trying to process empty tree");
		}

		Node* currentNode = m_root;
		while (currentNode != nullptr)
		{
			if (currentNode->leftChild() == nullptr)
			{
				process(currentNode->getData());
				currentNode = currentNode->rightChild();
			}
			else
			{
				Node* predecessor = currentNode->leftChild();
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
		postOrderTraversal([&](Node* node) {
			process(node->getData());
		});
	}

	void processPreOrder(std::function<void(T)> process)
	{
		if (m_root == nullptr)
		{
			throw std::runtime_error("Trying to process empty tree");
		}

		std::stack<Node*> stack;
		stack.push(m_root);

		while (!stack.empty())
		{
			Node* currentNode = stack.top();
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

		std::queue<Node*> queue;
		queue.push(m_root);

		while (!queue.empty())
		{
			Node* currentNode = queue.front();
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
		postOrderTraversal([&](Node* node) {
			delete node;
		});

		m_root = nullptr;
		m_depth = 0;
	}
	
	~BinarySearchTree()
	{
		clear();
	}
};