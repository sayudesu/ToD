#pragma once
enum ObstructSelectNo
{
	// �����I�����Ă��Ȃ����
	EMPTY_PRESS,
	EMPTY_RESULT,
	// �I����ʂ��J�������
	SELECT_PRESS,
	SELECT_RESULT,
	// �I�u�W�F�N�g��ݒu������
	OBSTRUCT_PRESS,
	OBSTRUCT_RESULT,
	// �I�u�W�F�N�g������������
	POWER_UP_PRESS,
	POWER_UP_RESULT,
	// �I�u�W�F�N�g���폜������
	ERASE_PRESS,
	ERASE_RESULT,

	// �I�u�W�F�N�g�̉���ݒu���邩�̏��
	HRAVY_PRESS,
	HRAVY_RESULT,

	NORMAL_PRESS,
	NORMAL_RESULT,

	MISSILE_PRESS,
	MISSILE_RESULT,

	SPEED_PRESS,
	SPEED_RESULT,

	DAMAGE_PRESS,
	DAMAGE_RESULT,
};

struct ObstructSelect
{
	// �I�������ԍ�
	ObstructSelectNo no;
};