#pragma once
#include <random>
#include <algorithm>
#include <chrono>

using namespace std::chrono;

class Tester
{
protected:
	static constexpr unsigned int RANDOM_DATA_COUNT = 10000000;
	static constexpr unsigned int REMOVE_DATA_COUNT = 2000000;
	static constexpr unsigned int SEARCH_DATA_COUNT = 5000000;
	static constexpr unsigned int SEARCH_INTERVAL_COUNT = 100;
	static constexpr unsigned int SEARCH_INTERVAL = 500;
	static constexpr unsigned int KEY_SEARCH_COUNT = 2000000;
	const char* m_name;
	std::random_device m_rd;
	std::mt19937 m_g{ m_rd() };

public:
	virtual void testInsertion() = 0;
	virtual void testRemoval() = 0;
	virtual void testPointSearch() = 0;
	virtual void testIntervalSearch() = 0;
	virtual void testFindMinKey() = 0;
	virtual void testFindMaxKey() = 0;

	void printName()
	{
		std::cout << m_name << "\n";
	}

	virtual ~Tester() = default;
};