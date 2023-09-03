#include "EnemyNormal.h"
#include <cmath>
#include <cassert>

#include "../../Util/Pad.h"
#include "../../Util/Vec2.h"
#include <iostream>

#include "../../Util/Collision3D.h"

namespace
{
	// マップチップサイズ
	constexpr int kMapChipMaxZ = 13;// 行
	constexpr int kMapChipMaxX = 25;// 列
	// マップチップナンバー(敵の道)
	constexpr int kEnemyRoad = 2;
	constexpr int kEnemyStop = 4;
	// ブロック1つの大きさ
	const float kBlockSize = 50.0f;

	// 速度
	constexpr float kSpeed = 3.0f;
	// 距離
	constexpr float kRange = 50.0f;
}

EnemyNormal::EnemyNormal():
	m_hMouse(0),
	moveCount(0),
	m_dir(VGet(0, 0, 0)),
	m_targetPos(VGet(0, 0, 0)),
	m_screenPos(VGet(0, 0, 0)),
	m_hp(0),
	m_count(-1),
	forX(0),
	forZ(0),
	m_isHit(false),
	m_tempCountHit(0)
{
	m_hp = 20.0f;
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

	m_isNextMove = true;

	m_pColl = new Collision3D;

	m_hMouse = MV1LoadModel("Data/Model/Mouse.mv1");
	MV1SetPosition(m_hMouse, m_pos);
	MV1SetRotationXYZ(m_hMouse,VGet(0, 90.0f * DX_PI_F / 18.0f, 0));
}

void EnemyNormal::End()
{
}

void EnemyNormal::Update()
{
	MV1SetPosition(m_hMouse, m_pos);
	// どこに移動するかを考える
	ChangeNextPos(m_isNextMove);

	// 移動
	// 向きを算出
	m_dir = VSub(m_targetPos, m_pos);
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
	m_pos = VAdd(m_pos, velecity);

	// 距離を測る
	const float nowPosToNextPosX = static_cast<int>(sqrt(pow(m_pos.x - m_targetPos.x, 2) + pow(m_pos.x - m_targetPos.x, 2)));
	const float nowPosToNextPosZ = static_cast<int>(sqrt(pow(m_pos.z - m_targetPos.z, 2) + pow(m_pos.z - m_targetPos.z, 2)));

	// 移動までの距離が短いと
	if (nowPosToNextPosX < kRange &&
		nowPosToNextPosZ < kRange)
	{
		m_isNextMove = true;
	}

	// モデルの回転行列を計算して設定
	VECTOR dir2 = VSub(m_targetPos, m_pos);
	const float angle2 = atan2f(m_dir.x, m_dir.z) + -90.0f * DX_PI_F / 180.0f;
	MV1SetRotationXYZ(m_hMouse, VGet(0.0f, angle2, 0.0f));

	CheckColl();

	// 3D座標から2D座標に変換
	m_screenPos = ConvWorldPosToScreenPos(m_pos);

	CheckHp();
}

void EnemyNormal::ChangeNextPos(bool &isMoveing)
{
	// 配列が無かったら...
	assert(m_mapChip.size() != 0);

	m_pos.y = -kBlockSize + 50.0f;

	int tempZ = 0;
	int tempX = 0;

	bool isBreak = false;

	// どのマップチップの上にいるか
	bool isStop = false;
	bool isMove = false;

	int tempStopPosZ = 0;
	int tempStopPosX = 0;

	int tempMovePosZ = 0;
	int tempMovePosX = 0;
	moveCount++;
	if (isMoveing) {
		moveCount = 0;
		// 行
		for (int z = forZ - 1; z <= forZ + 1; z++) 
		{
			// 全てのfor分から脱出する
			if (isBreak)
			{
				isBreak = false;
				break;
			}
			// 配列の制御
			tempZ = z;
			if (z >= kMapChipMaxZ) { tempZ = kMapChipMaxZ - 1 ; }
			if (z <= 0) { tempZ = 0; }
			// 列
			for (int x = forX - 1; x <= forX + 1; x++) 
			{
				// 配列の制御
				tempX = x;

				if (x >= kMapChipMaxX) { tempX = kMapChipMaxX - 1; }
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
				// 飛ばす
				if (back)
				{
					back = false;
					continue;
				}

				// [現在の列 + 現在の列 * チップ最大列]
				if ((m_mapChip[tempX + tempZ * kMapChipMaxX] == kEnemyStop))
				{
					// 止まることを知らせる
					isStop = true;

					// マップチップでの場所を記録
					tempStopPosX = tempX;
					tempStopPosZ = tempZ;	

					// 止まる場所が決まったのでbraak
					isBreak = true;
					break;
				}
				// [現在の列 + 現在の列 * チップ最大列]
				if ((m_mapChip[tempX + tempZ * kMapChipMaxX] == kEnemyRoad))
				{
					// 動くことを知らせる
					isMove = true;

					// マップチップでの場所を記録
					tempMovePosX = tempX;
					tempMovePosZ = tempZ;	

					// 動く事のできる方向を確認
					moveDirX.push_back(tempX);
					moveDirZ.push_back(tempZ);				
				}
			}
		}

		if (isRandMove && isMove)
		{
			// 進む位置をランダムに決める
			tempMovePosX = moveDirX[GetRand(static_cast<int>(moveDirX.size()) - 1)];
			tempMovePosZ = moveDirZ[GetRand(static_cast<int>(moveDirZ.size()) - 1)];
			isRandMove = false;
		}
		else
		{
			// 要素を消す
			for (int i = 0; i < moveDirX.size(); i++)
			{
				moveDirX.pop_back();
				moveDirZ.pop_back();
			}
		}

		// 動きがある場合のみ
		if (isMove || isStop)
		{		
			// 立ち止まる場所
			if (isStop)
			{
				// 動かない
				isMove = false;
			}

			// 座標を記録
			// 次動く場所
			if (isMove)
			{
				forX = tempMovePosX;
				forZ = tempMovePosZ;
			}
			// 座標を記録
			// 立ち止まる場所
			if (isStop)
			{
				forX = tempStopPosX;
				forZ = tempStopPosZ;

				isRandMove = true;

				isStop = false;
			}

			// フラグのリセット
			isMove = false;
			isStop = false;

			// 通った事のある場所の記録
			m_recordX.push_back(forX);
			m_recordZ.push_back(forZ);
			// 位置を変更
			m_targetPos.x = (forX* kBlockSize);
			m_targetPos.z = (forZ* kBlockSize);
			isMoveing = false;

			// 要素を消す
			for (int i = 0; i < moveDirX.size(); i++)
			{
				moveDirX.pop_back();
				moveDirZ.pop_back();
			}
		}
	}
}


void EnemyNormal::Draw()
{
	// 敵を描画
	if (m_hp >= -20)
	{
	//	DrawSphere3D(m_pos, 16, 16, 0xff0000, 0xff0000, true);
		MV1DrawModel(m_hMouse);
	}

}

void EnemyNormal::DrawUI()
{
	if (m_hp >= -20)
	{
		DrawBox(
			m_screenPos.x - 20, m_screenPos.y - 30,
			m_screenPos.x + 20, m_screenPos.y - 30 + 10,
			0xffffff,
			true);
		DrawBox(
			m_screenPos.x - 20, m_screenPos.y - 30,
			m_screenPos.x + m_hp, m_screenPos.y - 30 + 10,
			0xaa0000,
			true);
	}
}

void EnemyNormal::CheckColl()
{
	// ショットの数分
	for (int i = 0; i < m_collData.size(); i++)
	{
		// 判定を見る
		if (m_pColl->UpdateCheck(m_pos, m_collData[i].pos,16.0f, m_collData[i].radius))
		{
			m_isHit = true;
		}
	}
}

void EnemyNormal::CheckHp()
{
	// 後で修正する
	// 体力の処理
	if (!m_isTempHit)
	{
		if (m_isHit)
		{
			m_isTempHit = true;
			m_hp -= 3;
		}
	}
	else
	{
		m_tempCountHit++;
		if (m_tempCountHit > 30)
		{
			m_tempCountHit = 0;
			m_isTempHit = false;
			m_isHit = false;
		}
	}

}
