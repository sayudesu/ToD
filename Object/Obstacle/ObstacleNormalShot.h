#pragma once
#include "ObstacleBase.h"
#include <vector>
#include <memory>


class ObstacleNormalShot : public ObstacleBase
{
public:
	ObstacleNormalShot(VECTOR pos,int no);
	virtual ~ObstacleNormalShot() {};
	void Init();
};

