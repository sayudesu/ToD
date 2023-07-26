#pragma once
#include "ObstacleBase.h"
#include <vector>
#include <memory>

class ShotBase;
class ObstacleShot : public ObstacleBase
{
public:
	ObstacleShot(VECTOR pos);
	virtual ~ObstacleShot();

	void Init();
	void End();
	void Update();
	void Draw();

	void GetTarGetPos(VECTOR pos);
private:
	std::vector<std::shared_ptr<ShotBase>>m_pShot;
	int m_shootFrameCount;
};

