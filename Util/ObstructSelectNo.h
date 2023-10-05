#pragma once
enum ObstructSelectNo
{
	// 何も選択していない状態
	EMPTY_PRESS,
	EMPTY_RESULT,
	// 選択画面を開いた状態
	SELECT_PRESS,
	SELECT_RESULT,
	// オブジェクトを設置する状態
	OBSTRUCT_PRESS,
	OBSTRUCT_RESULT,
	// オブジェクトを強化する状態
	POWER_UP_PRESS,
	POWER_UP_RESULT,
	// オブジェクトを削除する状態
	ERASE_PRESS,
	ERASE_RESULT,

	// オブジェクトの何を設置するかの状態
	HRAVY_PRESS,
	HRAVY_RESULT,

	NORMAL_PRESS,
	NORMAL_RESULT,

	MISSILE_PRESS,
	MISSILE_RESULT,

	SPEED_PRESS,
	SPEED_RESULT,

	DAMAGE_PRESS,
	DAMAGE_RESULT,
};

struct ObstructSelect
{
	// 選択した番号
	ObstructSelectNo no;
};