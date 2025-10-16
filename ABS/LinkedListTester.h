#pragma once
#include <list>
#include <vector>
#include <iostream>
#include "Tester.h"
#include "Number.h"

class LinkedListTester : public Tester
{
private:
	std::vector<Number*> m_randomData;
	std::list<Number*> m_linkedList;

public:
	LinkedListTester(const char* name)
	{
		m_name = name;
		m_randomData.reserve(RANDOM_DATA_COUNT);
		for (int i = 1; i <= RANDOM_DATA_COUNT; ++i)
		{
			m_randomData.push_back(new Number(i));
		}
		std::shuffle(m_randomData.begin(), m_randomData.end(), m_g);
		std::cout << "Data generated\n";
	}

	void testInsertion() override
	{
		std::cout << "INSERTION\n";
		auto start = high_resolution_clock::now();
		for (auto& number : m_randomData)
		{
			m_linkedList.push_back(number);
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
			m_linkedList.remove(m_randomData[i]);
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
			auto iterator = std::find(m_linkedList.begin(), m_linkedList.end(), m_randomData[i]);
		}
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(end - start).count();
		std::cout << duration << " seconds\n";

	}

	void testIntervalSearch() override
	{
		std::cout << "INTERVAL SEARCH\n";
		auto start = high_resolution_clock::now();

		//TODO

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(end - start).count();
		std::cout << duration << " seconds\n";

	}

	void testFindMinKey() override
	{
		std::cout << "MIN KEY SEARCH\n";
		auto start = high_resolution_clock::now();
		auto iterator = std::min_element(m_linkedList.begin(), m_linkedList.end(), [](Number* a, Number* b) {
			return a->getData() < b->getData();
		});
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(end - start).count();
		std::cout << duration << " seconds\n";

	}

	void testFindMaxKey() override
	{
		std::cout << "MAX KEY SEARCH\n";
		auto start = high_resolution_clock::now();
		auto iterator = std::min_element(m_linkedList.begin(), m_linkedList.end(), [](Number* a, Number* b) {
			return a->getData() > b->getData();
		});
		auto end = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(end - start).count();
		std::cout << duration << " seconds\n";

	}

	~LinkedListTester() override
	{
		for (auto& number : m_randomData)
		{
			delete number;
		}
	}
};

