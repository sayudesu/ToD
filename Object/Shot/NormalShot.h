#pragma once
#include "ShotBase.h"

class NormalShot : public ShotBase
{
public:
	NormalShot(VECTOR pos, int originNo,int no);
	~NormalShot();

	// ������
	void Init(VECTOR taegetPos, VECTOR scale, VECTOR rotation, float radius, float damage, float speed, bool isTracking)override;
	// ����p�f�[�^
	ObjectData GetCollData();
};

