#pragma once
#include "EnemyBase.h"

/// <summary>
/// ��{�I�ȓG�N���X(�˂���)
/// </summary>
class EnemyMouseBig : public EnemyBase
{
public:
	EnemyMouseBig();
	virtual ~EnemyMouseBig();

	void Attack()override;

	// �����蔻��p�f�[�^
	ObjectData GetCollDatas()override;
};

