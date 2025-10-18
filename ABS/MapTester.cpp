#include "MapTester.h"

MapTester::MapTester(const char* name)
{
	m_name = name;
	m_randomData.reserve(RANDOM_DATA_COUNT);
	for (int i = 1; i <= RANDOM_DATA_COUNT; ++i)
	{
		m_randomData.push_back(i);
	}
	std::shuffle(m_randomData.begin(), m_randomData.end(), m_g);
	std::cout << "Data generated\n";
}

void MapTester::testInsertion()
{
	std::cout << "INSERTION\n";
	auto start = high_resolution_clock::now();
	for (auto& number : m_randomData)
	{
		m_structure[number] = number;
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(end - start).count();
	std::cout << duration << " seconds\n";
}

void MapTester::testRemoval()
{
	std::shuffle(m_randomData.begin(), m_randomData.begin() + REMOVE_DATA_COUNT, m_g);
	std::cout << "REMOVAL\n";
	auto start = high_resolution_clock::now();
	for (int i{}; i < REMOVE_DATA_COUNT; ++i)
	{
		m_structure.erase(m_randomData[i]);
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(end - start).count();
	std::cout << duration << " seconds\n";
}

void MapTester::testPointSearch()
{
	std::shuffle(m_randomData.begin(), m_randomData.begin() + SEARCH_DATA_COUNT, m_g);
	std::cout << "POINT SEARCH\n";
	auto start = high_resolution_clock::now();
	for (int i{}; i < SEARCH_DATA_COUNT; ++i)
	{
		m_structure.find(m_randomData[i]);
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(end - start).count();
	std::cout << duration << " seconds\n";
}

void MapTester::generateInterval(int& minKey, int& maxKey)
{
	minKey = -1;
	while (minKey <= 0 || minKey >= m_structure.size() - SEARCH_INTERVAL)
	{
		minKey = (rand() % m_structure.size()) + 1;
	}
	maxKey = minKey + SEARCH_INTERVAL;
}

void MapTester::testIntervalSearch()
{
	int minKey, maxKey;
	std::map<int, int> keys;
	for (int i{}; i < SEARCH_INTERVAL_COUNT; ++i)
	{
		generateInterval(minKey, maxKey);
		keys[minKey] = maxKey;
	}

	std::vector<int> interval;
	interval.reserve(m_structure.size());

	std::cout << "INTERVAL SEARCH\n";
	auto start = high_resolution_clock::now();
	for (auto& keyPair : keys)
	{
		auto lowKey = m_structure.lower_bound(keyPair.first);
		auto highKey = m_structure.lower_bound(keyPair.second);
		for (auto it = lowKey; it != highKey; ++it)
		{
			(void)it->second;
		}
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start).count();
	std::cout << duration << " milliseconds\n";
}

void MapTester::testFindMinKey()
{
	std::cout << "SEARCH FOR MIN KEY\n";
	auto start = high_resolution_clock::now();
	for (int i{}; i < KEY_SEARCH_COUNT; ++i)
	{
		m_structure.begin()->second;
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start).count();
	std::cout << duration << " milliseconds\n";
}

void MapTester::testFindMaxKey()
{
	std::cout << "SEARCH FOR MAX KEY\n";
	auto start = high_resolution_clock::now();
	for (int i{}; i < KEY_SEARCH_COUNT; ++i)
	{
		m_structure.rbegin()->second;
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start).count();
	std::cout << duration << " milliseconds\n";
}
