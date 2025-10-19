#pragma once
#include <vector>
#include <map>
#include "Tester.h"
#include "Number.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"


class CommonTester : public Tester
{
private:
	std::vector<Number*> m_randomData;
	BinarySearchTree<Number*> m_bst;
	AVLTree<Number*> m_at;

public:
	CommonTester(const char* name);
	void testInsertion() override;
	void testRemoval() override;
	void testPointSearch() override;
	void testIntervalSearch() override;
	void testFindMinKey() override;
	void testFindMaxKey() override;
	void generateInterval(int& minKey, int& maxKey);
	~CommonTester() override;
};