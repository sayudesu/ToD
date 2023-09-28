#pragma once
#include <DxLib.h>
#include <array>

class BloodDrawer
{
public:
	BloodDrawer(VECTOR pos);
	virtual ~BloodDrawer();

	virtual void Init(int no);
	virtual void End();
	virtual void Update();
	virtual void Draw();

	virtual bool IsGetErase();
private:
	void First();
private:
	VECTOR m_pos;
	VECTOR m_vec;
	bool m_isErase;
	// メンバ関数ポインタ
	void(BloodDrawer::* m_pFunc)();
};

