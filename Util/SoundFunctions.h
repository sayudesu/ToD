#pragma once
namespace SoundFunctions
{
	typedef enum SoundId
	{
		// BGM
		SoundIdTitle,		// タイトル画面のBGM
		SoundIdMain,		// メイン(ゲームプレイ)画面のBGM

		SoundIdSelct,
		SoundIdSelctChange,
		SoundIdOver,

		SoundIdMaxNum
	}SoundId;

	// ロード、アンロード
	void Load();
	void UnLoad();

	// BGMの再生
	void StartBgm(SoundId id, int volume = 255);
	void ReStartBgm(SoundId id);
	void StopBgm(SoundId id);

	// 効果音の再生
	void Play(SoundId id);

	// 音量設定	0~255
	void SetVolume(SoundId id, int volume);
};

