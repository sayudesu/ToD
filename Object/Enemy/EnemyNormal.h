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
	// 向き
	VECTOR m_dir;
	// ターゲット位置
	VECTOR m_targetPos;
};

