#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "SpeedTester.h"
#include "FunctionalityTester.h"
#include "BinarySearchTree.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(nullptr));

	{
		//FunctionalityTester ft;
		//ft.runTests();

		SpeedTester st;
		st.testInsertion();
		st.testRemoval();
		st.testPointSearch();
		st.testIntervalSearch();
		st.testFindMinKey();
		st.testFindMaxKey();
	}

	return 0;
}