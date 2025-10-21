#include "FunctionalityTester.h"


void FunctionalityTester::insert()
{
	auto number = new Number(rand() % VALUE_UPPER_BOUND);
	m_data.push_back(number);
	m_bst.insert(number);
	m_at.insert(number);
}

void FunctionalityTester::remove()
{
	int index = rand() % m_data.size();
	std::swap(m_data[index], m_data.back());
	m_bst.remove(m_data.back());
	m_at.remove(m_data.back());
	delete m_data.back();
	m_data.pop_back();
}

void FunctionalityTester::find()
{
	auto number = m_data[rand() % m_data.size()];
	m_bst.find(number);
	m_at.find(number);
}

void FunctionalityTester::findInterval()
{
	//TODO
}

void FunctionalityTester::findMinKey()
{
	if (m_data.size() > 0)
	{
		auto number = m_data[rand() % m_data.size()];
		m_bst.findMinKey(number);
		m_at.findMinKey(number);
	}
	else
	{
		m_bst.findMinKey();
		m_at.findMinKey();
	}
}

void FunctionalityTester::findMaxKey()
{
	if (m_data.size() > 0)
	{
		auto number = m_data[rand() % m_data.size()];
		m_bst.findMaxKey(number);
		m_at.findMaxKey(number);
	}
	else
	{
		m_bst.findMaxKey();
		m_at.findMaxKey();
	}
}

int FunctionalityTester::generateOperation()
{
	return rand() % 4;
}

void FunctionalityTester::runTests()
{
	int operation = INSERT;

	for (int i{}; i < REPLICATIONS; ++i)
	{
		if (i % CHECKPOINT_INDEX == 0)
		{
			std::cout << "OPERATION N." << i << "\n";
			std::cout << "BINARY TREE SIZE: " << m_bst.size() << "\n";
			std::cout << "AVL SIZE: " << m_at.size() << "\n";
			findMinKey();
			findMaxKey();
		}
		else
		{
			switch (operation)
			{
				case INSERT:
					insert();
					break;
				case REMOVE:
					if (m_data.size() > 0)
					{
						remove();
					}
					break;
				case FIND_POINT:
					if (m_data.size() > 0)
					{
						find();
					}
					break;
				case FIND_INTERVAL:
				default:
					if (m_data.size() > 0)
					{
						findInterval();
					}
					break;
			}
		}

		operation = generateOperation();
	}
}

FunctionalityTester::~FunctionalityTester()
{
	if (m_data.size() > 0)
	{
		for (auto& number : m_data)
		{
			delete number;
		}
	}
}
