#pragma once
#include <utility>
#include "IComparable.h"

template<typename T>
class Node
{
	static_assert(std::is_base_of_v<IComparable, std::remove_pointer_t<T>>, "T must inherit from IComparable");

private:
	T m_data;
	Node<T>* m_ancestor;
	Node<T>* m_leftChild;
	Node<T>* m_rightChild;

public:
	Node(T data, Node<T>* ancestor)
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

	void setAncestor(Node* ancestor)
	{
		m_ancestor = ancestor;
	}

	void setRightChild(Node* rightChild)
	{
		m_rightChild = rightChild;
	}

	void setLeftChild(Node* leftChild)
	{
		m_leftChild = leftChild;
	}

	T getData()
	{
		return m_data;
	}

	Node* getAncestor()
	{
		return m_ancestor;
	}

	Node* leftChild()
	{
		return m_leftChild;
	}

	Node* rightChild()
	{
		return m_rightChild;
	}

	~Node() = default;
};