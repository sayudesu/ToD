#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/Vec2.h"
#include "../../Util/Tracking.h"
#include "../../Util/ObstructSelectNo.h"
#include "../../MapDatas.h"
#include "../../Util/ObjectData.h"

// �v���C���[�N���X
class Player
{
public:
	Player();
	virtual ~Player();

	// ����������
	void Init(MapDatas mapChip);
	// �������J������
	void End();
	// �X�V����
	void Update();
	// �`��
	void Draw();
	// �v���C���[�̈ʒu��n��
	VECTOR SetPos() { return m_pos; }
	// �}�E�X��������Ă��邩�ǂ���
	bool GetObjCreate() { return m_isResultObject; }
	// �J�����N���X�ɓn��
	Tracking GetTracingData();
	// ���݂̃I�u�W�F�N�g�R�X�g��n��
	int GetObjectCostNum();

	// �I�𒆂̏�Ԃ�n��
	ObstructSelect GetObstructData();

	ObjectData GetCollShotDatas();

	// �}�b�v�`�b�v��̍��W��n��
	int GetMapChipX();
	int GetMapChipZ();

private:
	// ����𐧌�
	void UpdateControl();
	void UpdateObjSelect();
	// �͈͊O����
	bool CheckOutSide();
	// �I�u�W�F�N�g�̃R�X�g�֘A
	void ObjectCost();
private:
	// �v���C���[�̈ʒu
	VECTOR m_pos;
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
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
	// �ړ��ʒu���m�F
	VECTOR m_checkMapChipNo;

	ObstructSelect m_selectObstructData;

	MapDatas m_mapData;

	ObjectData m_collShotData;

	bool m_isSelectPowerUp;
};

