#pragma once
#include <DxLib.h>

// ショットクラス
class Shot
{
public:
	Shot(VECTOR pos);
	virtual~Shot();

	void Update();
	void Draw();

	// ショットの位置
	VECTOR SetPos()const{ return m_pos; }

private:
	VECTOR m_pos;
	bool m_isScreenOut;
};

