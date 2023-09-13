#pragma once
#include "EnemyBase.h"

/// <summary>
/// 基本的な敵クラス(ねずみ)
/// </summary>
class EnemyMouseSpeed : public EnemyBase
{
public:
	EnemyMouseSpeed();
	virtual ~EnemyMouseSpeed();

	void Attack()override;

	// 当たり判定用データ
	ObjectData GetCollDatas()override;
};

