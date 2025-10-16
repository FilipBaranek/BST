#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "Tester.h"
#include "BTTester.h"
#include "LinkedListTester.h"
#include "AVLTree.h"
#include "Number.h"

//void testBinarySearchTree()
//{
//	BinarySearchTree<Number*> bt;
//	Tester<BinarySearchTree<Number*>, Number> tester(bt);
//
//	tester.testInsertion();
//	tester.testPointSearch();
//	tester.testFindMinKey();
//	tester.testFindMaxKey();
//	tester.testIntervalSearch();
//	tester.testRemoval();
//}
//
//void testAVLTree()
//{
//	AVLTree<Number*> at;
//	Tester<AVLTree<Number*>, Number> tester(at);
//
//	tester.testInsertion();
//	tester.testPointSearch();
//	tester.testFindMinKey();
//	tester.testFindMaxKey();
//	tester.testIntervalSearch();
//	tester.testRemoval();
//}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(nullptr));
	{
		//std::cout << "Binary search tree:\n";
		//testBinarySearchTree();
		//std::cout << "AVL tree\n";
		//testAVLTree();

		BinarySearchTree<Number*> bt;
		AVLTree<Number*> at;

		std::vector<Tester*> testers;
		testers.push_back(new BTTester<BinarySearchTree<Number*>, Number>(bt, "Binary search tree"));
		testers.push_back(new BTTester<AVLTree<Number*>, Number>(at, "AVL tree"));
		testers.push_back(new LinkedListTester("Linked list"));

		for (auto& tester : testers)
		{
			tester->printName();
			tester->testInsertion();
			tester->testRemoval();
			tester->testPointSearch();
			tester->testFindMinKey();
			tester->testFindMaxKey();
			//tester->testIntervalSearch();

			delete tester;
		}
	}

	return 0;
}