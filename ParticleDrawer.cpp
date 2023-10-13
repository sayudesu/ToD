#include "ParticleDrawer.h"
#include "Util/game.h"

namespace
{
	// 画像パス
	const char* kFileNameMeat = "Data/Image/UI_Meat.png";
	// 画像サイズ
	constexpr float kMeatSize = 0.5f;
	// 画像角度
	constexpr float kMeatRota = DX_PI_F * 180.0f;
	// 吸い込み速度
	constexpr float kSpeed = 5.0f;
	// 画像の半径
	constexpr float kMeatRadius = 20.0f;
	// コスト画像位置の半径
	constexpr float kCostRadius = 20.0f;
	// コスト画像位置
	const VECTOR kCostPos = VGet(1500, 110, 0);
}

ParticleDrawer::ParticleDrawer(VECTOR pos)
{
	m_pos = pos;

	m_pFunc = &ParticleDrawer::FirstMove;

	m_speed = kSpeed;

	m_isErase = false;
}

ParticleDrawer::~ParticleDrawer()
{
}

void ParticleDrawer::Init(int no)
{
	// 3D座標から2D座標に変換
	// パーティクルの初期位置
	m_pos = ConvWorldPosToScreenPos(m_pos);

	// 画像の読み込み
	m_hGraph = LoadGraph(kFileNameMeat);

	// 移動量
	if (no % 2 == 0)
	{
		m_vec.x = (-GetRand(6));
	}
	else
	{
		m_vec.x = (GetRand(6));
	}

	m_vec.y = (-GetRand(24));

	m_vec.x += (m_vec.x * 3.0f);
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
	DrawRotaGraph(m_pos.x, m_pos.y, kMeatSize, kMeatRota, m_hGraph, true);
}

bool ParticleDrawer::IsGetErase()
{
	return m_isErase;
}

void ParticleDrawer::FirstMove()
{
	// ベクトルの加算
	m_pos = VAdd(m_pos, m_vec);

	m_pFunc = &ParticleDrawer::Suction;
}

void ParticleDrawer::Suction()
{
	// 移動
	// 向きを算出
	VECTOR dir = VSub(kCostPos,VGet(m_pos.x, m_pos.y,0));
	// プレイヤーからエネミーまでの角度を求める
	const float angle = atan2(dir.y, dir.x);
	// 斜めになったとき((1, 1, 0)など)にいったん長さ１に戻す(正規化)
	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}
	
	m_speed += 0.9f;

	// 速度を求める
	const VECTOR velecity = VScale(VGet(dir.x, dir.y, dir.z), m_speed);

	// 位置を変える
	m_pos = VAdd(m_pos, VGet(velecity.x, velecity.y, velecity.z));
	m_pos = VAdd(m_pos, m_vec);
	
	// 判定処理
	const VECTOR vec = VSub(VGet(m_pos.x, m_pos.y, 0), kCostPos);
	const float  del = VSize(vec);

	if (del < kMeatRadius + kCostRadius)
	{
		m_isErase = true;
	}
}
