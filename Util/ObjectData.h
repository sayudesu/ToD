#pragma once
#include <DxLib.h>

// 当たり判定データ
struct ObjectData
{
	// 位置
	VECTOR pos;
	// 半径
	float radius;
	// ダメージ
	float datage;
	// 速度
	float speed;
	// サイズ
	float size;
	// 体力
	float hp;
	// 判定をみるかどうか
	bool isHit;

	// 攻撃しているかどうかS
	bool isAttack;
};
