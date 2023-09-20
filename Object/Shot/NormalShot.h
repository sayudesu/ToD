#pragma once
#include "ShotBase.h"

class NormalShot : public ShotBase
{
public:
	NormalShot(VECTOR pos, int originNo,int no);
	~NormalShot();

	// 初期化
	void Init(int handle, int shotFrameCount,VECTOR taegetPos, VECTOR scale, VECTOR rotation, float radius, float damage, float speed, bool isTracking)override;
	// 判定用データ
	ObjectData GetCollData()override;
};

