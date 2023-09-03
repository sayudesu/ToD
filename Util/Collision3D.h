#pragma once
#include <DxLib.h>
#include <vector>

// 3D�ŋ����m�̓��������蔻��
class Collision3D
{
public:
	Collision3D() {};
	~Collision3D() {};
	
	/// <summary>
	/// �����m�̓����蔻�菈��
	/// </summary>
	/// <param name="pos1">������������I�u�W�F�N�g�̈ʒu</param>
	/// <param name="pos2">������������I�u�W�F�N�g�̈ʒu</param>
	/// <param name="radius1">pos1�̔��a</param>
	/// <param name="radius2">pos2�̔��a</param>
	/// <returns></returns>
	bool UpdateCheck(VECTOR pos1, VECTOR pos2, float radius1, float radius2);
};

