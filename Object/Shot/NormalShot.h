#pragma once
#include "ShotBase.h"

class NormalShot : public ShotBase
{
public:
	NormalShot(VECTOR pos, int originNo,int no);
	~NormalShot();

	// ������
	void Init(int handle, int shotFrameCount,VECTOR taegetPos, VECTOR scale, VECTOR rotation, float radius, float damage, float speed, bool isTracking)override;
	// ����p�f�[�^
	ObjectData GetCollData()override;
};

