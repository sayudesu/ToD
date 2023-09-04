#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/CollDatas.h"

// 障害物クラスベース
class ObstacleBase
{
public:
	ObstacleBase(){};
	virtual ~ObstacleBase() {};

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// 障害物の位置
	virtual VECTOR GetPos() const { return m_pos; }
	// ターゲットの位置
	virtual void SetTarGetPos(VECTOR pos) { m_targetPos = pos; }
	// 当たり判定データ
	virtual std::vector<CollData> GetCollDatas() { return m_collData; }
	// エネミーの判定用データ
	virtual void SetCollEnemyDatas(std::vector<CollData> collEnemyData) { m_collEnemyData = collEnemyData; }
	// ショットの数
	virtual int SetShotNum() { return 0; }

protected:
	// 位置
	VECTOR m_pos = VGet(0.0f, 0.0f, 0.0f);
	// ターゲット位置
	VECTOR m_targetPos = VGet(0.0f, 0.0f, 0.0f);
	// 当たり判定データ
	std::vector<CollData> m_collData;
	std::vector<CollData> m_collEnemyData;
};