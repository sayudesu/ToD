#include "ShotBase.h"

ShotBase::ShotBase(VECTOR pos):
	m_pos(pos),
	m_isScreenOut(false)
{
}

ShotBase::~ShotBase()
{
}

void ShotBase::Update()
{
	// 画面外の処理をしない
	if (m_pos.x > 500.0f)
	{
	//	m_isScreenOut = true;
	}

	if (!m_isScreenOut)
	{
		//m_pos.x += 30.0f;
	}

	//const VECTOR enemy = VGet(1000.0f, 0.0f, 0.0f);

	//// エネミーをプレイヤーの方向に移動
	//VECTOR direction = VSub(m_pos, enemy);

	//const float distance = VSize(direction);

	//if (distance != 0.0f)
	//{
	//	direction = VScale(direction, 1.0f / distance);
	//}

	//m_pos = VAdd(enemy, VScale(direction, 1.0f));

}

void ShotBase::Draw()
{
	if (!m_isScreenOut)
	{
		DrawSphere3D(m_pos, 8, 8, 0x00ff00, 0x00ff00, true);
		DrawFormatString(100, 100, 0xffffff, "x = %f,y = %f,z = %f", m_pos.x, m_pos.y, m_pos.z);
	}

}
