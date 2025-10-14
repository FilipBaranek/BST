#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include "Number.h"
#include "BinarySearchTree.h"

template<typename Structure, typename T>
class Tester
{
	static_assert(std::is_base_of<BinarySearchTree<T*>, Structure>::value, "Structure must be some form of Binary search tree");

private:
	static constexpr unsigned int RANDOM_DATA_COUNT = 10000000;
	static constexpr unsigned int REMOVE_DATA_COUNT = 2000000;
	static constexpr unsigned int SEARCH_DATA_COUNT = 5000000;
	static constexpr unsigned int SEARCH_INTERVAL_COUNT = 1000000;
	static constexpr unsigned int SEARCH_INTERVAL = 500;
	std::vector<T*> m_randomData;
	std::random_device m_rd;
	std::mt19937 m_g{ m_rd() };

public:
	Tester()
	{
		for (int i = 1; i <= RANDOM_DATA_COUNT; ++i)
		{
			m_randomData.push_back(new T(i));
		}

		std::shuffle(m_randomData.begin(), m_randomData.end(), m_g);
		std::cout << "Data generated\n";
	}

	void testInsertion(Structure& bts)
	{
		std::cout << "INSERT START\n";
		for (auto& num : m_randomData)
		{
			bts.insert(num);
		}
		std::cout << "INSERT END\n";
	}

	void testRemoval(Structure& bts)
	{
		std::shuffle(m_randomData.begin(), m_randomData.begin() + REMOVE_DATA_COUNT, m_g);

		std::cout << "REMOVE START\n";
		for (int i = 0; i < REMOVE_DATA_COUNT; ++i)
		{
			bts.remove(m_randomData[i]);
		}
		std::cout << "REMOVE END\n";
	}

	void testPointSearch(Structure& bts)
	{
		std::shuffle(m_randomData.begin() + REMOVE_DATA_COUNT, m_randomData.begin() + REMOVE_DATA_COUNT + SEARCH_DATA_COUNT, m_g);

		std::cout << "POINT SEARCH START\n";
		for (int i = REMOVE_DATA_COUNT; i < REMOVE_DATA_COUNT + SEARCH_DATA_COUNT; ++i)
		{
			bts.find(m_randomData[i]);
		}
		std::cout << "POINT SEARCH END\n";
	}

	void testIntervalSearch(Structure& bts)
	{
		std::shuffle(m_randomData.begin(), m_randomData.begin() + SEARCH_INTERVAL_COUNT, m_g);
		std::vector<T*> interval;
		int currentReplication = 0;

		std::cout << "INTERVAL SEARCH START\n";
		for (int i = 0; i < SEARCH_INTERVAL_COUNT; ++i)
		{
			bts.find(m_randomData[currentReplication], m_randomData[currentReplication + SEARCH_INTERVAL - 1], interval);
			currentReplication += SEARCH_INTERVAL;
		}

		std::cout << "INTERVAL SEARCH END\n";
	}

	void testFindMinKey(Structure& bts)
	{
		std::cout << "SEARCH FOR MIN KEY START\n";
		bts.findMinKey();
		std::cout << "SEARCH FOR MIN KEY END\n";
	}

	void testFindMaxKey(Structure& bts)
	{
		std::cout << "SEARCH FOR MAX KEY START\n";
		bts.findMaxKey();
		std::cout << "SEARCH FOR MAX KEY END\n";
	}
	
	~Tester()
	{
		for (auto& num : m_randomData)
		{
			delete num;
		}
	}
};

