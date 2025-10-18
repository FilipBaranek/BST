#pragma once
#include <map>
#include <vector>
#include "Tester.h"

class MapTester : public Tester
{
private:
	std::vector<int> m_randomData;
	std::map<int, int> m_structure;

public:
	MapTester(const char* name);
	void testInsertion() override;
	void testRemoval() override;
	void testPointSearch() override;
	void testIntervalSearch() override;
	void testFindMinKey() override;
	void testFindMaxKey() override;
	void generateInterval(int& minKey, int& maxKey);
	~MapTester() = default;
};