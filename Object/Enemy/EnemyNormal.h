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

private:
	void CheckColl();
private:
	// �G�̓��������@�܂����Ȃ̂ł���͏���
	int moveCount;
	// �������ǂ���
	bool m_isNextMove;
	// ����
	VECTOR m_dir;
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
	int m_count;
	int forX;
	int forZ;

	bool isRandMove = false;

	std::vector<int> m_recordX;
	std::vector<int> m_recordZ;

	std::vector<int>moveDirZ;
	std::vector<int>moveDirX;

	bool m_isHit;

	// ����p
	Collision3D* m_pColl;
};

