#pragma once
#include <DxLib.h>
#include "../../Util/Vec2.h"
#include "../../Util/Tracking.h"
#include <vector>
#include "../../Util/ObstructSelectNo.h"
#include "../../MapDatas.h"

class ObjectMenuDrawer;
class NormalShot;


// �v���C���[�N���X
class Player
{
public:
	Player();
	virtual ~Player();

	// ����������
	void Init();
	// �������J������
	void End();
	// �X�V����
	void Update();
	// �`��
	void Draw();
	// UI��p�`��
	void DrawUI();
	// �v���C���[�̈ʒu��n��
	VECTOR SetPos() { return m_pos; }
	// �}�E�X��������Ă��邩�ǂ���
	bool GetObjCreate() { return m_isResultObject; }
	// �Q�[���̐i�s���~�߂邩�ǂ���
	bool IsGetGameStop();
	// ����U���������Ȃ������ǂ���
	bool isSpecialAttack();
	// ����U���̏�Ԃ����Z�b�g����
	void SpecialAttackReset();
	// �V���b�g�������ǂ���
	void IsSetShot(bool isShot);
	// �J�����N���X�ɓn��
	Tracking GetTracingData();
	// ���݂̃I�u�W�F�N�g�R�X�g��n��
	int GetObjectCostNum();
	// �}�b�v�`�b�v�f�[�^���󂯂Ƃ�
	void SetMapChip(MapDatas mapChip);

	ObstructSelect GetObstructData();
private:
	// ����𐧌�
	void UpdateControl();
	// ����U���p
	void UpdateSpecialAttack();
	// �͈͊O����
	void CheckOutSide();
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
	VECTOR m_start3DPos;
	VECTOR m_end3DPos;
	// �ʒu���L�^���܂�
	std::vector<VECTOR>m_posHistory;
	// false : �����Ă��Ȃ� true : �����Ă���
	bool m_isResultObject;
	// �ݒu�o���邩�̍ŏI�m�F
	bool m_isSetObject;
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
	// �ړ��ʒu���m�F
	VECTOR m_checkMapChipNo;

	std::vector<VECTOR> recordChipNo{ VGet(-1, -1, -1) };

	ObstructSelect m_selectObstructData;

	MapDatas m_mapData;
};

