#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "CommonTester.h"
#include "FunctionalityTester.h"
#include "BinarySearchTree.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(nullptr));

	{
		//FunctionalityTester ft;
		//ft.runTests();

		CommonTester ct;
		ct.testInsertion();
		ct.testRemoval();
		ct.testPointSearch();
		//ct.testIntervalSearch();
		ct.testFindMinKey();
		ct.testFindMaxKey();

		//BinarySearchTree<Number*> bt;
		//bt.insert(new Number(10));
		//bt.insert(new Number(20));

		//std::vector<Number*> output;
		//auto low = new Number(10);
		//auto high = new Number(19);

		//bt.find(low, high, output);

		//for (auto& num : output)
		//{
		//	num->print();
		//}

		//delete low;
		//delete high;

		//bt.processPostOrder([](Number* num) {
		//	delete num;
		//	});

		//Speed testy do jedneho loopu
		//Rebalance avl
		//AVL check balance factor
	}

	return 0;
}