#pragma once
#include <DxLib.h>
#include <array>

class ParticleDrawer
{
public:
	ParticleDrawer(VECTOR pos);
	virtual ~ParticleDrawer();

	virtual void Init();
	virtual void End();
	virtual void Update();
	virtual void Draw();
private:
	void First();
	void Jet();
private:
	std::array<int, 10> m_hGraph;
	std::array<VECTOR, 10> m_pos;
	std::array<VECTOR, 10> m_posTarget;
	VECTOR m_posMain;
	VECTOR m_vec[10];

	int m_count;

	float m_speed;

	// メンバ関数ポインタ
	void(ParticleDrawer::* m_pFunc)();

};

