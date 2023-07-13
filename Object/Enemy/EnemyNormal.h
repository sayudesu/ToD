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
	void Draw();
};

