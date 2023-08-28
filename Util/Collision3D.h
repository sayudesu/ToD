#pragma once
#include <DxLib.h>
#include <vector>

class Collision3D
{
public:
	Collision3D();
	~Collision3D();

	bool UpdateCheck(std::vector<VECTOR>pos1, std::vector<VECTOR>pos2);
private:
	// �z��̐����̃T�C�Y
	int m_pos1Num;
	int m_pos2Num;
	// �z��̍ő�l
	int m_tempMax1Num;
	int m_tempMax2Num;
};

