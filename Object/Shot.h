#pragma once
#include <DxLib.h>

// �V���b�g�N���X
class Shot
{
public:
	Shot(VECTOR pos);
	virtual~Shot();

	void Update();
	void Draw();

	// �V���b�g�̈ʒu
	VECTOR SetPos()const{ return m_pos; }

private:
	VECTOR m_pos;
	bool m_isScreenOut;
};

