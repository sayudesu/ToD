#pragma once
#include "EnemyBase.h"

// ����p
class Collision3D;

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

private:
	// ���菈��
	void CheckColl();
	// HP�̏���
	void CheckHp();
private:
	int m_hMouse;
	// �G�̓��������@�܂����Ȃ̂ł���͏���
	int moveCount;
	// �������ǂ���
	bool m_isNextMove;
	// ����
	VECTOR m_dir;
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
	// 3D���W����2D���W�ɕϊ�
	VECTOR m_screenPos;
	// �̗͌n
	float m_hp;

	int m_count;

	int forX;
	int forZ;

	bool isRandMove = false;

	std::vector<int> m_recordX;
	std::vector<int> m_recordZ;

	std::vector<int>moveDirZ;
	std::vector<int>moveDirX;

	bool m_isHit;
	bool m_isTempHit;
	int m_tempCountHit;

	// ����p
	Collision3D* m_pColl;
};

