#pragma once
namespace SoundFunctions
{
	typedef enum SoundId
	{
		// BGM
		SoundIdTitle,		// �^�C�g����ʂ�BGM
		SoundIdMain,		// ���C��(�Q�[���v���C)��ʂ�BGM

		SoundIdSelct,
		SoundIdSelctChange,
		SoundIdOver,

		SoundIdMaxNum
	}SoundId;

	// ���[�h�A�A�����[�h
	void Load();
	void UnLoad();

	// BGM�̍Đ�
	void StartBgm(SoundId id, int volume = 255);
	void ReStartBgm(SoundId id);
	void StopBgm(SoundId id);

	// ���ʉ��̍Đ�
	void Play(SoundId id);

	// ���ʐݒ�	0~255
	void SetVolume(SoundId id, int volume);
};

