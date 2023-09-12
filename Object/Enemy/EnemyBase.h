#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/CollDatas.h"

class EnemyBase
{
public:
	EnemyBase() {};
	virtual ~EnemyBase() {};

	virtual void Init(VECTOR firstPos,int x,int z);
	virtual void End();
	virtual void Update();
	virtual void Draw();
	virtual void DrawUI();

	// �G�l�~�[�̈ʒu
	virtual VECTOR GetPos() const   { return m_pos; }
	// ����f�[�^���󂯎��
	virtual void SetCollData(std::vector<CollData>collData) { m_collObstacleShotData = collData; }
	// �����蔻��f�[�^
	virtual CollData GetCollDatas() { return m_collData; }
	// �ʂ铹
	virtual void SetRoadPos(std::vector<int> mapChip) { m_mapChip = mapChip; }
	// �^������_���[�W���󂯎��
	virtual void SetHitDamage(int damage);
	// ���̃f�[�^���K�v�Ȃ̂��ǂ���
	virtual bool GetErase();
	// �����ʒu��T���Ĉړ�
	virtual void ChangeNextPos(bool& isMoveing);

protected:
	// ���f���n���h��
	int m_hModel;
	// ���f���̃t�@�C���p�X
	const char* m_filePathModel;
	// �ʒu
	VECTOR m_pos = VGet(0.0f, 0.0f, 0.0f);
	// �̗�
	int m_hp = 0;
	// �_���[�W
	int m_damage = 0;
	// �}�b�v�`�b�v�f�[�^
	std::vector<int> m_mapChip{};
	// �v���C���[�ݒu�I�u�W�F�N�g�̃f�[�^
	std::vector<CollData> m_collObstacleShotData{};
	// ���g�̃f�[�^
	CollData m_collData{};


	// ����
	VECTOR m_dir;
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
	// 3D���W����2D���W�ɕϊ�
	VECTOR m_screenPos;
	// �������ǂ���
	bool m_isNextMove;
	// �ŏI�n�_�܂œ���������
	bool m_isEndPos;
	// �`�b�v�ԍ��ł̌��݈ʒu
	int m_chipPosX;
	int m_chipPosZ;
	// �����_���œ������������s���邩�ǂ���
	bool m_isRandMove;
	// �������ʒu���L�^�������ꏊ��ʂ�Ȃ��l�ɂ���
	std::vector<int> m_recordX;
	std::vector<int> m_recordZ;
	// �����_���œ����ꍇ�ǂ̕����ɓ����������߂�
	std::vector<int>m_moveDirX;
	std::vector<int>m_moveDirZ;
};

