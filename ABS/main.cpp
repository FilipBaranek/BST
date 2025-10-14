#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "Tester.h"
#include "AVLTree.h"

void testBinarySearchTree()
{
	BinarySearchTree<Number*> bt;
	Tester<BinarySearchTree<Number*>, Number> tester;

	tester.testInsertion(bt);
	tester.testRemoval(bt);
	tester.testPointSearch(bt);
	//tester.testIntervalSearch(bt);
	tester.testFindMinKey(bt);
	tester.testFindMaxKey(bt);
}

void testAVLTree()
{
	AVLTree<Number*> at;
	Tester<AVLTree<Number*>, Number> tester;

	tester.testInsertion(at);
	//tester.testRemoval(at);
	tester.testPointSearch(at);
	//tester.testIntervalSearch(at);
	tester.testFindMinKey(at);
	tester.testFindMaxKey(at);
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