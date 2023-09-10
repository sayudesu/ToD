#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/CollDatas.h"

class EnemyBase
{
public:
	EnemyBase() {};
	virtual ~EnemyBase() {};

	virtual void Init(VECTOR firstPos,int x,int y) = 0;
	virtual void End()    = 0;
	virtual void Update() = 0;
	virtual void Draw()   = 0;
	virtual void DrawUI() = 0;

	// エネミーの位置
	virtual VECTOR GetPos() const   { return m_pos; }
	virtual void SetPos(VECTOR pos) { m_pos = pos;  }
	// 判定データを受け取る
	virtual void SetCollData(std::vector<CollData>collData) { m_collObstacleShotData = collData; }
	// 当たり判定データ
	virtual CollData GetCollDatas() { return m_collData; }
	// 通る道
	virtual void SetRoadPos(std::vector<int> mapChip) { m_mapChip = mapChip; }

protected:
	VECTOR m_pos = VGet(0.0f, 0.0f, 0.0f);
	std::vector<int> m_mapChip{};
	// 判定データ
	// 自身のデータ
	CollData m_collData{};
	// プレイヤー設置オブジェクトのデータ
	std::vector<CollData> m_collObstacleShotData{};
};

