#pragma once
enum ObstructSelectNo
{
	EMPTY,
	POWER_UP,
	OBSTRUCT,
	ERASE
};

enum ObstructNo
{
	NONE,
	NORMAL,
	HRAVY
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