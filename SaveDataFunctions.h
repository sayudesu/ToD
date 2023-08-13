#pragma once
#include "GameData.h"

namespace SaveDataFunctions
{
	// �Z�[�u�f�[�^�����[�h���܂�
	void Load();
	// �Z�[�u�f�[�^�̍X�V
	void RenewalData();
	// �f�[�^��ۑ����܂�
	void Save(GameData::Input data);

	// �T�E���h�̃Z�[�u�f�[�^��n��
	// 0����255
	GameData::Sound GetSoundData();
	// 0����1000
	GameData::Sound GetSoundBarData();
}
