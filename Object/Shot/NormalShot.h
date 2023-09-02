#pragma once
#include "ShotBase.h"

class NormalShot : public ShotBase
{
public:
	NormalShot(int no,VECTOR pos);
	~NormalShot();

	void Init(VECTOR taegetPos, VECTOR scale, float speed);
	void End();
	void Update();
	void Draw();
private:
	VECTOR m_tagetPos;
	float m_speed;
};

