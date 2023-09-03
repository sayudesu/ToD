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
	// �z��̐����̃T�C�Y
	int m_pos1Num;
	int m_pos2Num;
	// �z��̍ő�l
	int m_tempMax1Num;
	int m_tempMax2Num;
};

