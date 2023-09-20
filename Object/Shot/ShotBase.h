#pragma once
#include <DxLib.h>

#include "../../Util/ObjectData.h"

// �V���b�g�N���X
class ShotBase
{
public:
	ShotBase(VECTOR pos);
	virtual~ShotBase() {};

	virtual void Init  (int handle,int shotFrameCount,VECTOR taegetPos, VECTOR scale, VECTOR rotation, float radius, float damage, float speed, bool isTracking) {};
	virtual void End   ();
	virtual void Update();
	virtual void Draw  ();

	// �V���b�g����f�[�^
	virtual ObjectData GetCollData ()  { return m_collData; }
	// �V���b�g�̈ʒu
	virtual VECTOR   SetPos      ()const      { return m_pos;      }
	// �^�[�Q�b�g�ʒu
	virtual void     SetTargetPos(VECTOR pos) { m_targetPos = pos; }
	virtual bool     IsEnabled()const;
	virtual void	 SetEnabled(bool isEnabled);
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
	// �傫��
	VECTOR m_scale;
	// �U����
	float m_damage;
	// ��ʊO����
	bool m_isScreenOut;
	// �ړI�n�ƍ��̋���
	float m_nowPosToNextPosX;
	float m_nowPosToNextPosZ;
	// ����p�f�[�^
	ObjectData m_collData;
	// ���x
	float m_speed;
	// ���a
	float m_radius;
	// �ǐՂ��邩�ǂ���
	bool m_isTracking;
	// ���Ԗڂ̃I�u�W�F�N�g���琶������邩
	int m_originNo;
	// ���񐶐����ꂽ��
	int m_no;
	// ���̃V���b�g���������ǂ���
	bool m_isEnabled;
	// 
	bool m_isTrackingNow;
};

