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
	void Create(VECTOR pos, int no);
	void Update();
	void Draw();

	// オブジェクトの数を返す
	int GetNum();
	// ショットの数を返します
	int GetShotNum(int objNum);
	// 二次元配列を一次元配列にしてを返す
	CollData GetCollShotDatas(int objNum, int shotNum);
	// 敵の判定用データを受け取る
	void SetCollEnemyDatas(std::vector<CollData> collEnemyData);
	// 必要の無いshotの番号を受け取る
	void SetEraseShotData(std::vector<CollData> eraseShotData);
	// 必要のないショット番号を受け取る
	void SetShotErase(int objNum, int shotNum,bool erase);

private:
	std::vector<std::shared_ptr<ObstacleBase>>m_pNormalObstacle;
	// 出現数をカウントします
	int m_countCreate;
};

