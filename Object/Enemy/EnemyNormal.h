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
private:
	// ����
	VECTOR m_dir;
	// �^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
};

