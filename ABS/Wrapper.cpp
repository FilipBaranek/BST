#include "Wrapper.h"
#include <iostream>

Wrapper::Wrapper(int data)
{
	m_data = data;
}

int Wrapper::getData()
{
	return m_data;
}

void Wrapper::print()
{
	std::cout << m_data << "\n";
}

int Wrapper::compare(IComparable* other) const
{
	int otherData = ((Wrapper*)other)->getData();

	if (m_data == otherData)
	{
		return 0;
	}
	else if (m_data > otherData)
	{
		return -1;
	}
	else if (m_data < otherData)
	{
		return 1;
	}
}
