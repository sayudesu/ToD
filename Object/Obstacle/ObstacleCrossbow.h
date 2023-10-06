#pragma once
#include "ObstacleBase.h"
#include <vector>
#include <memory>

class ShotBase;
class ObstacleCrossbow : public ObstacleBase
{
public:
	ObstacleCrossbow(VECTOR pos,int no, int mapCihpX, int mapCihpY);
	virtual ~ObstacleCrossbow() {};
	void Init()override;
};

