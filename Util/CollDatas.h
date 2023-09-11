#pragma once
#include <DxLib.h>

// 当たり判定データ
struct CollData
{
	// 位置
	VECTOR pos;
	// 半径
	float radius;
	// ダメージ
	float datage;
	// 判定をみるかどうか
	bool isHit;
	// オブジェクトのが生成される番号
	int originNo;
	// オブジェクトに番号を付ける
	int no;
};
