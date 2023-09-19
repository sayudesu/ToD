#pragma once
#include "ObstacleBase.h"
#include <vector>


class ObstacleNormalShot : public ObstacleBase
{
public:
	ObstacleNormalShot(VECTOR pos,int no);
	virtual ~ObstacleNormalShot() {};
	void Init();
};

