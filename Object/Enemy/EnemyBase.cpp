#include "EnemyBase.h"
#include <cassert>

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
	// 半径
	constexpr float kRadius = 16.0f * 2.0f;
}

void EnemyBase::Init(VECTOR firstPos, int x, int z)
{
	// 初期位置
	m_pos = firstPos;
	m_chipPosX = x;
	m_chipPosZ = z;
	// 通った事のある場所の記録
	m_recordX.push_back(m_chipPosX);
	m_recordZ.push_back(m_chipPosZ);
	// 次の場所に行くかどうか
	m_isNextMove = true;
	// モデルの読み込み
	m_hModel = MV1LoadModel(m_filePathModel);
	// 初期位置
	MV1SetPosition(m_hModel, m_pos);
	// 初期角度
	MV1SetRotationXYZ(m_hModel, VGet(0, 90.0f * DX_PI_F / 18.0f, 0));
}

void EnemyBase::End()
{
	// メモリ解放
	MV1DeleteModel(m_hModel);
}

void EnemyBase::Update()
{
	if (!m_isEndPos)
	{
		MV1SetPosition(m_hModel, m_pos);
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
		MV1SetRotationXYZ(m_hModel, VGet(0.0f, angle2, 0.0f));
	}

	// 3D座標から2D座標に変換
	m_screenPos = ConvWorldPosToScreenPos(m_pos);
}

void EnemyBase::Draw()
{
	// 敵を描画
	DrawSphere3D(m_pos, kRadius, 6, 0xff0000, 0xff0000, false);
	MV1DrawModel(m_hModel);
}

void EnemyBase::DrawUI()
{
	const VECTOR hp = VGet(m_screenPos.x, m_screenPos.y, m_screenPos.z);

	DrawBox(
		hp.x - 20, hp.y - 30,
		hp.x + m_hp, hp.y - 30 + 10,
		0xffffff,
		true);
	DrawBox(
		m_screenPos.x - 20, m_screenPos.y - 30,
		m_screenPos.x + m_hp, m_screenPos.y - 30 + 10,
		0xaa0000,
		true);
}

void EnemyBase::SetHitDamage(int damage)
{
	// あとで修正
	if (m_damage != damage)
	{
		m_damage = damage;
		m_hp -= damage;
		m_damage = 0;
	}
}

bool EnemyBase::GetErase()
{
	if (m_hp < -20)
	{
		m_hp = -20;
		return true;
	}
	return false;
}

void EnemyBase::ChangeNextPos(bool& isMoveing)
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

	if (isMoveing) {
		// 行
		for (int z = m_chipPosZ - 1; z <= m_chipPosZ + 1; z++)
		{
			// 全てのfor分から脱出する
			if (isBreak)
			{
				isBreak = false;
				break;
			}
			// 配列の制御
			tempZ = z;
			if (z >= kMapChipMaxZ) { tempZ = kMapChipMaxZ - 1; }
			if (z <= 0) { tempZ = 0; }
			// 列
			for (int x = m_chipPosX - 1; x <= m_chipPosX + 1; x++)
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
				else if ((m_mapChip[tempX + tempZ * kMapChipMaxX] == kEnemyRoad))
				{
					// 動くことを知らせる
					isMove = true;

					// マップチップでの場所を記録
					tempMovePosX = tempX;
					tempMovePosZ = tempZ;

					// 動く事のできる方向を確認
					m_moveDirX.push_back(tempX);
					m_moveDirZ.push_back(tempZ);
				}
			}
		}

		if (m_isRandMove && isMove)
		{
			// 進む位置をランダムに決める
			tempMovePosX = m_moveDirX[GetRand(static_cast<int>(m_moveDirX.size()) - 1)];
			tempMovePosZ = m_moveDirZ[GetRand(static_cast<int>(m_moveDirZ.size()) - 1)];
			m_isRandMove = false;
		}
		else
		{
			// 要素を消す
			for (int i = 0; i < m_moveDirX.size(); i++)
			{
				m_moveDirX.pop_back();
				m_moveDirZ.pop_back();
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
				m_chipPosX = tempMovePosX;
				m_chipPosZ = tempMovePosZ;
			}
			// 座標を記録
			// 立ち止まる場所
			if (isStop)
			{
				m_chipPosX = tempStopPosX;
				m_chipPosZ = tempStopPosZ;

				m_isRandMove = true;

				isStop = false;
			}

			// フラグのリセット
			isMove = false;
			isStop = false;

			// 通った事のある場所の記録
			m_recordX.push_back(m_chipPosX);
			m_recordZ.push_back(m_chipPosZ);
			// 位置を変更
			m_targetPos.x = (m_chipPosX * kBlockSize);
			m_targetPos.z = (m_chipPosZ * kBlockSize);
			isMoveing = false;

			// 要素を消す
			for (int i = 0; i < m_moveDirX.size(); i++)
			{
				m_moveDirX.pop_back();
				m_moveDirZ.pop_back();
			}
		}
		else
		{
			m_isEndPos = true;
		}
	}
}