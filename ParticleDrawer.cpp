#include "ParticleDrawer.h"
#include "Util/game.h"

namespace
{
	const char* kFileNameMeat = "Data/Image/UI_Meat.png";

	constexpr float kSpeed =10.0f;

	constexpr float kGravity = 0.2f;
}

ParticleDrawer::ParticleDrawer(VECTOR pos)
{
	m_posMain = pos;

	m_pFunc = &ParticleDrawer::First;

	m_speed = kSpeed;

	m_count = 0;

	m_isErase = false;
}

ParticleDrawer::~ParticleDrawer()
{
}

void ParticleDrawer::Init()
{
	// 3D座標から2D座標に変換
	m_posMain = ConvWorldPosToScreenPos(m_posMain);

	// 画像の読み込み
	m_hGraph = LoadGraph(kFileNameMeat);
	// パーティクルの初期位置
	m_pos = m_posMain;
		
	// 移動量
	m_vec.x = static_cast<float>(GetRand(6) - 3);
	m_vec.y = static_cast<float>(-GetRand(6) - 1);
}

void ParticleDrawer::End()
{
	DeleteGraph(m_hGraph);
}

void ParticleDrawer::Update()
{
	(this->*m_pFunc)();
}

void ParticleDrawer::Draw()
{
	DrawRotaGraph(m_pos.x, m_pos.y, 0.5f, DX_PI_F * 180.0f, m_hGraph, true);
}

bool ParticleDrawer::IsGetErase()
{
	return m_isErase;
}

void ParticleDrawer::First()
{
	// 重力を与える
	m_vec.y += kGravity;
	// ベクトルの加算
	m_pos = VAdd(m_pos, m_vec);

	m_count++;
	if (m_count > 40)
	{
		m_count = 0;
		m_pFunc = &ParticleDrawer::Jet;
	}
}

void ParticleDrawer::Jet()
{

	// 移動
	// 向きを算出
	VECTOR dir = VSub(VGet(1500, Game::kScreenHeight - 110, 0),VGet(m_pos.x, m_pos.y,0));
	// プレイヤーからエネミーまでの角度を求める
	const float angle = atan2(dir.y, dir.x);
	// 斜めになったとき((1, 1, 0)など)にいったん長さ１に戻す(正規化)
	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}
	// 速度を求める
	const VECTOR velecity = VScale(dir, kSpeed);
	// 位置を変える
	m_pos = VAdd(m_pos, velecity);		

	// 判定処理
	const VECTOR vec = VSub(VGet(m_pos.x, m_pos.y, 0), VGet(1500, Game::kScreenHeight - 110, 0));
	const float  del = VSize(vec);

	if (del < 5.0f + 5.0f)
	{
		m_isErase = true;
	}

	1 > 2 ? 3 : 4;

	// 重力を与える
	m_vec.y += kGravity;
}
