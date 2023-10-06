#pragma once
#include "ObstacleBase.h"
#include <vector>


class ObstacleCannon : public ObstacleBase
{
public:
	ObstacleCannon(VECTOR pos,int no, int mapCihpX, int mapCihpY);
	virtual ~ObstacleCannon() {};
	void Init()override;
};

