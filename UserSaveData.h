#pragma once
#include <vector>
#include "SaveData.h"

namespace SaveDataFunctions
{
	// セーブデータをロードします
	void Load();
	// データを保存します
	void Save(SaveData data);

	// サウンドのセーブデータを渡す
	// 0から255
	SaveData GetSoundData();
	// 0から1000
	SaveData GetSoundBarData();
}
