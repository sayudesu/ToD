#pragma once
#include "EnemyBase.h"

/// <summary>
/// ��{�I�ȓG�N���X(�˂���)
/// </summary>
class EnemyMouse : public EnemyBase
{
public:
	EnemyMouse();
	virtual ~EnemyMouse();

	// �����蔻��p�f�[�^
	CollData GetCollDatas()override;
};

