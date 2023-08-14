#pragma once

namespace LoadGraphFunction
{
	typedef enum GraphId
	{
		// 画像の名前
		VolCat,
		VolCatS,
		Wood,
		Bar,
		OutSideBar,
		OutSideBarBg,
		SelectFrame,
		SelectCatHand,

		// 最大数
		GraphIdMaxNum
	}GraphId;

	// 画像をロードします
	void Load();
	// メモリを解放します
	void UnLoad();
	// 画像データを渡す
	int GraphData(GraphId name);
}

