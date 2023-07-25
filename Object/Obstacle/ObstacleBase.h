#pragma once
#include <DxLib.h>

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
	VECTOR SetPos() const { return m_pos; }
	virtual void GetTarGetPos(VECTOR pos) { m_targetPos = pos; }

protected:
	VECTOR m_pos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR m_targetPos = VGet(0.0f, 0.0f, 0.0f);
};