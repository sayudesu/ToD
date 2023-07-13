#include "EnemyNormal.h"

EnemyNormal::EnemyNormal()
{
}
EnemyNormal::~EnemyNormal()
{
}

void EnemyNormal::Init()
{
}

void EnemyNormal::End()
{
}

void EnemyNormal::Update()
{
	m_pos.x -= 3.0f;
}

void EnemyNormal::Draw()
{
	DrawSphere3D(m_pos, 16, 16, 0xff0000, 0xff0000, true);
}
