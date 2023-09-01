#pragma once
#include "../Util/GameData.h"

namespace SaveDataFunctions
{
	// �Z�[�u�f�[�^�����[�h���܂�
	void Load();
	// �f�[�^��ۑ����܂�
	void Save(GameData::Input data, bool now = true);

	// �T�E���h�̃Z�[�u�f�[�^��n��
	// 0����255
	GameData::Sound GetSoundData();
	// 0����1000
	GameData::Sound GetSoundBarData();
	// �A�C�R���̃f�[�^�[��n��
	GameData::Icon GetIconData();
}
