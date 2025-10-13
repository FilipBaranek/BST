#pragma once
#include "BSTNode.h"

template<typename T>
class AVLNode : public BSTNode<T>
{
private:
	int m_balanceFactor;	//right subtree hight - left subtree hight //acceptable: -1, 0, 1

public:
	AVLNode(T data, BSTNode<T>* ancestor, int balanceFactor) : BSTNode<T>(data, ancestor)
	{
		m_balanceFactor = balanceFactor;
	}

	int getBalanceFactor()
	{
		return m_balanceFactor;
	}

	void operator++()
	{
		++m_balanceFactor;
	}

	void operator--()
	{
		--m_balanceFactor;
	}

	~AVLNode() = default;
};