#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/ObjectData.h"
#include "../../Util/ObstructSelectNo.h"

class ObstacleBase;
class ObstacleManager
{
public:
	ObstacleManager();
	virtual ~ObstacleManager();

	void Init();
	void End();
	/// <summary>
	/// 選択したオブジェクトを生成
	/// </summary>
	/// <param name="pos">  設置位置</param>
	/// <param name="obsNo">設置するオブジェクトID</param>
	/// <param name="no">   設置順番の番号</param>
	/// <param name="mapCihpX">   マップチップ上でのX番号</param>
	/// <param name="mapCihpY">   マップチップ上でのY番号</param>
	void Create(VECTOR pos, int obsNo, int no, int mapCihpX, int mapCihpY);
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
	// 強化するオブジェクトを探す
	void SetPowerUpPos(ObstructSelectNo no,int mapChipX, int mapChipY);

private:
	std::vector<ObstacleBase*>m_pObstacle;
};

