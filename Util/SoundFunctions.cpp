#include "SoundFunctions.h"
#include <DxLib.h>
#include <vector>

namespace
{
	// サウンドハンドル
	std::vector<int> m_soundHandle;

	// サウンドファイル名
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
		// サウンドデータの読み込み
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			m_soundHandle.push_back(handle);
		}
	}

	void UnLoad()
	{
		// サウンドデータの解放
		for (auto& handle : m_soundHandle)
		{
			DeleteSoundMem(handle);
		}
	}

	// 初めにBGMを流す
	void StartBgm(SoundId id, int volume)
	{
		PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
		SetVolume(id, volume);
	}

	// BGMが流れているかどうか
	// 流れていない場合はもう一度流す
	void ReStartBgm(SoundId id)
	{
		if (CheckSoundMem(id) == 0)
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
}
