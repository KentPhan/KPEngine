
#include <iostream>
#include "../KPEngine/include/KPEngine-init.h"

extern bool DynamicHeapManager_UnitTest();
extern bool KPVector2_UnitTest();
extern bool FixedHeapManager_UnitTest();

int main()
{

	/*KPEngine::Initialize();*/
	/*KPVector2_UnitTest();*/
	/*DynamicHeapManager_UnitTest();*/
	FixedHeapManager_UnitTest();
	

	std::getchar();

}