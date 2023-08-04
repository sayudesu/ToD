#include "ObstacleBase.h"

bool ObstacleBase::GetErase()
{
	if (test)
	{
		printfDx("t");
	}
	else
	{
		printfDx("f");
	}

	return test;
}
