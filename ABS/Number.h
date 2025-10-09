#pragma once
#include "IComparable.h"

class Number : public IComparable
{
private:
	int m_data;

public:
	Number(int data);
	int getData();
	void print();
	int compare(IComparable* other) const override;
	~Number() = default;
};

