#pragma once
#include <DxLib.h>

#include "../../Util/CollDatas.h"

// �V���b�g�N���X
class ShotBase
{
public:
	ShotBase(VECTOR pos);
	virtual~ShotBase() {};

	virtual void Init  (VECTOR taegetPos, VECTOR scale, VECTOR rotation, float speed, bool isTracking) {};
	virtual void End   ()    {};
	virtual void Update()    {};
	virtual void Draw  ()    {};

	// �V���b�g����f�[�^
	virtual CollData GetCollData ()           { return m_collData; }
	// �V���b�g�̈ʒu
	virtual VECTOR   SetPos      ()const      { return m_pos;      }
	// �^�[�Q�b�g�ʒu
	virtual void     SetTargetPos(VECTOR pos) { m_targetPos = pos; }
	virtual bool     IsGetEnd    ();
protected:
	// �ړ��̌v�Z�����Ă��܂�
	void VecCalculation(VECTOR tagetPos, float speed, bool isTracking);
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
	// ����p�f�[�^
	CollData m_collData;
	// ���x
	float m_speed;
	// ���a
	float m_radius;
	// �ǐՂ��邩�ǂ���
	bool m_isTracking;
};

