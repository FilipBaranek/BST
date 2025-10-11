#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Number.h"
#include "BinaryTree.h"
#include "IComparable.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(nullptr));
	{
		std::vector<int> numbers;
		for (int i = 1; i <= 10; ++i)
		{
			numbers.push_back(i);
		}
		std::random_shuffle(numbers.begin(), numbers.end());

		std::cout << "Numbers order:\n";
		for (int i : numbers)
		{
			std::cout << i << "\n";
		}

		BinaryTree<Number*> bt;
		Number* number = new Number(1651651351);
		bt.insert(number);
		for (int i : numbers)
		{
			bt.insert(new Number(i));
		}
		std::cout << "Numbers were inserted, tree depth is " << bt.depth() << "\n";

		std::cout << "\nIn order traversal:\n";
		bt.processInOrder([](Number* item) {
			item->print();
		});

		std::cout << "Found item: ";
		bt.find(number)->print();
		bt.remove(number);
		delete number;

		std::cout << "Pre order traversal:\n";
		bt.processPreOrder([](Number* item) {
			item->print();
		});

		std::cout << "Level order traversal:\n";
		bt.processLevelOrder([](Number* item) {
			item->print();
		});

		bt.processPostOrder([](Number* item) {
			delete item;
		});
	}

	return 0;
}