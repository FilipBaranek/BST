#pragma once
#include "BinarySearchTree.h"
#include "AVLNode.h"

template<typename T>
class AVLTree : public BinarySearchTree<T>
{
//Destructor intentionaly inherited

private:
	void rotateLeft(AVLNode<T>* a)
	{
		AVLNode<T>* b = static_cast<AVLNode<T>*>(a->rightChild());
		AVLNode<T>* ancestor = static_cast<AVLNode<T>*>(a->getAncestor());

		if (b->leftChild() != nullptr)
		{
			b->leftChild()->setAncestor(a);
		}
		
		a->setRightChild(b->leftChild());
		b->setLeftChild(a);
		a->setAncestor(b);
		b->setAncestor(ancestor);
		
		if (ancestor == nullptr)
		{
			this->m_root = b;
		}
		else if (ancestor->leftChild() == a)
		{
			ancestor->setLeftChild(b);
		}
		else
		{
			ancestor->setRightChild(b);
		}

		a->updateBalanceFactor();
		b->updateBalanceFactor();
	}

	void rotateRight(AVLNode<T>* a)
	{
		AVLNode<T>* b = static_cast<AVLNode<T>*>(a->leftChild());
		AVLNode<T>* ancestor = static_cast<AVLNode<T>*>(a->getAncestor());

		if (b->rightChild() != nullptr)
		{
			b->rightChild()->setAncestor(a);
		}

		a->setLeftChild(b->rightChild());
		b->setRightChild(a);
		a->setAncestor(b);
		b->setAncestor(ancestor);

		if (ancestor == nullptr)
		{
			this->m_root = b;
		}
		else if (ancestor->leftChild() == a)
		{
			ancestor->setLeftChild(b);
		}
		else
		{
			ancestor->setRightChild(b);
		}

		a->updateBalanceFactor();
		b->updateBalanceFactor();
	}

	void rebalance(AVLNode<T>* node)
	{
		AVLNode<T>* current = node;

		while (current != nullptr)
		{
			current->updateBalanceFactor();

			if (!current->isBalanced())
			{
				AVLNode<T>* parent = static_cast<AVLNode<T>*>(current->getAncestor());
				if (current->balanceFactor() < -1)
				{
					if (static_cast<AVLNode<T>*>(current->rightChild())->balanceFactor() <= 0)
					{
						// RR
						rotateLeft(current);
					}
					else
					{
						// RL
						rotateRight(static_cast<AVLNode<T>*>(current->rightChild()));
						rotateLeft(current);
					}
				}
				else if (current->balanceFactor() > 1)
				{
					if (static_cast<AVLNode<T>*>(current->leftChild())->balanceFactor() >= 0)
					{
						//LL
						rotateRight(current);
					}
					else
					{
						//LR
						rotateLeft(static_cast<AVLNode<T>*>(current->leftChild()));
						rotateRight(current);
					}
				}
				break;
			}
			current = static_cast<AVLNode<T>*>(current->getAncestor());
		}
	}

public:
	bool insert(T data) override
	{
		AVLNode<T>* insertedNode = static_cast<AVLNode<T>*>(this->insertNode<AVLNode<T>>(data));
		if (insertedNode == nullptr)
		{
			return false;
		}

		rebalance(insertedNode);
		return true;
	}

	T remove(T& key) override
	{
		AVLNode<T>* rebalanceStartingNode = static_cast<AVLNode<T>*>(this->removeNode(key).m_removedNodeAncestor);
		rebalance(rebalanceStartingNode);

		return nullptr;
	}

	unsigned int depth()
	{
		return static_cast<AVLNode<T>*>(this->m_root)->height();
	}
};