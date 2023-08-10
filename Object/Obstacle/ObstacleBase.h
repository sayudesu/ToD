#pragma once
#include <DxLib.h>

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
	virtual VECTOR SetPos() const { return m_pos; }
	// ターゲットの位置
	virtual void GetTarGetPos(VECTOR pos) { m_targetPos = pos; }

protected:
	// 位置
	VECTOR m_pos = VGet(0.0f, 0.0f, 0.0f);
	// ターゲット位置
	VECTOR m_targetPos = VGet(0.0f, 0.0f, 0.0f);
};