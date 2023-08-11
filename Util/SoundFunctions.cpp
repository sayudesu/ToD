#include "SoundFunctions.h"
#include <DxLib.h>
#include <vector>

namespace
{
	// �T�E���h�n���h��
	std::vector<int> m_soundHandle;

	// �T�E���h�t�@�C����
	const char* const kFileName[SoundFunctions::SoundIdMaxNum] =
	{
		// BGM
		"Data/Sound/Bgm/0.mp3",
		"Data/Sound/Bgm/1.mp3",
		// SE
		"Data/Sound/SE/Select.mp3",
		"Data/Sound/SE/SelectChange.mp3",
		"Data/Sound/SE/Over.mp3",
	};
}

namespace SoundFunctions
{

	void Load()
	{
		// �T�E���h�f�[�^�̓ǂݍ���
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			m_soundHandle.push_back(handle);
		}
	}

	void UnLoad()
	{
		// �T�E���h�f�[�^�̉��
		for (auto& handle : m_soundHandle)
		{
			DeleteSoundMem(handle);
		}
	}

	// ���߂�BGM�𗬂�
	void StartBgm(SoundId id, int volume)
	{
		PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
		SetVolume(id, volume);
	}

	// BGM������Ă��邩�ǂ���
	// ����Ă��Ȃ��ꍇ�͂�����x����
	void ReStartBgm(SoundId id)
	{
		if (CheckSoundMem(id) == 0)
		{
			PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
		}
	}

	// BGM���~�߂�
	void StopBgm(SoundId id)
	{
		StopSoundMem(m_soundHandle[id]);
	}
	
	// ���ʉ��̍Đ�
	void Play(SoundId id)
	{
		PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
	}

	// ���ʐݒ�	0~255
	void SetVolume(SoundId id, int volume)
	{
		ChangeVolumeSoundMem(volume, m_soundHandle[id]);
	}
}
