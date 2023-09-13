#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/ObjectData.h"

class ObstacleBase;
class ObstacleManager
{
public:
	ObstacleManager();
	virtual ~ObstacleManager();

	void Init();
	void End();
	void Create(VECTOR pos, int obsNo, int no);
	void Update();
	void Draw();

	// オブジェクトの数を返す
	int GetNum();
	// ショットの数を返します
	int GetShotNum(int objNum);
	// 二次元配列を一次元配列にしてを返す
	ObjectData GetCollShotDatas(int objNum, int shotNum);
	// 敵の判定用データを受け取る
	void SetCollEnemyDatas(std::vector<ObjectData> collEnemyData);
	// 必要の無いshotの番号を受け取る
	void SetEraseShotData(std::vector<ObjectData> eraseShotData);
	// 必要のないショット番号を受け取る
	void SetShotErase(int objNum, int shotNum,bool erase);

private:
	std::vector<ObstacleBase*>m_pNormalObstacle;
};

