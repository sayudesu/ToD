#include "SoundFunctions.h"
#include <DxLib.h>
#include <vector>
#include <cassert>

namespace
{
	// サウンドハンドル
	std::vector<int> m_soundHandle;

	// サウンドファイル名
	const char* const kFileName[SoundFunctions::SoundIdMaxNum] =
	{
		// BGM
		"Data/Sound/Bgm/Title.mp3",  // はじまるぞ
		"Data/Sound/Bgm/Battle.mp3", // 激しい
		"Data/Sound/Bgm/End.mp3",    // すこしかなしい
		// SE
		"Data/Sound/SE/Select.mp3",		  // 選択中
		"Data/Sound/SE/SelectChange.mp3", // 選択決定
		"Data/Sound/SE/Over.mp3",         // 選択できません
		"Data/Sound/SE/Dwon.mp3",         // でぅーん
		"Data/Sound/SE/Change.mp3",         // かちーん
		"Data/Sound/SE/Set.mp3",         // 設置
		"Data/Sound/SE/Shot.mp3",         // 撃つ
	};
}

namespace SoundFunctions
{
	void Load(GameData::Sound soundVol)
	{
		// サウンドデータの読み込み
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			assert(handle != -1);
			m_soundHandle.push_back(handle);
		}

		// 音量だけロードします
		ReLoad(soundVol);
	}

	void UnLoad()
	{
		// サウンドデータの解放
		for (auto& handle : m_soundHandle)
		{
			DeleteSoundMem(handle);
		}
	}

	// 音量だけロードします
	void ReLoad(GameData::Sound soundVol)
	{
		// サウンドの初期調整
		// BGM
		SetVolume(SoundIdTitle, soundVol.Bgm);
		SetVolume(SoundIdBattle, soundVol.Bgm);
		SetVolume(SoundIdEnd, soundVol.Bgm);
		// SE
		SetVolume(SoundIdSelct, soundVol.SE);
		SetVolume(SoundIdSelctChange, soundVol.SE);
		SetVolume(SoundIdOver, soundVol.SE);
		SetVolume(SoundIdDwon, soundVol.SE);
		SetVolume(SoundIdChange, soundVol.SE);
		SetVolume(SoundIdSet, soundVol.SE);
		SetVolume(SoundIdShot, soundVol.SE);
	}

	// 初めにBGMを流す
	void StartBgm(SoundId id)
	{
		PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
	}

	// BGMが流れているかどうか
	// 流れていない場合はもう一度流す
	void ReStartBgm(SoundId id)
	{
		if (CheckSoundMem(m_soundHandle[id]) == 0)
		{
			PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
		}
	}

	// BGMを止める
	void StopBgm(SoundId id)
	{
		StopSoundMem(m_soundHandle[id]);
	}
	
	// 効果音の再生
	void Play(SoundId id)
	{
		PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
	}

	// 音量設定	0~255
	void SetVolume(SoundId id, int volume)
	{
		ChangeVolumeSoundMem(volume, m_soundHandle[id]);
	}

	// 現在の音量を得る
	int GetVolume(SoundId id)
	{
		int volume = 0;
		// 0から1000の範囲を0から255に
		return volume = ((GetVolumeSoundMem(m_soundHandle[id]) - 0) * (255 - 0)) / (10000 - 0);
	}
}
