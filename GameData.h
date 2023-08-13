#pragma once

// 保存するリスト
typedef struct 
{	
	// サウンド
	struct Sound
	{
		int Bgm;
		int SE;
	};

	// 保存する場所
	struct Input
	{
		int Bgm_;
		int SE_;
	};

} GameData;
