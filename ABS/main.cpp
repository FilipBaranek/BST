#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "Tester.h"
#include "AVLTree.h"

void testBinarySearchTree()
{
	BinarySearchTree<Number*> bt;
	Tester<BinarySearchTree<Number*>, Number> tester(bt);

	tester.testInsertion();
	tester.testIntervalSearch();
	tester.testRemoval();
	tester.testPointSearch();
	tester.testFindMinKey();
	tester.testFindMaxKey();
}

void testAVLTree()
{
	AVLTree<Number*> at;
	Tester<AVLTree<Number*>, Number> tester(at);

	tester.testInsertion();
	tester.testIntervalSearch();
	tester.testRemoval();
	tester.testPointSearch();
	tester.testFindMinKey();
	tester.testFindMaxKey();
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(nullptr));
	{
		std::cout << "Binary search tree:\n";
		testBinarySearchTree();
		std::cout << "AVL tree\n";
		testAVLTree();
	}

	return 0;
}