#pragma once
enum ObstructSelectNo
{
	EMPTY_PRESS,
	EMPTY_RESULT,

	POWER_UP_PRESS,
	POWER_UP_RESULT,

	OBSTRUCT_PRESS,
	OBSTRUCT_RESULT,

	ERASE_PRESS,
	ERASE_RESULT
};

enum ObstructNo
{
	NONE_PRESS,
	NONE_RESULT,

	NORMAL_PRESS,
	NORMAL_RESULT,

	HRAVY_PRESS,
	HRAVY_RESULT
};

struct ObstructSelect
{
	// �I�������ԍ�
	ObstructSelectNo no;
	// �ݒu����I�u�X�g���N�g�̔ԍ�
	ObstructNo obstructNo;
	//// �ݒu���Ă���I�u�X�g���N�g����������ԍ�
	//ObstructSelectNo obstructUpNo;
};