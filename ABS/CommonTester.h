#pragma once
#include <vector>
#include <map>
#include "SpeedTester.h"
#include "Number.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"


class CommonTester : public SpeedTester
{
private:
	std::vector<Number*> m_randomData;
	std::map<Number*, int> m_rb;
	BinarySearchTree<Number*> m_bst;
	AVLTree<Number*> m_at;

public:
	CommonTester();
	void testInsertion() override;
	void testRemoval() override;
	void testPointSearch() override;
	void testIntervalSearch() override;
	void testFindMinKey() override;
	void testFindMaxKey() override;
	void generateInterval(int& minKey, int& maxKey);
	~CommonTester() override;
};