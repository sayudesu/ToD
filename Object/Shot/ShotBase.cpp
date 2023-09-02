#include "ShotBase.h"
#include <cmath>
#include "../../Util/SoundFunctions.h"

namespace
{
	constexpr float kSpeed = 10.0f;
}

ShotBase::ShotBase(VECTOR pos):
	m_pos(pos)
{
//	SoundFunctions::Play(SoundFunctions::SoundIdShot);
}

bool ShotBase::IsGetEnd()
{
	if (m_nowPosToNextPosX < 30.0f &&
		m_nowPosToNextPosZ < 30.0f)
	{
		return true;
	}

	return false;
}

// 移動の計算をしています
void ShotBase::VecCalculation(VECTOR tagetPos,float speed)
{
	//**** 追従のAI ****//
	// 向きを算出
	m_dir = VSub(tagetPos, m_pos);
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
	const VECTOR velecity = VScale(m_dir, speed);
	// 位置を変える
	m_pos = VAdd(m_pos, velecity);

	// 距離を測る
	m_nowPosToNextPosX = sqrt(pow(m_pos.x - tagetPos.x, 2) + pow(m_pos.x - tagetPos.x, 2));
	m_nowPosToNextPosZ = sqrt(pow(m_pos.z - tagetPos.z, 2) + pow(m_pos.z - tagetPos.z, 2));
}
