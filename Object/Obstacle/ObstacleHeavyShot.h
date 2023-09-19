#pragma once
#include "ObstacleBase.h"
#include <vector>
#include <memory>

class ShotBase;
class EffekseerDrawer;

class ObstacleHeavyShot : public ObstacleBase
{
public:
	ObstacleHeavyShot(VECTOR pos,int no);
	virtual ~ObstacleHeavyShot() {};
	void Init();
};

