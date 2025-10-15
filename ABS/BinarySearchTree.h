#pragma once
#include <stdexcept>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include "BSTNode.h"
#include "IComparable.h"

template<typename T>
struct RemoveData
{
	BSTNode<T>* m_removedNodeAncestor;
	T m_data;
};

template<typename T>
class BinarySearchTree
{
private:

	unsigned int m_size = 0;
	unsigned int m_depth = 0;

	BSTNode<T>* findNode(T& key)
	{
		if (m_root == nullptr)
		{
			return nullptr;
		}

		BSTNode<T>* currentNode = m_root;
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

	BSTNode<T>* findMinKeyNode(BSTNode<T>* startingNode)
	{
		BSTNode<T>* currentNode = startingNode;
		while (currentNode->leftChild() != nullptr)
		{
			currentNode = currentNode->leftChild();
		}

		return currentNode;
	}

	BSTNode<T>* findMaxKeyNode(BSTNode<T>* startingNode)
	{
		BSTNode<T>* currentNode = startingNode;
		while (currentNode->rightChild() != nullptr)
		{
			currentNode = currentNode->rightChild();
		}

		return currentNode;
	}

	void postOrderTraversal(std::function<void(BSTNode<T>*)> process)
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
					process(topNode);
					lastNode = topNode;
					stack.pop();
				}
			}
		}
	}

protected:
	BSTNode<T>* m_root;

	template<typename Node>
	BSTNode<T>* insertNode(T data)
	{
		static_assert(std::is_base_of_v<BSTNode<T>, Node>, "Node must inherit from BSTNode<T>");

		if (m_root == nullptr)
		{
			m_root = new Node(data, nullptr);
			m_depth = 1;
			++m_size;
			return m_root;
		}

		unsigned int depth = 1;
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
		++m_size;

		return newNode;
	}

	RemoveData<T> removeNode(T& key)
	{
		BSTNode<T>* currentNode = findNode(key);
		if (currentNode == nullptr)
		{
			return {};
		}

		T data = currentNode->getData();
		BSTNode<T>* ancestor = currentNode->getAncestor();
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
			BSTNode<T>* child = currentNode->leftChild() != nullptr ? currentNode->leftChild() : currentNode->rightChild(); //Might be intentionaly nullptr if has no child
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
			BSTNode<T>* swapNode = findMinKeyNode(currentNode->rightChild());
			currentNode->setData(swapNode->getData());
			BSTNode<T>* swapNodeAncestor = swapNode->getAncestor();
			BSTNode<T>* swapNodeChild = swapNode->rightChild();	//Only possible child

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

			ancestor = swapNodeAncestor;
			delete swapNode;
		}

		--m_size;
		return { ancestor, data };
	}

public:
	BinarySearchTree()
	{
		m_root = nullptr;
		m_depth = 0;
	}

	unsigned int size()
	{
		return m_size;
	}

	virtual unsigned int depth()
	{
		return m_depth;
	}

	virtual bool insert(T data)
	{
		return insertNode<BSTNode<T>>(data) != nullptr;
	}

	T find(T& key)
	{
		return findNode(key)->getData();
	}

	bool find(T lowestKey, T highestKey, std::vector<T>& outputInterval)
	{
		if (m_root == nullptr)
		{
			return false;
		}
		
		std::stack<BSTNode<T>*> stack;
		stack.push(m_root);

		while (!stack.empty())
		{
			BSTNode<T>* currentNode = stack.top();
			stack.pop();

			int cmpLowest = currentNode->getData()->compare(lowestKey);
			int cmpHighest = currentNode->getData()->compare(highestKey);

			if (cmpLowest == -1 && currentNode->leftChild() != nullptr)
			{
				stack.push(currentNode->leftChild());
			}
			if (cmpLowest != -1 && cmpHighest != 1)
			{
				outputInterval.push_back(currentNode->getData());
			}
			if (cmpHighest == 1 && currentNode->rightChild() != nullptr)
			{
				stack.push(currentNode->rightChild());
			}
		}

		return !outputInterval.empty();
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
		return removeNode(key).m_data;
	}

	void processInOrder(std::function<void(T)> process)
	{
		if (m_root == nullptr)
		{
			throw std::runtime_error("Trying to process empty tree");
		}

		BSTNode<T>* currentNode = m_root;
		while (currentNode != nullptr)
		{
			if (currentNode->leftChild() == nullptr)
			{
				process(currentNode->getData());
				currentNode = currentNode->rightChild();
			}
			else
			{
				BSTNode<T>* predecessor = currentNode->leftChild();
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
		postOrderTraversal([&](BSTNode<T>* node) {
			process(node->getData());
		});
	}

	void processPreOrder(std::function<void(T)> process)
	{
		if (m_root == nullptr)
		{
			throw std::runtime_error("Trying to process empty tree");
		}

		std::stack<BSTNode<T>*> stack;
		stack.push(m_root);

		while (!stack.empty())
		{
			BSTNode<T>* currentNode = stack.top();
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

		std::queue<BSTNode<T>*> queue;
		queue.push(m_root);

		while (!queue.empty())
		{
			BSTNode<T>* currentNode = queue.front();
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
		postOrderTraversal([&](BSTNode<T>* node) {
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