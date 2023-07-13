#pragma once
#include "ObstacleBase.h"
#include <vector>
#include <memory>

class Shot;
class ObstacleShot : public ObstacleBase
{
public:
	ObstacleShot(VECTOR pos);
	virtual ~ObstacleShot();

	void Init();
	void End();
	void Update();
	void Draw();
private:
	std::vector<std::shared_ptr<Shot>>m_pShot;

	int m_shotCount;
};

