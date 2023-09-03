#pragma once
#include <DxLib.h>
#include <vector>

class Collision3D
{
public:
	Collision3D();
	~Collision3D();

	bool UpdateCheck(VECTOR pos1, VECTOR pos2, float radius1, float radius2);
private:
	// 配列の数分のサイズ
	int m_pos1Num;
	int m_pos2Num;
	// 配列の最大値
	int m_tempMax1Num;
	int m_tempMax2Num;
};

