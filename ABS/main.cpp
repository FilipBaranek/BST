#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "Tester.h"
#include "BTTester.h"
#include "AVLTree.h"
#include "Number.h"
#include "MapTester.h"



void runBTTester(bool dataInOrder = false)
{
	BinarySearchTree<Number*> bt;
	AVLTree<Number*> at;

	std::vector<Tester*> bstTesters;
	bstTesters.push_back(new BTTester<BinarySearchTree<Number*>, Number>(bt, "Binary search tree", dataInOrder));
	bstTesters.push_back(new BTTester<AVLTree<Number*>, Number>(at, "AVL tree", dataInOrder));
	bstTesters.push_back(new MapTester("Map tester"));
	bstTesters.shrink_to_fit();

	for (auto& tester : bstTesters)
	{
		tester->printName();
		tester->testInsertion();
		tester->testRemoval();
		tester->testPointSearch();
		tester->testIntervalSearch();
		tester->testFindMaxKey();
		tester->testFindMinKey();
		std::cout << "\n";

		delete tester;
	}
}

void testOrderedData()
{
	runBTTester(true);
}

void testRandomData()
{
	runBTTester();
}

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(nullptr));

	std::cout << "TESTING RANDOM DATA\n";
	testRandomData();

	//{
	//	std::cout << "TESTING RANDOM DATA\n";
	//	testRandomData();
	//}

	return 0;
}