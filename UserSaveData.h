#pragma once
#include <vector>
#include "SaveData.h"

namespace SaveDataFunctions
{
	// �Z�[�u�f�[�^�����[�h���܂�
	void Load();
	// �f�[�^��ۑ����܂�
	void Save(SaveData data);

	// �T�E���h�̃Z�[�u�f�[�^��n��
	// 0����255
	SaveData GetSoundData();
	// 0����1000
	SaveData GetSoundBarData();
}
