#include "EnemyNormal.h"
#include <cmath>
#include <cassert>

#include "../../Util/Pad.h"

namespace
{
	// 速度
	constexpr float kSpeed = 3.0f;
}

EnemyNormal::EnemyNormal() :
	m_dir(VGet(0, 0, 0)),
	m_targetPos(VGet(0, 0, 0)),
	m_count(-1),
	forX(0),
	forZ(0)
{
}
EnemyNormal::~EnemyNormal()
{
}

void EnemyNormal::Init(VECTOR firstPos, int x, int z)
{
	// 初期位置
	m_pos = firstPos;
	forX = x;
	forZ = z;

	m_recordX.push_back(forX);
	m_recordZ.push_back(forZ);
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
	const int mapChipMaxZ = 13;// 行
	const int mapChipMaxX = 25;// 列
	// マップチップナンバー(敵の道)
	const int enemyRoad = 2;
	// ブロック1つの大きさ
	const float block = 50.0f;

	m_pos.y = -block + 50.0f;

	int tempZ = 0;
	int tempX = 0;
	
	int count = -1;
	if (Pad::isTrigger(PAD_INPUT_3)){
		// 行
		for (int z = forZ - 1; z <= forZ + 1; ++z){
			// 列
			for (int x = forX - 1; x <= forX + 1; ++x){
				// 配列の制御
				tempZ = z;
				if (z > mapChipMaxZ){tempZ = mapChipMaxZ;}
				if (z < 0){tempZ = 0;}
				// 配列の制御
				tempX = x;
				if (x > mapChipMaxX){tempX = mapChipMaxX;}
				if (x < 0){tempX = 0;}
				
				//count++;
				//m_checkPos[count].x = ((tempX)*block);
				//m_checkPos[count].z = ((tempZ)*block);
				//m_checkPos[count].y = 50.0f;

				// [現在の列 + 現在の列 * チップ最大列]
				if (m_mapChip[tempX + tempZ * mapChipMaxX] == enemyRoad)
				{				
					// 一度通った道はみない
					bool back = false;
					for (int i = 0; i < m_recordX.size(); i++)
					{
						// 見ようとしている場合はcontinu
						if (m_recordX[i] == x && m_recordZ[i] == z)
						{
							back = true;
						}
					}
					if (back)
					{
						continue;
					}
					// 座標を記録
					forX = x;
					forZ = z;

					// 1つまえの場所
					m_recordX.push_back(x);
					m_recordZ.push_back(z);
					// 敵の位置に代入
					m_pos.x = ((x) * block);
					m_pos.z = ((z) * block);
					// 座標制御
					if (x > mapChipMaxX)forX = mapChipMaxX;
					if (z > mapChipMaxZ)forZ = mapChipMaxZ;
					if (x < 0)forX = 0;
					if (z < 0)forZ = 0;
#if _DEBUG
					// デバッグ用
					//m_testPosX.push_back(m_pos.x);
					//m_testPosZ.push_back(m_pos.z);
					//printfDx("通過\n");
					printfDx(" x = %d  z = %d\n",x,z);
					printfDx("tx = %d tz = %d\n",tempX, tempZ);
					printfDx("fx = %d fz = %d\n", forX, forZ);
#endif
					break;
				}
			}
		}	
	}
}


void EnemyNormal::Draw()
{

	//for (int i = 0; i < m_testPosX.size(); i++)
	//{
	//	VECTOR pos = VGet(m_testPosX[i], 0.0f, m_testPosZ[i]);
	//	DrawSphere3D(pos, 16, 16, 0xff00ff, 0xff00ff, true);
	//}

	//for (int i = 0; i < 9; i++)
	//{
	//	DrawSphere3D(m_checkPos[i], 16, 16, 0xffffff, 0xffffff, true);
	//}


	DrawSphere3D(m_pos, 16, 16, 0xff0000, 0xff0000, true);
}
