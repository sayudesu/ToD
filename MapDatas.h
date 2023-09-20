#pragma once
#include <vector>

struct MapDatas
{
	// �`�b�v�̍ő吔
	int chipMaxX;
	int chipMaxZ;
	// �`�b�v�̃T�C�Y
	float chipSizeX;
	float chipSizeZ;

	// �`�b�v�ԍ�
	// �n��
	int road;
	// �G���ʂ铹
	int enemyRoad;
	// �G�����ʒu
	int enemySpawner;
	// �G�������~�܂�ʒu
	int enemyStop;

	// 3D��ԏ�̃T�C�Y
	float blockSizeY;
	float blockSizeZ;

	// csv����ǂݍ��񂾈ꎟ���z��̃}�b�v�p
	// �̃f�[�^���i�[�����
	std::vector<int> data;
};