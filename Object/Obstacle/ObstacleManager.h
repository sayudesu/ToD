#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include "../../Util/CollDatas.h"

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

	void SetTarGetPos(VECTOR pos);

	VECTOR GetPos(int num);

	std::vector<std::vector<CollData>> GetCollDatas();

	// 配列の数を渡す
	int GetNormalNum();

private:
	std::vector<std::shared_ptr<ObstacleBase>>m_pObstacle;
	// 出現数をカウントします
	int m_count;
};

