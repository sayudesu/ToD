#pragma once
#include "../GameData.h"

namespace SoundFunctions
{
	typedef enum SoundId
	{
		// BGM
		SoundIdTitle,		// �͂��܂邼
		SoundIdBattle,		// ������
		SoundIdEnd,		    // ���������Ȃ���
		// SE
		SoundIdSelct,	    // �I��
		SoundIdSelctChange, // �I������
		SoundIdOver,        // �I���ł��܂���
		SoundIdDwon,        // �ł��[��
		// �ő吔
		SoundIdMaxNum
	}SoundId;

	// ���[�h�A�A�����[�h
	void Load(GameData::Sound soundVol);
	void UnLoad();

	// BGM�̍Đ�
	void StartBgm(SoundId id);
	void ReStartBgm(SoundId id);
	void StopBgm(SoundId id);

	// ���ʉ��̍Đ�
	void Play(SoundId id);

	// ���ʐݒ�	0~255
	void SetVolume(SoundId id, int volume);

	// ���݂̉��ʂ𓾂�
	int GetVolume(SoundId id);
};

