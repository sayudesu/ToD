#include "ShotBase.h"
#include <cmath>

namespace
{
	constexpr float kSpeed = 10.0f;
}

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

	VECTOR m_dir = VGet(0, 0, 0);
	VECTOR Player = VGet(300, 0, 0);
	//**** プレイヤー追従のAI ****//
	// 向きを算出
	m_dir = VSub(Player, m_pos);

	// プレイヤーからエネミーまでの角度を求める
	float angle = atan2(m_dir.y, m_dir.x);

	// 現在敵が向いている方向のベクトルを生成する
	MATRIX enemyRotMtx = MGetRotY(angle);
	VECTOR dir = VTransform(VGet(0, 0, 0), enemyRotMtx);

	// 斜めになったとき((1, 1, 0)など)にいったん長さ１に戻す(正規化)
	if (VSquareSize(m_dir) > 0)
	{
		m_dir = VNorm(m_dir);
	}

	// 速度を求める
	VECTOR velecity = VScale(m_dir, kSpeed);
	// 
	m_pos = VAdd(m_pos, velecity);

	//	m_pModel->SetPos(m_pos);
	//	m_pModel->SetRot(VGet(0, m_pPlayer->GetDir().y, 0));

}

void ShotBase::Draw()
{
	if (!m_isScreenOut)
	{
		DrawSphere3D(m_pos, 8, 8, 0x00ff00, 0x00ff00, true);
		DrawFormatString(100, 100, 0xffffff, "x = %f,y = %f,z = %f", m_pos.x, m_pos.y, m_pos.z);
	}

}
