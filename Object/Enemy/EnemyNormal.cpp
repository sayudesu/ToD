#include "EnemyNormal.h"
#include <cmath>
#include <cassert>

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
	m_targetPos(VGet(0,0,0)),
	m_count(-1)
{
}
EnemyNormal::~EnemyNormal()
{
}

void EnemyNormal::Init(VECTOR firstPos)
{
	// 初期位置
	m_pos = firstPos;
	
#if _DEBUG
	printfDx(
		"x = %2f,y = %2f,z = %2f\n",
		m_pos.x, m_pos.y, m_pos.z);
#endif
}

void EnemyNormal::End()
{
}

void EnemyNormal::Update()
{
	////**** 追従のAI ****//
	//// 向きを算出
	//m_dir = VSub(m_targetPos, m_pos);
	//// プレイヤーからエネミーまでの角度を求める
	//const float angle = atan2(m_dir.y, m_dir.x);
	//// 現在敵が向いている方向のベクトルを生成する
	//const MATRIX enemyRotMtx = MGetRotY(angle);
	//const VECTOR dir = VTransform(VGet(0, 0, 0), enemyRotMtx);
	////printfDx("%2d\n",dir.z);
	//// 斜めになったとき((1, 1, 0)など)にいったん長さ１に戻す(正規化)
	//if (VSquareSize(m_dir) > 0)
	//{
	//	m_dir = VNorm(m_dir);
	//}
	//// 速度を求める
	//const VECTOR velecity = VScale(m_dir, kSpeed);
	//// 位置を変える
	//m_pos = VAdd(m_pos, velecity);
	////	m_pModel->SetPos(m_pos);
	////	m_pModel->SetRot(VGet(0, m_pPlayer->GetDir().y, 0));

	NextPosChange();
}

void EnemyNormal::NextPosChange()
{
	// 配列が無かったら...
	assert(m_mapChip.size() != 0);

	// マップチップサイズ
	const int mapChipMaxZ = 26;
	const int mapChipMaxX = 13;
	// マップチップナンバー(敵の道)
	const int enemyRoad = 2;
	// ブロック1つの大きさ
	const float block = 50.0f;

	m_count = -1;

	for (int z = 0; z < mapChipMaxZ; ++z)
	{
		m_count++;
		
		for (int x = 0; x < mapChipMaxX; ++x)
		{
			m_count++;

			if (m_count > mapChipMaxZ &&
				(m_count + mapChipMaxZ) < m_mapChip.size())
			{
				printfDx("現在通っています\n");

				//if (m_mapChip[x + z * mapChipMaxZ] == enemyRoad)
				//{
				//	// 敵の位置に代入
				//	m_pos.x = x * block;
				//	m_pos.z = z * block;
				//}
			}

		}
	}
	printfDx("%d\n", m_count);
}

void EnemyNormal::Draw()
{
	DrawSphere3D(m_pos, 16, 16, 0xff0000, 0xff0000, true);

	DrawFormatString(1000, 100, 0xffffff, "敵の位置　x = %2f,y = %2f,z = %2f",
		m_pos.x, m_pos.y, m_pos.z);
}
