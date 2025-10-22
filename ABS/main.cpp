#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "CommonTester.h"
#include "FunctionalityTester.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(nullptr));

	{
		FunctionalityTester ft;
		ft.runTests();

		//CommonTester ct;
		//ct.testInsertion();
		//ct.testRemoval();
		//ct.testPointSearch();
		////ct.testIntervalSearch();
		//ct.testFindMinKey();
		//ct.testFindMaxKey();
	}

	return 0;
}