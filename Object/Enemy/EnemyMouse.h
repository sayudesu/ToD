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

	void Attack()override;

	// �����蔻��p�f�[�^
	ObjectData GetCollDatas()override;
};
