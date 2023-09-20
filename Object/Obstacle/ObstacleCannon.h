#pragma once
#include "ObstacleBase.h"
#include <vector>


class ObstacleCannon : public ObstacleBase
{
public:
	ObstacleCannon(VECTOR pos,int no);
	virtual ~ObstacleCannon() {};
	void Init()override;
};

