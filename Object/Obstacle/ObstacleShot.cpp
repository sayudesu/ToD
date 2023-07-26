#include "ObstacleShot.h"
#include "Object/Shot/ShotBase.h"

namespace
{
	constexpr int kShootFrameMax = 4;
}

ObstacleShot::ObstacleShot(VECTOR pos):
	m_shootFrameCount(0)
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
	m_shootFrameCount++;
	if (m_shootFrameCount == kShootFrameMax)
	{
		m_pShot.push_back(std::make_shared<ShotBase>(m_pos));
		m_shootFrameCount = 0;
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

void ObstacleShot::GetTarGetPos(VECTOR pos)
{
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i]->GetTargetPos(pos);
	}
}
