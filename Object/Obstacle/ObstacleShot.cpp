#include "ObstacleShot.h"
#include "Object/Shot/ShotBase.h"

ObstacleShot::ObstacleShot(VECTOR pos):
	m_shotCount(0)
{
	m_pos = pos;
}

ObstacleShot::~ObstacleShot()
{
}

void ObstacleShot::Init()
{
}

void ObstacleShot::End()
{
}

void ObstacleShot::Update()
{
	m_shotCount++;
	if (m_shotCount == 60)
	{
		m_pShot.push_back(std::make_shared<ShotBase>(m_pos));
		m_shotCount = 0;
	}

	for (auto& shot : m_pShot)
	{
		shot->Update();
	}
}

void ObstacleShot::Draw()
{
	DrawSphere3D(m_pos, 16, 16, 0x00ff00, 0x00ff00, true);

	for (auto& shot : m_pShot)
	{
		shot->Draw();
	}
}
