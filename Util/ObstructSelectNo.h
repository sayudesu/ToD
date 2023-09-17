#pragma once
enum ObstructSelectNo
{
	EMPTY_PRESS,
	EMPTY_RESULT,

	POWER_UP_PRESS,
	POWER_UP_RESULT,

	OBSTRUCT_PRESS,
	OBSTRUCT_RESULT,

	ERASE_PRESS,
	ERASE_RESULT
};

enum ObstructNo
{
	NONE_PRESS,
	NONE_RESULT,

	NORMAL_PRESS,
	NORMAL_RESULT,

	HRAVY_PRESS,
	HRAVY_RESULT
};

struct ObstructSelect
{
	// 選択した番号
	ObstructSelectNo no;
	// 設置するオブストラクトの番号
	ObstructNo obstructNo;
	//// 設置しているオブストラクトを強化する番号
	//ObstructSelectNo obstructUpNo;
};