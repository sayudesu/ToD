#pragma once
#include "ObstacleBase.h"
#include <vector>


class ObstacleHomingMissile : public ObstacleBase
{
public:
	ObstacleHomingMissile(VECTOR pos,int no);
	virtual ~ObstacleHomingMissile() {};
	void Init()override;
};

