#include <iostream>
#include "TestActor.h"

void TestActor::Tick(float deltaTime)
{
	//Actor::Tick(deltaTime);
	super::Tick(deltaTime);

	std::cout << "TestActor::Tick.FPS "
		<< (1.0 / deltaTime)
		<< "\n";

}
