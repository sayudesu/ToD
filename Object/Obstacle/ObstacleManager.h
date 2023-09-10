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

	// 二次元配列を一次元配列にしてを返す
	std::vector<CollData> GetCollDatas();
	// 敵の判定用データを受け取る
	void SetCollEnemyDatas(std::vector<CollData> collEnemyData);
	// 必要の無いshotの番号を受け取る
	void SetEraseShotNo(std::vector<int> eraseShotNo);

private:
	std::vector<std::shared_ptr<ObstacleBase>>m_pNormalObstacle;
	// 出現数をカウントします
	int m_countCreate;
};

