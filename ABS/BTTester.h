#pragma once
#include <vector>
#include <map>
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
	BTTester(Structure& structure, const char* name, bool dataInOrder = false) : m_bts(structure)
	{
		m_name = name;
		m_randomData.reserve(RANDOM_DATA_COUNT);
		for (int i = 1; i <= RANDOM_DATA_COUNT; ++i)
		{
			m_randomData.push_back(new T(i));
		}

		if (!dataInOrder)
		{
			std::shuffle(m_randomData.begin(), m_randomData.end(), m_g);
		}
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
		auto duration = duration_cast<milliseconds>(end - start).count();
		std::cout << duration << " milliseconds\n";
	}

	void testRemoval() override
	{
		std::shuffle(m_randomData.begin(), m_randomData.end(), m_g);

		int startIndex = m_randomData.size() - REMOVE_DATA_COUNT;
		int endIndex = m_randomData.size();

		std::cout << "REMOVAL\n";
		auto start = high_resolution_clock::now();
		for (int i = startIndex; i < endIndex; ++i)
		{
			m_bts.remove(m_randomData[i]);
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start).count();
		std::cout << duration << " milliseconds\n";

		for (int i{}; i < REMOVE_DATA_COUNT; ++i)
		{
			T* data = m_randomData[m_randomData.size() - 1];
			m_randomData.pop_back();
			delete data;
		}
	}

	void testPointSearch() override
	{
		std::shuffle(m_randomData.begin(), m_randomData.end(), m_g);

		std::cout << "POINT SEARCH\n";
		auto start = high_resolution_clock::now();
		for (int i{}; i < SEARCH_DATA_COUNT; ++i)
		{
			m_bts.find(m_randomData[i]);
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start).count();
		std::cout << duration << " milliseconds\n";
	}

	void generateInterval(int& minKey, int& maxKey)
	{
		minKey = -1;
		while (minKey <= 0 || minKey >= m_randomData.size() - SEARCH_INTERVAL)
		{
			minKey = (rand() % m_randomData.size()) + 1;
		}
		maxKey = minKey + SEARCH_INTERVAL + (rand() % SEARCH_INTERVAL_MAX_EXTENSION);
	}

	void testIntervalSearch() override
	{
		std::map<Number*, Number*> keys;
		int min, max;
		for (int i{}; i < SEARCH_INTERVAL_COUNT; ++i)
		{
			generateInterval(min, max);
			keys[new Number(min)] = new Number(max);
		}

		std::vector<T*> interval;
		interval.reserve(m_randomData.size());

		std::cout << "INTERVAL SEARCH\n";
		auto start = high_resolution_clock::now();
		for (const auto& keyPair : keys)
		{
			m_bts.find(keyPair.first, keyPair.second, interval);
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start).count();
		std::cout << duration << " milliseconds\n";

		for (const auto& keyPair : keys)
		{
			delete keyPair.first;
			delete keyPair.second;
		}
	}

	void testFindMinKey() override
	{
		std::cout << "SEARCH FOR MIN KEY\n";
		auto start = high_resolution_clock::now();
		for (int i{}; i < KEY_SEARCH_COUNT; ++i)
		{
			m_bts.findMinKey(m_randomData[rand() % m_randomData.size()]);
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start).count();
		std::cout << duration << " milliseconds\n";
	}

	void testFindMaxKey() override
	{
		std::cout << "SEARCH FOR MAX KEY\n";
		auto start = high_resolution_clock::now();
		for (int i{}; i < KEY_SEARCH_COUNT; ++i)
		{
			m_bts.findMaxKey(m_randomData[rand() % m_randomData.size()]);
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start).count();
		std::cout << duration << " milliseconds\n";
	}

	~BTTester() override
	{
		for (auto& num : m_randomData)
		{
			delete num;
		}
	}
};

