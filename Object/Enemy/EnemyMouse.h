#pragma once
#include "EnemyBase.h"

/// <summary>
/// 基本的な敵クラス(ねずみ)
/// </summary>
class EnemyMouse : public EnemyBase
{
public:
	EnemyMouse();
	virtual ~EnemyMouse();

	void Attack()override;

	// 当たり判定用データ
	ObjectData GetCollDatas()override;
};

