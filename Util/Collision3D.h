#pragma once
#include <DxLib.h>
#include <vector>

// 3Dで球同士の当た当たり判定
class Collision3D
{
public:
	Collision3D() {};
	~Collision3D() {};
	
	/// <summary>
	/// 球同士の当たり判定処理
	/// </summary>
	/// <param name="pos1">判定を見たいオブジェクトの位置</param>
	/// <param name="pos2">判定を見たいオブジェクトの位置</param>
	/// <param name="radius1">pos1の半径</param>
	/// <param name="radius2">pos2の半径</param>
	/// <returns></returns>
	bool UpdateCheck(VECTOR pos1, VECTOR pos2, float radius1, float radius2);
};

