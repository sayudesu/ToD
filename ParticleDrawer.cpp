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
}

ParticleDrawer::~ParticleDrawer()
{
}

void ParticleDrawer::Init()
{
	// 3D座標から2D座標に変換
	m_posMain = ConvWorldPosToScreenPos(m_posMain);
	for (int i = 0; i < m_hGraph.size(); i++)
	{
		// 画像の読み込み
		m_hGraph[i] = LoadGraph(kFileNameMeat);
		// パーティクルの初期位置
		m_pos[i] = m_posMain;
		
		// 移動量
		m_vec[i].x = static_cast<float>(GetRand(6) - 3);
		m_vec[i].y = static_cast<float>(GetRand(2) - 1);
	}
}

void ParticleDrawer::End()
{
	for (int i = 0; i < m_hGraph.size(); i++)
	{
		DeleteGraph(m_hGraph[i]);
	}
}

void ParticleDrawer::Update()
{
	(this->*m_pFunc)();
}

void ParticleDrawer::Draw()
{
	for (int i = 0; i < m_hGraph.size(); i++)
	{
		DrawRotaGraph(m_pos[i].x, m_pos[i].y, 0.5f, DX_PI_F * 180.0f, m_hGraph[i], true);
	}
}

void ParticleDrawer::First()
{
	for (int i = 0; i < m_hGraph.size(); i++)
	{
		// 重力を与える
		m_vec[i].y += kGravity;
		// ベクトルの加算
		m_pos[i] = VAdd(m_pos[i], m_vec[i]);
	}

	m_count++;
	if (m_count > 30)
	{
		m_count = 0;
		m_pFunc = &ParticleDrawer::Jet;
	}
}

void ParticleDrawer::Jet()
{
	for (int i = 0; i < m_hGraph.size(); i++)
	{
		// 移動
		// 向きを算出
		VECTOR m_dir = VSub(VGet(Game::kScreenWidth, Game::kScreenHeight, 0), m_pos[i]);
		// プレイヤーからエネミーまでの角度を求める
		const float angle = atan2(m_dir.y, m_dir.x);
		// 現在向いている方向のベクトルを生成する
		const MATRIX enemyRotMtx = MGetRotY(angle);
		const VECTOR dir = VTransform(VGet(0, 0, 0), enemyRotMtx);
		// 斜めになったとき((1, 1, 0)など)にいったん長さ１に戻す(正規化)
		if (VSquareSize(m_dir) > 0)
		{
			m_dir = VNorm(m_dir);
		}
		// 速度を求める
		const VECTOR velecity = VScale(m_dir, kSpeed);
		// 位置を変える
		m_pos[i] = VAdd(m_pos[i], velecity);

		//// 距離を測る
		//const float nowPosToNextPosX = static_cast<int>(sqrt(pow(m_pos[i].x - Game::kScreenWidth, 2) + pow(m_pos[i].x - Game::kScreenWidth, 2)));
		//const float nowPosToNextPosZ = static_cast<int>(sqrt(pow(m_pos[i].y - Game::kScreenHeight, 2) + pow(m_pos[i].y - Game::kScreenHeight, 2)));

		//// 移動までの距離が短いと
		//if (nowPosToNextPosX < 3.0f &&
		//	nowPosToNextPosZ < 3.0f)
		//{
		//	m_pFunc = &ParticleDrawer::Jet;
		//}
	}
}
