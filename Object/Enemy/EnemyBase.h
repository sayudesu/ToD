#pragma once
#include <DxLib.h>
class EnemyBase
{
public:
	EnemyBase() {};
	virtual ~EnemyBase() {};

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// エネミーの位置
	VECTOR SetPos() const { return m_pos; }

protected:
	VECTOR m_pos = VGet(300.0f, 0.0f, 0.0f);
};

