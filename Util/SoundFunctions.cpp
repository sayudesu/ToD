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
		"Data/Sound/Bgm/Title.mp3",  // �͂��܂邼
		"Data/Sound/Bgm/Battle.mp3", // ������
		"Data/Sound/Bgm/End.mp3",    // ���������Ȃ���
		// SE
		"Data/Sound/SE/Select.mp3",		  // �I��
		"Data/Sound/SE/SelectChange.mp3", // �I������
		"Data/Sound/SE/Over.mp3",         // �I���ł��܂���
	};
}

namespace SoundFunctions
{
	void Load(SaveData soundVol)
	{
		// �T�E���h�f�[�^�̓ǂݍ���
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			m_soundHandle.push_back(handle);
		}

		// �T�E���h�̏�������
		// BGM
		SetVolume(SoundIdTitle, soundVol.Bgm);
		SetVolume(SoundIdBattle, soundVol.Bgm);
		SetVolume(SoundIdEnd, soundVol.Bgm);
		// SE
		SetVolume(SoundIdSelct, soundVol.SE);
		SetVolume(SoundIdSelctChange, soundVol.SE);
		SetVolume(SoundIdOver, soundVol.SE);
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
	void StartBgm(SoundId id)
	{
		PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
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

	// ���݂̉��ʂ𓾂�
	int GetVolume(SoundId id)
	{
		int volume = 0;
		// 0����1000�͈̔͂�0����255��
		return volume = ((GetVolumeSoundMem(m_soundHandle[id]) - 0) * (255 - 0)) / (10000 - 0);
	}
}
