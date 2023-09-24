#pragma once
#include "ShotBase.h"

class MissileShot : public ShotBase
{
public:
	MissileShot(VECTOR pos, int originNo, int no);
	~MissileShot();

	// ������
	void Init(int handle, int shotFrameCount, VECTOR taegetPos, VECTOR scale, VECTOR rotation, float radius, float damage, float speed, bool isTracking)override;
	void FirstMove()override;
	void VecCalculation(VECTOR tagetPos, float speed, bool isTracking)override;
	// ����p�f�[�^
	ObjectData GetCollData()override;
private:
	int m_frameCount;
	int m_num;

	float dirX;
	float dirZ;

	int m_fspeed;
};

