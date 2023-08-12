#pragma once
namespace SoundFunctions
{
	typedef enum SoundId
	{
		// BGM
		SoundIdTitle,		// �͂��܂邼
		SoundIdBattle,		// ������
		SoundIdEnd,		    // ���������Ȃ���

		SoundIdSelct,
		SoundIdSelctChange,
		SoundIdOver,

		SoundIdMaxNum
	}SoundId;

	// ���[�h�A�A�����[�h
	void Load();
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

