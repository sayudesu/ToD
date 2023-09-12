#pragma once
#include "EnemyBase.h"

class EnemyNormal : public EnemyBase
{
public:
	EnemyNormal();
	virtual ~EnemyNormal();

	void Init(VECTOR firstPos, int x, int z);
	void End();
	void Update();
	void ChangeNextPos(bool & isMoveing);
	void Draw();
	void DrawUI();

	// �����蔻��p�f�[�^
	CollData GetCollDatas();
	// �^������_���[�W���󂯎��
	void SetHitDamage(int damage);
	// ���̃I�u�W�F�N�g���K�v���ǂ���
	bool GetErase();
private:
	// ���f���n���h��
	int m_hMouse;
	// �G�̓��������@�܂����Ȃ̂ł���͏���
	int m_moveCount;
	// �������ǂ���
	bool m_isNextMove;
	// �ŏI�n�_�܂œ���������
	bool m_isEndPos;
	// ����
	VECTOR m_dir;
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
	// 3D���W����2D���W�ɕϊ�
	VECTOR m_screenPos;
	// �`�b�v�ԍ��ł̌��݈ʒu
	int m_ChipPosX;
	int m_ChipPosZ;
	// �����_���œ������������s���邩�ǂ���
	bool m_isRandMove;
	// �������ʒu���L�^�������ꏊ��ʂ�Ȃ��l�ɂ���
	std::vector<int> m_recordX;
	std::vector<int> m_recordZ;
	// �����_���œ����ꍇ�ǂ̕����ɓ����������߂�
	std::vector<int>m_moveDirX;
	std::vector<int>m_moveDirZ;
};

