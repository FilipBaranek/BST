#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <unordered_set>
#include "Number.h"
#include "BinaryTree.h"
#include "IComparable.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(nullptr));
	{
		std::unordered_set<int> usedNumbers;
		BinaryTree<IComparable*> bt;
		
		while (usedNumbers.size() <= 10000)
		{
			usedNumbers.insert(rand());
		}
		std::cout << "Numbers were inserted\n";

		IComparable* number = new Number(500);
		bt.insert(number);
		for (int i : usedNumbers)
		{
			bt.insert(new Number(i));
		}

		std::cout << "Found item:";
		((Number*)bt.find(number))->print();			//TOTO ISTO BUDE TREBA PREROBIT LEBO HLADAM KLUC PODLA KLUCA - NEZMYSEL
		
		std::cout << "\nItems printed in order:\n";
		bt.processInOrder([](IComparable* item) {
			((Number*)item)->print();
		});
		
		bt.processPostOrder([](IComparable* item) {
			delete item;
		});
	}

	return 0;
}