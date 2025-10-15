#pragma once
#include <utility>
#include "IComparable.h"

template<typename T>
class BSTNode
{
	static_assert(std::is_base_of_v<IComparable, std::remove_pointer_t<T>>, "T must inherit from IComparable");

private:
	T m_data;
	BSTNode<T>* m_ancestor;
	BSTNode<T>* m_leftChild;
	BSTNode<T>* m_rightChild;

public:
	BSTNode(T data, BSTNode<T>* ancestor)
	{
		m_data = data;
		m_ancestor = ancestor;
		m_leftChild = nullptr;
		m_rightChild = nullptr;
	}

	void setData(T data)
	{
		m_data = data;
	}

	void setAncestor(BSTNode* ancestor)
	{
		m_ancestor = ancestor;
	}

	void setRightChild(BSTNode* rightChild)
	{
		m_rightChild = rightChild;
	}

	void setLeftChild(BSTNode* leftChild)
	{
		m_leftChild = leftChild;
	}

	int childCount()
	{
		int count = 0;
		
		if (m_leftChild != nullptr)
		{
			++count;
		}
		if (m_rightChild != nullptr)
		{
			++count;
		}

		return count;
	}

	T& getData()
	{
		return m_data;
	}

	BSTNode*& getAncestor()
	{
		return m_ancestor;
	}

	BSTNode*& leftChild()
	{
		return m_leftChild;
	}

	BSTNode*& rightChild()
	{
		return m_rightChild;
	}

	~BSTNode() = default;
};