#include "FunctionalityTester.h"


FunctionalityTester::FunctionalityTester()
{
	m_minimalKey = 999999999;
	m_maximalKey = -1;
}

void FunctionalityTester::insert()
{
	auto number = new Number(rand() % VALUE_UPPER_BOUND);
	bool duplicity = false;
	if (std::find_if(m_data.begin(), m_data.end(), [number](Number* n) { return n->getData() == number->getData(); }) != m_data.end())
	{
		duplicity = true;
	}
	else
	{
		m_data.push_back(number);

		if (number->getData() < m_minimalKey)
		{
			m_minimalKey = number->getData();
		}
		else if (number->getData() > m_maximalKey)
		{
			m_maximalKey = number->getData();
		}
	}
	bool btInserted = m_bst.insert(number);
	bool atInserted = m_at.insert(number);

	auto bstFindNum = m_bst.find(number);
	auto atFindNum = m_at.find(number);

	if ((duplicity && (btInserted || atInserted)) || (!duplicity && (bstFindNum != number || atFindNum != number)))
	{
		throw std::runtime_error("Incorrect inserting");
	}

	if (duplicity)
	{
		delete number;
	}
}

void FunctionalityTester::remove()
{
	int index = rand() % m_data.size();
	int numValue = m_data[index]->getData();
	std::swap(m_data[index], m_data.back());
	m_bst.remove(m_data.back());
	m_at.remove(m_data.back());

	if (m_bst.find(m_data.back()) != nullptr || m_at.find(m_data.back()) != nullptr)
	{
		throw std::runtime_error("Incorrect removal");
	}

	delete m_data.back();
	m_data.pop_back();

	if (numValue == m_minimalKey)
	{
		m_minimalKey = 999999999;
		for (int i{}; i < m_data.size(); ++i)
		{
			if (m_data[i]->getData() < m_minimalKey)
			{
				m_minimalKey = m_data[i]->getData();
			}
		}
	}
	if (numValue == m_maximalKey)
	{
		m_maximalKey = -1;
		for (int i{}; i < m_data.size(); ++i)
		{
			if (m_data[i]->getData() > m_maximalKey)
			{
				m_maximalKey = m_data[i]->getData();
			}
		}
	}
}

void FunctionalityTester::find()
{
	auto number = m_data[rand() % m_data.size()];
	Number* bstKey = m_bst.find(number);
	Number* atKey = m_at.find(number);

	if (bstKey != number || atKey != number)
	{
		throw std::runtime_error("Incorrect point search");
	}
}

void FunctionalityTester::findInterval()
{
	int interval = (rand() % MAX_INTERVAL) + 1;;
	
	if (m_data.size() > 0)
	{
		int min, max;
		min = rand() % VALUE_UPPER_BOUND;
		max = min + interval;

		std::vector<Number*> numbersInInterval;
		for (auto n : m_data)
		{
			if (n->getData() >= min && n->getData() <= max)
			{
				numbersInInterval.push_back(n);
			}
		}
		std::sort(numbersInInterval.begin(), numbersInInterval.end(), [](Number* a, Number* b) {
			return a->getData() < b->getData();
		});

		auto low = new Number(min);
		auto high = new Number(max);
		std::vector<Number*> output;
		m_bst.find(low, high, output);

		if (numbersInInterval.size() != output.size())
		{
			throw std::runtime_error("Interval size doesn't match");
		}

		for (int i{}; i < numbersInInterval.size(); ++i)
		{
			if (numbersInInterval[i]->getData() != output[i]->getData())
			{
				throw std::runtime_error("Incorrect interval search");
			}
		}
		delete low;
		delete high;
	}
}

void FunctionalityTester::findMinKey()
{
	if (m_data.size() > 0)
	{
		Number* bstMinKey = m_bst.findMinKey();
		Number* atMinKey = m_at.findMinKey();

		if (bstMinKey->getData() != m_minimalKey || atMinKey->getData() != m_minimalKey)
		{
			throw std::runtime_error("Incorrect minimal key search");
		}
	}
}

void FunctionalityTester::findMaxKey()
{
	if (m_data.size() > 0)
	{
	 	Number* bstMaxKey = m_bst.findMaxKey();
		Number* atMaxKey = m_at.findMaxKey();

		if (bstMaxKey->getData() != m_maximalKey || atMaxKey->getData() != m_maximalKey)
		{
			throw std::runtime_error("Incorrect maximal key search");
		}
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
		std::cout << "OPERATION N." << i << "\n";
		std::cout << "BINARY TREE SIZE: " << m_bst.size() << "\n";
		std::cout << "AVL SIZE: " << m_at.size() << "\n";
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
