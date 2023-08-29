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
	void NextPosChange();
	void Draw();

private:
	// ����
	VECTOR m_dir;
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
	int m_count;
	int forX;
	int forZ;

	std::vector<int> m_testPosX;
	std::vector<int> m_testPosZ;
};

