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

	// 通った事のある場所の記録
	m_recordX.push_back(forX);
	m_recordZ.push_back(forZ);

	m_testPosX.push_back(m_pos.x);
	m_testPosZ.push_back(m_pos.z);
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
	const int enemyStop = 4;
	// ブロック1つの大きさ
	const float block = 50.0f;

	m_pos.y = -block + 50.0f;

	int tempZ = 0;
	int tempX = 0;

	bool isBreak = false;


	bool isStop = false;
	bool isMove = false;
	bool isStopNow = false;
	bool isMoveNow = false;

	int tempStopPosZ = 0;
	int tempStopPosX = 0;

	int tempMovePosZ = 0;
	int tempMovePosX = 0;

	if (Pad::isTrigger(PAD_INPUT_3)) {
	//if (Pad::isPress(PAD_INPUT_3)) {
		// 行
		for (int z = forZ - 1; z <= forZ + 1; z++) {
			// 全てのfor分から脱出する
			if (isBreak)
			{
				isBreak = false;
				break;
			}
			// 配列の制御
			tempZ = z;
			if (z >= mapChipMaxZ) { tempZ = mapChipMaxZ - 1 ; }
			if (z <= 0) { tempZ = 0; }
			// 列
			for (int x = forX - 1; x <= forX + 1; x++) {
				// 配列の制御
				tempX = x;

				if (x >= mapChipMaxX) { tempX = mapChipMaxX - 1; }
				if (x <= 0) { tempX = 0; }

				// ここで移動処理を

				// 一度通った道はみない
				bool back = false;
				for (int i = 0; i < m_recordX.size(); i++)
				{
					// 見ようとしている場合はcontinu
					if (m_recordX[i] == tempX && m_recordZ[i] == tempZ)
					{
						back = true;
					}
				}
				if (back)
				{

					back = false;

					printfDx("continue\n");
					continue;
				}


				// [現在の列 + 現在の列 * チップ最大列]

				if (m_mapChip[tempX + tempZ * mapChipMaxX] == enemyStop)
				{
					printfDx("道を選びます。\n");
					isStop = true;

					tempStopPosX = tempX;
					tempStopPosZ = tempZ;

					isStopNow = true;

					isBreak = true;
					break;
				}
				// [現在の列 + 現在の列 * チップ最大列]
				if (m_mapChip[tempX + tempZ * mapChipMaxX] == enemyRoad)
				{
					printfDx("移動します。\n");
					isMove = true;

					tempMovePosX = tempX;
					tempMovePosZ = tempZ;

					isMoveNow = true;
					
					//isBreak = true;
					//break;
				}
			}
		}

		if (isMove || isStop)
		{

			isMove = false;
			isStop = false;

			if (isStopNow)
			{
				//
				isMoveNow = false;
			}

			// 座標を記録
			if (isMoveNow)
			{
				forX = tempMovePosX;
				forZ = tempMovePosZ;

				isMoveNow = false;
			}
			if (isStopNow)
			{
				forX = tempStopPosX;
				forZ = tempStopPosZ;

				isStopNow = false;
			}
			// 通った事のある場所の記録
			m_recordX.push_back(forX);
			m_recordZ.push_back(forZ);
			// 敵の位置を更新
			m_testPosX.push_back((forX)*block);
			m_testPosZ.push_back((forZ)*block);
			m_pos.x = ((forX)*block);
			m_pos.z = ((forZ)*block);
			// 全てのfor分から脱出する
			//isBreak = true;
			// break;
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

	DrawSphere3D(m_pos, 16, 16, 0xff0000, 0xff0000, true);
}
