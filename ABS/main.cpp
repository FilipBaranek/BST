#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "Wrapper.h"
#include "BinaryTree.h"
#include "IComparable.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	{
		BinaryTree<IComparable*> bt;
		IComparable* wrapp = new Wrapper(5);
		bt.insert(wrapp);
		bt.insert(new Wrapper(4));
		bt.insert(new Wrapper(6));
		bt.insert(new Wrapper(7));

		((Wrapper*)bt.find(wrapp))->print();
		
		bt.processInOrder([](IComparable* item) {
			((Wrapper*)item)->print();
		});
		
		bt.processPostOrder([](IComparable* item) {
			delete item;
		});

		bt.clear();
	}

	return 0;
}