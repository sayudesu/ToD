#include "Shot.h"

Shot::Shot(VECTOR pos):
	m_pos(pos),
	m_isScreenOut(false)
{
}

Shot::~Shot()
{
}

void Shot::Update()
{
	// ��ʊO�̏��������Ȃ�
	if (m_pos.x > 500.0f)
	{
		m_isScreenOut = true;
	}

	if (!m_isScreenOut)
	{
		m_pos.x += 30.0f;
	}
}

void Shot::Draw()
{
	if (!m_isScreenOut)
	{
		DrawSphere3D(m_pos, 8, 8, 0x00ff00, 0x00ff00, true);
	}
}
