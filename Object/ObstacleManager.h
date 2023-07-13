#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>

class ObstacleBase;
class ObstacleManager
{
public:
	ObstacleManager();
	virtual ~ObstacleManager();

	void Init();
	void End();
	void Create(VECTOR pos);
	void Update();
	void Draw();
private:
	std::vector<std::shared_ptr<ObstacleBase>>m_pObstacle;
	int m_count;
};

