#pragma once
#include <DxLib.h>
#include <array>

class BloodDrawer
{
public:
	BloodDrawer(VECTOR pos);
	virtual ~BloodDrawer();

	virtual void Init();
	virtual void End();
	virtual void Update();
	virtual void Draw();

	virtual bool IsGetErase();
private:
	void First();
	void Jet();
private:
	int m_hGraph;
	VECTOR m_pos;
	int m_posTarget;
	VECTOR m_posMain;
	VECTOR m_vec;

	int m_count;

	float m_speed;

	// メンバ関数ポインタ
	void(BloodDrawer::* m_pFunc)();

	bool m_isErase;

};

