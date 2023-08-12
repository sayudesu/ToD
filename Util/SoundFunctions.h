#pragma once
namespace SoundFunctions
{
	typedef enum SoundId
	{
		// BGM
		SoundIdTitle,		// はじまるぞ
		SoundIdBattle,		// 激しい
		SoundIdEnd,		    // すこしかなしい

		SoundIdSelct,
		SoundIdSelctChange,
		SoundIdOver,

		SoundIdMaxNum
	}SoundId;

	// ロード、アンロード
	void Load();
	void UnLoad();

	// BGMの再生
	void StartBgm(SoundId id);
	void ReStartBgm(SoundId id);
	void StopBgm(SoundId id);

	// 効果音の再生
	void Play(SoundId id);

	// 音量設定	0~255
	void SetVolume(SoundId id, int volume);

	// 現在の音量を得る
	int GetVolume(SoundId id);
};

