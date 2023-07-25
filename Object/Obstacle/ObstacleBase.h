#pragma once
#include <DxLib.h>

// ��Q���N���X�x�[�X
class ObstacleBase
{
public:
	ObstacleBase() {};
	virtual ~ObstacleBase() {};

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ��Q���̈ʒu
	VECTOR SetPos() const { return m_pos; }
	virtual void GetTarGetPos(VECTOR pos) { m_targetPos = pos; }

protected:
	VECTOR m_pos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR m_targetPos = VGet(0.0f, 0.0f, 0.0f);
};