#pragma once
#include <DxLib.h>
#include "../../Util/Vec2.h"
#include "../../Util/Tracking.h"
#include <vector>



class ObjectMenuDrawer;
class NormalShot;

// �v���C���[�N���X
class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void End();
	void Update();
	void Draw();
	void DrawUI();

	// �}�E�X�̈ʒu��Ԃ�
//	VECTOR SetMouseWorldPos() { return m_screenToWorldPos; }
	VECTOR SetPos() { return m_pos; }
	// �}�E�X��������Ă��邩�ǂ���
	bool SetMouseLeft() { return m_isResultObject; }

	// �Q�[���̐i�s���~�߂邩�ǂ���
	bool isGetGameStop();
	// ����U���������Ȃ������ǂ���
	bool isSpecialAttack();
	void SpecialAttackReset();
	// �V���b�g�������ǂ���
	void IsSetShot(bool isShot);
	// �J�����N���X�ɓn��
	Tracking GetTracingData();
private:
	// ����𐧌�
	void UpdateControl();
	void UpdateSpecialAttack();
	// �V���b�g�𐶐�
	void UpdateShot();
	// �I�u�W�F�N�g�̃R�X�g�֘A
	void ObjectCost();
private:
	// �v���C���[�̈ʒu
	VECTOR m_pos;
	// ����U���w��ꏊ
	VECTOR m_specialAttackPos;
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
	// ����U���������Ȃ������ǂ���
	bool m_isSpecialAttack;
	// ��ʂ���3D��Ԃɕϊ��p
	VECTOR m_screenPos;
	VECTOR m_start3DPos;
	VECTOR m_end3DPos;

	// �ʒu���L�^���܂�
	std::vector<VECTOR>m_posHistory;

	// �}�E�X�̍��N���b�N��������Ă��邩�ǂ���
	// false : �����Ă��Ȃ� true : �����Ă���
	bool m_isResultObject;
	// �ݒu�o���邩�̍ŏI�m�F
	bool m_isSetObject;

	// �I�u�W�F�N�g�R�X�g�֘A
	// �w�i�n���h��
	int m_hCostBg;
	// �R�X�g��
	int m_objectCostNum;

	// �V���b�g�̐�
	int m_countShotNo;
	bool m_isTrackingShot;
	int m_deleteFrameCountShot;
	// �V���b�g�������ǂ���
	bool m_isShot;
	// �J�����ɓn���p�̃f�[�^
	Tracking m_trackingData;

	// ���j���[�\�L
	ObjectMenuDrawer* m_pObjMenu;
	// �K�E�Z(�V���b�g)
	NormalShot* m_pShot;
};

