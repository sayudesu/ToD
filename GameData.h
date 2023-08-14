#pragma once

// 保存するリスト
typedef struct 
{	
	// アイコン
	struct Icon
	{
		int Icon;
	};
	// サウンド
	struct Sound
	{
		int Bgm;
		int SE;
	};



	// 保存する場所
	struct Input
	{
		int Icon_;
		int Bgm_;
		int SE_;
	};

} GameData;
