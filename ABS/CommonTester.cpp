#include "CommonTester.h"

CommonTester::CommonTester()
{
	for (int i = 1; i <= RANDOM_DATA_COUNT; ++i)
	{
		m_randomData.push_back(new Number(i));
	}
	std::shuffle(m_randomData.begin(), m_randomData.end(), m_g);
	std::cout << "Data generated\n";
}

void CommonTester::testInsertion()
{
	std::cout << "INSERTION\n";
	std::cout << "Binary search tree\n";
	auto start = high_resolution_clock::now();
	for (auto& num : m_randomData)
	{
		m_bst.insert(num);
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start).count();
	std::cout << duration << " milliseconds\n";

	std::cout << "AVL tree\n";
	auto startAT = high_resolution_clock::now();
	for (auto& num : m_randomData)
	{
		m_at.insert(num);
	}
	auto endAT = high_resolution_clock::now();
	auto durationAT = duration_cast<milliseconds>(endAT - startAT).count();
	std::cout << durationAT << " milliseconds\n";

	std::cout << "RB tree\n";
	auto startRB = high_resolution_clock::now();
	for (auto& num : m_randomData)
	{
		m_rb[num] = num->getData();
	}
	auto endRB = high_resolution_clock::now();
	auto durationRB = duration_cast<milliseconds>(endRB - startRB).count();
	std::cout << durationRB << " milliseconds\n";
}

void CommonTester::testRemoval()
{
	std::shuffle(m_randomData.begin(), m_randomData.end(), m_g);

	int startIndex = m_randomData.size() - REMOVE_DATA_COUNT;
	int endIndex = m_randomData.size();

	std::cout << "REMOVAL\n";
	std::cout << "Binary search tree\n";
	auto start = high_resolution_clock::now();
	for (int i = startIndex; i < endIndex; ++i)
	{
		m_bst.remove(m_randomData[i]);
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start).count();
	std::cout << duration << " milliseconds\n";

	std::cout << "AVL tree\n";
	auto startAT = high_resolution_clock::now();
	for (int i = startIndex; i < endIndex; ++i)
	{
		m_at.remove(m_randomData[i]);
	}
	auto endAT = high_resolution_clock::now();
	auto durationAT = duration_cast<milliseconds>(endAT - startAT).count();
	std::cout << durationAT << " milliseconds\n";

	std::cout << "RB tree\n";
	auto startRB = high_resolution_clock::now();
	for (int i = startIndex; i < endIndex; ++i)
	{
		m_at.remove(m_randomData[i]);
	}
	auto endRB = high_resolution_clock::now();
	auto durationRB = duration_cast<milliseconds>(endRB - startRB).count();
	std::cout << durationRB << " milliseconds\n";

	for (int i{}; i < REMOVE_DATA_COUNT; ++i)
	{
		Number* data = m_randomData[m_randomData.size() - 1];
		m_randomData.pop_back();
		delete data;
	}
}

void CommonTester::testPointSearch()
{
	std::shuffle(m_randomData.begin(), m_randomData.end(), m_g);

	std::cout << "POINT SEARCH\n";
	std::cout << "Binary search tree\n";
	auto start = high_resolution_clock::now();
	for (int i{}; i < SEARCH_DATA_COUNT; ++i)
	{
		m_bst.find(m_randomData[i]);
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start).count();
	std::cout << duration << " milliseconds\n";

	std::cout << "AVL tree\n";
	auto startAT = high_resolution_clock::now();
	for (int i{}; i < SEARCH_DATA_COUNT; ++i)
	{
		m_at.find(m_randomData[i]);
	}
	auto endAT = high_resolution_clock::now();
	auto durationAT = duration_cast<milliseconds>(endAT - startAT).count();
	std::cout << durationAT << " milliseconds\n";

	std::cout << "RB tree\n";
	auto startRB = high_resolution_clock::now();
	for (int i{}; i < SEARCH_DATA_COUNT; ++i)
	{
		m_rb[m_randomData[i]];
	}
	auto endRB = high_resolution_clock::now();
	auto durationRB = duration_cast<milliseconds>(endRB - startRB).count();
	std::cout << durationRB << " milliseconds\n";
}

void CommonTester::generateInterval(int& minKey, int& maxKey)
{
	minKey = -1;
	while (minKey <= 0 || minKey >= m_randomData.size() - SEARCH_INTERVAL)
	{
		minKey = (rand() % m_randomData.size()) + 1;
	}
	maxKey = minKey + SEARCH_INTERVAL + (rand() % SEARCH_INTERVAL_MAX_EXTENSION);
}

void CommonTester::testIntervalSearch()
{
	std::map<Number*, Number*> keys;
	int min, max;
	for (int i{}; i < SEARCH_INTERVAL_COUNT; ++i)
	{
		generateInterval(min, max);
		keys[new Number(min)] = new Number(max);
	}

	std::vector<Number*> interval;
	interval.reserve(m_randomData.size());

	std::cout << "INTERVAL SEARCH\n";
	std::cout << "Binary search tree\n";
	auto start = high_resolution_clock::now();
	for (const auto& keyPair : keys)
	{
		m_bst.find(keyPair.first, keyPair.second, interval);
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start).count();
	std::cout << duration << " milliseconds\n";

	std::cout << "AVL tree\n";
	auto startAT = high_resolution_clock::now();
	for (const auto& keyPair : keys)
	{
		m_at.find(keyPair.first, keyPair.second, interval);
	}
	auto endAT = high_resolution_clock::now();
	auto durationAT = duration_cast<milliseconds>(endAT - startAT).count();
	std::cout << durationAT << " milliseconds\n";

	std::cout << "RB tree\n";
	auto startRB = high_resolution_clock::now();
	for (const auto& keyPair : keys)
	{
		auto itLow = m_rb.lower_bound(keyPair.first);
		auto itHigh = m_rb.lower_bound(keyPair.second);

		for (auto it = itLow; it != itHigh; ++it)
		{
			it->first;
		}
	}
	auto endRB = high_resolution_clock::now();
	auto durationRB = duration_cast<milliseconds>(endRB - startRB).count();
	std::cout << durationRB << " milliseconds\n";

	//RB TEST TODO

	for (const auto& keyPair : keys)
	{
		delete keyPair.first;
		delete keyPair.second;
	}
}

void CommonTester::testFindMinKey()
{
	std::cout << "SEARCH FOR MIN KEY\n";
	std::cout << "Binary search tree\n";
	auto start = high_resolution_clock::now();
	for (int i{}; i < KEY_SEARCH_COUNT; ++i)
	{
		m_bst.findMinKey(m_randomData[rand() % m_randomData.size()]);
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start).count();
	std::cout << duration << " milliseconds\n";

	std::cout << "AVL tree\n";
	auto startAT = high_resolution_clock::now();
	for (int i{}; i < KEY_SEARCH_COUNT; ++i)
	{
		m_at.findMinKey(m_randomData[rand() % m_randomData.size()]);
	}
	auto endAT = high_resolution_clock::now();
	auto durationAT = duration_cast<milliseconds>(endAT - startAT).count();
	std::cout << durationAT << " milliseconds\n";

	std::cout << "RB tree\n";
	auto startRB = high_resolution_clock::now();
	for (int i{}; i < KEY_SEARCH_COUNT; ++i)
	{
		m_rb.begin()->first;
	}
	auto endRB = high_resolution_clock::now();
	auto durationRB = duration_cast<milliseconds>(endRB - startRB).count();
	std::cout << durationRB << " milliseconds\n";
}

void CommonTester::testFindMaxKey()
{
	std::cout << "SEARCH FOR MAX KEY\n";
	std::cout << "Binary search tree\n";
	auto start = high_resolution_clock::now();
	for (int i{}; i < KEY_SEARCH_COUNT; ++i)
	{
		m_bst.findMaxKey(m_randomData[rand() % m_randomData.size()]);
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start).count();
	std::cout << duration << " milliseconds\n";

	std::cout << "AVL tree\n";
	auto startAT = high_resolution_clock::now();
	for (int i{}; i < KEY_SEARCH_COUNT; ++i)
	{
		m_at.findMaxKey(m_randomData[rand() % m_randomData.size()]);
	}
	auto endAT = high_resolution_clock::now();
	auto durationAT = duration_cast<milliseconds>(endAT - startAT).count();
	std::cout << durationAT << " milliseconds\n";

	std::cout << "RB tree\n";
	auto startRB = high_resolution_clock::now();
	for (int i{}; i < KEY_SEARCH_COUNT; ++i)
	{
		m_rb.rbegin();
	}
	auto endRB = high_resolution_clock::now();
	auto durationRB = duration_cast<milliseconds>(endRB - startRB).count();
	std::cout << durationRB << " milliseconds\n";
}

CommonTester::~CommonTester()
{
	for (auto& num : m_randomData)
	{
		delete num;
	}
}
