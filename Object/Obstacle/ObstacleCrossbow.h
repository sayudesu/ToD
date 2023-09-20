#pragma once
#include "ObstacleBase.h"
#include <vector>
#include <memory>

class ShotBase;
class ObstacleCrossbow : public ObstacleBase
{
public:
	ObstacleCrossbow(VECTOR pos,int no);
	virtual ~ObstacleCrossbow() {};
	void Init()override;
};

