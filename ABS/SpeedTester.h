#pragma once
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>

using namespace std::chrono;

class SpeedTester
{
protected:
	static constexpr const unsigned int RANDOM_DATA_COUNT = 10000000;
	static constexpr const unsigned int REMOVE_DATA_COUNT = 2000000;
	static constexpr const unsigned int SEARCH_DATA_COUNT = 5000000;
	static constexpr const unsigned int SEARCH_INTERVAL_COUNT = 1000000;
	static constexpr const unsigned int SEARCH_INTERVAL = 500;
	static constexpr const unsigned int SEARCH_INTERVAL_MAX_EXTENSION = 200;
	static constexpr const unsigned int KEY_SEARCH_COUNT = 2000000;
	std::random_device m_rd;
	std::mt19937 m_g{ m_rd() };

public:
	virtual void testInsertion() = 0;
	virtual void testRemoval() = 0;
	virtual void testPointSearch() = 0;
	virtual void testIntervalSearch() = 0;
	virtual void testFindMinKey() = 0;
	virtual void testFindMaxKey() = 0;
	virtual ~SpeedTester() = default;
};