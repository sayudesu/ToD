#pragma once
#include <DxLib.h>

// �����蔻��f�[�^
struct ObjectData
{
	// �ʒu
	VECTOR pos;
	// ���a
	float radius;
	// �_���[�W
	float datage;
	// ���x
	float speed;
	// �T�C�Y
	float size;
	// �̗�
	float hp;
	// ������݂邩�ǂ���
	bool isHit;

	// �U�����Ă��邩�ǂ���S
	bool isAttack;
};
