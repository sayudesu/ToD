#include "ShotBase.h"
#include <cmath>

namespace
{
	constexpr float kSpeed = 10.0f;
}

ShotBase::ShotBase(VECTOR pos):
	m_pos(pos),
	m_targetPos(VGet(0,0,0)),
	m_isScreenOut(false)
{
}

ShotBase::~ShotBase()
{
}

void ShotBase::Update()
{
	if (!m_isScreenOut)
	{
		VecCalculation();
	}
}

void ShotBase::Draw()
{
	if (!m_isScreenOut)
	{
		DrawSphere3D(m_pos, 8, 8, 0x00ff00, 0x00ff00, true);
	}
}

// 移動の計算をしています
void ShotBase::VecCalculation()
{
	//**** 追従のAI ****//
	// 向きを算出
	m_dir = VSub(m_targetPos, m_pos);
	// プレイヤーからエネミーまでの角度を求める
	const float angle = atan2(m_dir.y, m_dir.x);
	// 現在敵が向いている方向のベクトルを生成する
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
	m_pos = VAdd(m_pos, velecity);
	//	m_pModel->SetPos(m_pos);
	//	m_pModel->SetRot(VGet(0, m_pPlayer->GetDir().y, 0));
}
