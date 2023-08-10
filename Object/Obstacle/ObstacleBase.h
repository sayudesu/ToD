#pragma once
#include <DxLib.h>

// ��Q���N���X�x�[�X
class ObstacleBase
{
public:
	ObstacleBase(){};
	virtual ~ObstacleBase() {};

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// ��Q���̈ʒu
	virtual VECTOR SetPos() const { return m_pos; }
	// �^�[�Q�b�g�̈ʒu
	virtual void GetTarGetPos(VECTOR pos) { m_targetPos = pos; }

protected:
	// �ʒu
	VECTOR m_pos = VGet(0.0f, 0.0f, 0.0f);
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos = VGet(0.0f, 0.0f, 0.0f);
};