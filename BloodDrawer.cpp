#include "BloodDrawer.h"
#include "Util/game.h"

namespace
{
	// 画像パス
	const char* kFileNameMeat = "Data/Image/UI_Meat.png";
	// 吸い込み速度
	constexpr float kSpeed =10.0f;
	// 重力
	constexpr float kGravity = 0.2f;
}

BloodDrawer::BloodDrawer(VECTOR pos)
{
	// パーティクルの初期位置
	m_pos = pos;

	m_pFunc = &BloodDrawer::First;

	m_speed = kSpeed;

	m_count = 0;

	m_isErase = false;
}

BloodDrawer::~BloodDrawer()
{
}

void BloodDrawer::Init()
{		
	// 移動量
	m_vec.x = static_cast<float>(GetRand(3) - 1);
	m_vec.y = static_cast<float>(-GetRand(2) - 1);
	m_vec.z = static_cast<float>(GetRand(3) - 1);
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
	m_vec.y += kGravity;
	// ベクトルの加算
	m_pos = VSub(m_pos, m_vec);

	m_count++;
	if (m_pos.y < -10.0f)
	{
		m_isErase = true;
	}
}

void BloodDrawer::Jet()
{

	//// 移動
	//// 向きを算出
	//VECTOR dir = VSub(VGet(1500, Game::kScreenHeight - 110, 0),VGet(m_pos.x, m_pos.y,0));
	//// プレイヤーからエネミーまでの角度を求める
	//const float angle = atan2(dir.y, dir.x);
	//// 斜めになったとき((1, 1, 0)など)にいったん長さ１に戻す(正規化)
	//if (VSquareSize(dir) > 0)
	//{
	//	dir = VNorm(dir);
	//}
	//// 速度を求める
	//const VECTOR velecity = VScale(dir, kSpeed);
	//// 位置を変える
	//m_pos = VAdd(m_pos, velecity);		

	//// 判定処理
	//const VECTOR vec = VSub(VGet(m_pos.x, m_pos.y, 0), VGet(1500, Game::kScreenHeight - 110, 0));
	//const float  del = VSize(vec);

	//if (del < 5.0f + 5.0f)
	//{
	//	m_isErase = true;
	//}

	// 重力を与える
	m_vec.y += kGravity;
}
