#pragma once
#include <DxLib.h>

// �V���b�g�N���X
class ShotBase
{
public:
	ShotBase(VECTOR pos);
	virtual~ShotBase() {};

	virtual void Init() {};
	virtual void End() {};
	virtual void Update() {};
	virtual void Draw() {};

	// �V���b�g�̈ʒu
	virtual VECTOR SetPos()const{ return m_pos; }
	// �^�[�Q�b�g�ʒu
	virtual void SetTargetPos(VECTOR pos) { m_targetPos = pos; }
	virtual bool IsGetEnd();
protected:
	// �ړ��̌v�Z�����Ă��܂�
	void VecCalculation(VECTOR tagetPos, float speed);
protected:
	// 3D���f���n���h��
	int m_hShot;
	// �ʒu
	VECTOR m_pos;
	// ����
	VECTOR m_dir;
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
	// ��ʊO����
	bool m_isScreenOut;
	// �ړI�n�ƍ��̋���
	float m_nowPosToNextPosX;
	float m_nowPosToNextPosZ;
};

