#pragma once
#include "ShotBase.h"

class NormalShot : public ShotBase
{
public:
	NormalShot(VECTOR pos, int originNo,int no);
	~NormalShot();

	void Init(VECTOR taegetPos, VECTOR scale, VECTOR rotation, float speed, bool isTracking);
	void End();
	void Update();
	void Draw();

	CollData GetCollData();
};

