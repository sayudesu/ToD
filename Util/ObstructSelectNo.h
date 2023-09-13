#pragma once
enum ObstructSelectNo
{
	EMPTY,
	POWER_UP,
	OBSTRUCT,
	ERASE
};

enum ObstructNo
{
	NONE,
	NORMAL,
	HRAVY
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