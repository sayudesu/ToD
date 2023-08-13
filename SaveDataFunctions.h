#pragma once
#include "GameData.h"

namespace SaveDataFunctions
{
	// セーブデータをロードします
	void Load();
	// セーブデータの更新
	void RenewalData();
	// データを保存します
	void Save(GameData::Input data);

	// サウンドのセーブデータを渡す
	// 0から255
	GameData::Sound GetSoundData();
	// 0から1000
	GameData::Sound GetSoundBarData();
}
