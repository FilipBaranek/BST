#include <random>
#include <algorithm>
#include <iostream>
#include "Tester.h"


Tester::Tester()
{
	std::random_device rd;
	std::mt19937 g(rd());

	for (int i = 1; i <= RANDOM_DATA_COUNT; ++i)
	{
		m_randomData.push_back(new Number(i));
	}

	std::shuffle(m_randomData.begin(), m_randomData.end(), g);
}

void Tester::testBST()
{
}
