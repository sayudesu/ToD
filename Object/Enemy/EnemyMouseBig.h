#pragma once
#include "EnemyBase.h"

/// <summary>
/// 基本的な敵クラス(ねずみ)
/// </summary>
class EnemyMouseBig : public EnemyBase
{
public:
	EnemyMouseBig();
	virtual ~EnemyMouseBig();

	void Attack()override;

	// 当たり判定用データ
	ObjectData GetCollDatas()override;
};

