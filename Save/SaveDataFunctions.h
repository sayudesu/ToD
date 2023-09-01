#pragma once
#include "../Util/GameData.h"

namespace SaveDataFunctions
{
	// セーブデータをロードします
	void Load();
	// データを保存します
	void Save(GameData::Input data, bool now = true);

	// サウンドのセーブデータを渡す
	// 0から255
	GameData::Sound GetSoundData();
	// 0から1000
	GameData::Sound GetSoundBarData();
	// アイコンのデーターを渡す
	GameData::Icon GetIconData();
}
