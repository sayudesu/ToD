#include "EnemyNormal.h"
#include <cmath>

namespace
{
	// 速度
	constexpr float kSpeed = 3.0f;
	// 移動位置
	const VECTOR kNextPos1 = VGet(300, 0, 200);
	const VECTOR kNextPos2 = VGet(0, 0, 200);
}

EnemyNormal::EnemyNormal():
	m_dir(VGet(0,0,0)),
	m_targetPos(VGet(0,0,0))
{
}
EnemyNormal::~EnemyNormal()
{
}

void EnemyNormal::Init()
{
}

void EnemyNormal::End()
{
}

void EnemyNormal::Update()
{
	//**** 追従のAI ****//
	// 向きを算出
	m_dir = VSub(m_targetPos, m_pos);
	// プレイヤーからエネミーまでの角度を求める
	const float angle = atan2(m_dir.y, m_dir.x);
	// 現在敵が向いている方向のベクトルを生成する
	const MATRIX enemyRotMtx = MGetRotY(angle);
	const VECTOR dir = VTransform(VGet(0, 0, 0), enemyRotMtx);
	//printfDx("%2d\n",dir.z);
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

	NextPosChange();
}

void EnemyNormal::NextPosChange()
{
	static int nextNo = 0;
	if (nextNo == 0)
	{
		m_targetPos = kNextPos1;
		if (m_dir.x == 0.0f&&
			m_dir.y == 0.0f&&
			m_dir.z == 0.0f)
		{
			nextNo = 1;
		}
	}
	if (nextNo == 1)
	{
		m_targetPos = kNextPos2;
		if (m_pos.x == m_targetPos.x &&
			m_pos.y == m_targetPos.y &&
			m_pos.z == m_targetPos.z)
		{
			nextNo = 2;
		}
	}
}

void EnemyNormal::Draw()
{
	DrawSphere3D(m_pos, 16, 16, 0xff0000, 0xff0000, true);
}
