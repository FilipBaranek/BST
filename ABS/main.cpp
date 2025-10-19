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
	bstTesters.shrink_to_fit();

	for (auto& tester : bstTesters)
	{
		tester->printName();
		tester->testInsertion();
		//tester->testRemoval();
		tester->testPointSearch();
		//tester->testIntervalSearch();
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

void testMap()
{
	Tester* mt = new MapTester("Map tester");
	mt->testInsertion();
	mt->testRemoval();
	mt->testPointSearch();
	mt->testIntervalSearch();
	mt->testFindMaxKey();
	mt->testFindMinKey();
	delete mt;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(nullptr));
	{
		std::cout << "TESTING RANDOM DATA\n";
		testRandomData();
		//std::cout << "\nTESTING IN ORDER DATA\n";
		////testOrderedData();
		//std::cout << "\nTESTING STD::MAP\n";
		//testMap();


		//AVLTree<Number*> at;
		//for (int i = 1; i <= 1000; ++i)
		//{
		//	at.insert(new Number(i));
		//}

		

		////////
		////////
		//////// FIXNUT REMOVE :DDDDDDDDDDD
		///////
		////////
	}

	return 0;
}