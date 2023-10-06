#pragma once
#include "ObstacleBase.h"
#include <vector>


class ObstacleHomingMissile : public ObstacleBase
{
public:
	ObstacleHomingMissile(VECTOR pos,int no, int mapCihpX, int mapCihpY);
	virtual ~ObstacleHomingMissile() {};
	void Init()override;
};

