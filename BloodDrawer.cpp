#include "BloodDrawer.h"
#include "Util/game.h"

namespace
{
	// 重力
	constexpr float kGravity = 0.4f;
}

BloodDrawer::BloodDrawer(VECTOR pos)
{
	// パーティクルの初期位置
	m_pos = pos;
	m_vec = VGet(0, 0, 0);
	m_pFunc = &BloodDrawer::First;

	m_isErase = false;
}

BloodDrawer::~BloodDrawer()
{
}

void BloodDrawer::Init(int no)
{		
	// 移動量
	if (no % 2 == 0)
	{
		m_vec.x = (-GetRand(6));
		m_vec.z = (-GetRand(6));
	}
	else
	{
		m_vec.x = (GetRand(6));
		m_vec.z = (GetRand(6));
	}
	m_vec.y = static_cast<float>(GetRand(12) + 1);
}

void BloodDrawer::End()
{
}

void BloodDrawer::Update()
{
	(this->*m_pFunc)();
}

void BloodDrawer::Draw()
{
	// ３Ｄ空間上に球を描画する
	DrawSphere3D(m_pos, 2, 4, 0xff0000, 0xff0000, true);

}

bool BloodDrawer::IsGetErase()
{
	return m_isErase;
}

void BloodDrawer::First()
{
	// 重力を与える
	m_vec.y -= kGravity;
	// ベクトルの加算
	m_pos = VAdd(m_pos, m_vec);

	if (m_pos.y < -10.0f)
	{
		m_isErase = true;
	}
}
