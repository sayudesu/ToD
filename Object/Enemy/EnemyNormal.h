#pragma once
#include "EnemyBase.h"


class EnemyNormal : public EnemyBase
{
public:
	EnemyNormal();
	virtual ~EnemyNormal();

	void Init();
	void End();
	void Update();
	void NextPosChange();
	void Draw();

	// �ʂ铹
//	void SetRoadPos(std::vector<int> mapChip);

private:
	// ����
	VECTOR m_dir;
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
};

