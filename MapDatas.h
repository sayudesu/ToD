#pragma once
#include <vector>

struct MapDatas
{
	// チップの最大数
	int chipMaxX;
	int chipMaxZ;
	// チップのサイズ
	float chipSizeX;
	float chipSizeZ;

	// チップ番号
	// 地面
	int road;
	// 敵が通る道
	int enemyRoad;
	// 敵生成位置
	int enemySpawner;
	// 敵が立ち止まる位置
	int enemyStop;

	// 3D空間上のサイズ
	float blockSizeY;
	float blockSizeZ;

	// csvから読み込んだ一次元配列のマップ用
	// のデータが格納される
	std::vector<int> data;
};