#pragma once
#include "IComparable.h"

class Wrapper : public IComparable
{
private:
	int m_data;

public:
	Wrapper(int data);
	int getData();
	void print();
	int compare(IComparable* other) const override;
	~Wrapper() = default;
};

