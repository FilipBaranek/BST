#pragma once
#include <vector>
#include "Tester.h"
#include "Number.h"
#include "BinarySearchTree.h"

template<typename Structure, typename T>
class BTTester : public Tester
{
	static_assert(std::is_base_of<BinarySearchTree<T*>, Structure>::value, "Structure must be some form of Binary search tree");

private:
	Structure& m_bts;
	std::vector<T*> m_randomData;

public:
	BTTester(Structure& structure, const char* name) : m_bts(structure)
	{
		m_name = name;
		m_randomData.reserve(RANDOM_DATA_COUNT);
		for (int i = 1; i <= RANDOM_DATA_COUNT; ++i)
		{
			m_randomData.push_back(new T(i));
		}

		std::shuffle(m_randomData.begin(), m_randomData.end(), m_g);
		std::cout << "Data generated\n";
	}

	void testInsertion() override
	{
		std::cout << "INSERTION\n";
		auto start = high_resolution_clock::now();
		for (auto& num : m_randomData)
		{
			m_bts.insert(num);
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(end - start).count();
		std::cout << duration << " seconds\n";
	}

	void testRemoval() override
	{
		std::shuffle(m_randomData.begin(), m_randomData.begin() + REMOVE_DATA_COUNT, m_g);

		std::cout << "REMOVAL\n";
		auto start = high_resolution_clock::now();
		for (int i = 0; i < REMOVE_DATA_COUNT; ++i)
		{
			m_bts.remove(m_randomData[i]);
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(end - start).count();
		std::cout << duration << " seconds\n";
	}

	void testPointSearch() override
	{
		std::shuffle(m_randomData.begin() + REMOVE_DATA_COUNT, m_randomData.begin() + REMOVE_DATA_COUNT + SEARCH_DATA_COUNT, m_g);

		std::cout << "POINT SEARCH\n";
		auto start = high_resolution_clock::now();
		for (int i = REMOVE_DATA_COUNT; i < REMOVE_DATA_COUNT + SEARCH_DATA_COUNT; ++i)
		{
			m_bts.find(m_randomData[i]);
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(end - start).count();
		std::cout << duration << " seconds\n";
	}

	void testIntervalSearch() override
	{
		m_randomData.clear();
		for (int i = 1; i <= SEARCH_INTERVAL_COUNT + SEARCH_INTERVAL; ++i)
		{
			m_randomData.push_back(new Number(i));
		}

		std::vector<T*> interval;
		interval.reserve(SEARCH_INTERVAL_COUNT + SEARCH_INTERVAL);
		int currentReplication = 0;

		std::cout << "INTERVAL SEARCH\n";
		auto start = high_resolution_clock::now();
		for (int i = 0; i < SEARCH_INTERVAL_COUNT; ++i)
		{
			m_bts.find(m_randomData[currentReplication], m_randomData[currentReplication + SEARCH_INTERVAL - 1], interval);
			++currentReplication;
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(end - start).count();
		std::cout << duration << " seconds\n";
	}

	void testFindMinKey() override
	{
		std::cout << "SEARCH FOR MIN KEY\n";
		auto start = high_resolution_clock::now();
		for (int i{}; i < KEY_SEARCH_COUNT; ++i)
		{
			m_bts.findMinKey();
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(end - start).count();
		std::cout << duration << " seconds\n";
	}

	void testFindMaxKey() override
	{
		std::cout << "SEARCH FOR MAX KEY\n";
		auto start = high_resolution_clock::now();
		for (int i{}; i < KEY_SEARCH_COUNT; ++i)
		{
			m_bts.findMaxKey();
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(end - start).count();
		std::cout << duration << " seconds\n";
	}

	~BTTester() override
	{
		for (auto& num : m_randomData)
		{
			delete num;
		}

		//m_bts.processPostOrder([](T* item) {
		//	delete item;
		//});
	}
};

