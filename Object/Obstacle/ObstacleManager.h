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

	// 二次元配列を一次元配列にしてを返す
	std::vector<CollData> GetCollDatas();

	// 配列の数を渡す
	int GetNormalNum();

private:
	std::vector<std::shared_ptr<ObstacleBase>>m_pNormalObstacle;
	// 出現数をカウントします
	int m_count;
};

