#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/ObjectData.h"

// 障害物クラスベース
class ObstacleBase
{
public:
	ObstacleBase() {};
	virtual ~ObstacleBase() {};

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// 障害物の位置
	virtual VECTOR GetPos() const { return m_pos; }
	// 当たり判定データ
	virtual ObjectData GetCollShotDatas(int shotNum) { return ObjectData(); }
	// エネミーの判定用データ
	virtual void SetCollEnemyDatas(std::vector<ObjectData> collEnemyData) { m_collEnemyData = collEnemyData; }
	// ショットの数
	virtual int GetShotNum() { return 0; }
	// いらないショットの番号を受け取る
	virtual void SetEraseShotData(std::vector<ObjectData> eraseShotData) {};
	// 必要のないショット番号を受け取る
	virtual void SetShotErase(int shotNum, bool erase) {};

protected:
	// 位置
	VECTOR m_pos       = VGet(0.0f, 0.0f, 0.0f);
	// ターゲット位置
	VECTOR m_targetPos = VGet(0.0f, 0.0f, 0.0f);
	// 当たり判定データ
	std::vector<ObjectData> m_collShotData {};
	std::vector<ObjectData> m_collEnemyData{};
};