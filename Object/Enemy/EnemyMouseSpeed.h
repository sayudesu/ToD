#pragma once
#include "EnemyBase.h"

/// <summary>
/// ��{�I�ȓG�N���X(�˂���)
/// </summary>
class EnemyMouseSpeed : public EnemyBase
{
public:
	EnemyMouseSpeed();
	virtual ~EnemyMouseSpeed();

	void Attack()override;

	// �����蔻��p�f�[�^
	ObjectData GetCollDatas()override;
};

