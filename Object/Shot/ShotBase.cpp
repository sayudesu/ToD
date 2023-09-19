#include "ShotBase.h"
#include <cmath>
#include "../../Util/SoundFunctions.h"

ShotBase::ShotBase(VECTOR pos):
	m_dir(VGet(0,0,0)),
	m_targetPos(VGet(0, 0, 0)),
	m_scale(VGet(0,0,0)),
	m_damage(0),
	m_isScreenOut(false),
	m_nowPosToNextPosX(0),
	m_nowPosToNextPosZ(0),
	m_speed(0.0f),
	m_radius(0.0f),
	m_isTracking(false),
	m_isTrackingNow(false)
{
	// 3Dモデルハンドル
	m_hShot = -1;
	// 位置
	m_pos = pos;
	m_isTracking = true;
	m_originNo = 0;
	m_no = 0;
	m_isEnabled = false;
	m_collData = {};
//	SoundFunctions::Play(SoundFunctions::SoundIdShot);
	m_collData.datage = 0;
	m_collData.pos = pos;
	m_collData.radius = 0;
}

// メモリ解放処理
void ShotBase::End()
{
	// メモリ解放
	MV1DeleteModel(m_hShot);
}

// 更新処理
void ShotBase::Update()
{
	// 弾の移動
	VecCalculation(m_targetPos, m_speed, m_isTrackingNow);
	MV1SetPosition(m_hShot, VGet(m_pos.x, m_pos.y + 30.0f, m_pos.z));

	// モデルの回転行列を計算して設定
	VECTOR dir2 = VSub(m_targetPos, m_pos);
	const float angle2 = atan2f(dir2.x, dir2.z) + -90.0f * DX_PI_F / 180.0f;
	MV1SetRotationXYZ(m_hShot, VGet(0.0f, angle2, 0.0f));
	// サイズ
	MV1SetScale(m_hShot, VGet(3,3,3));

}

// 描画
void ShotBase::Draw()
{
	MV1DrawModel(m_hShot);
	//	DrawSphere3D(m_pos, kRadius, 4.0f, 0xffff00, 0xffff00, false);
}

// オブジェクトを消すかどうか
bool ShotBase::IsEnabled()const
{
	return m_isEnabled;
}

// オブジェクトを消すかどうかを受け取る
void ShotBase::SetEnabled(bool isEnabled)
{
	m_isEnabled = isEnabled;
}

// 移動の計算をしています
void ShotBase::VecCalculation(VECTOR tagetPos,float speed,bool isTracking)
{	
	if (m_isTracking)
	{
		// 向きを算出
		m_dir = VSub(tagetPos, m_pos);
	}

	// プレイヤーからエネミーまでの角度を求める
	const float angle = atan2(m_dir.y, m_dir.x);

	// 現在敵が向いている方向のベクトルを生成する
	const MATRIX enemyRotMtx = MGetRotY(angle);

	// 斜めになったとき((1, 1, 0)など)にいったん長さ１に戻す(正規化)
	if (VSquareSize(m_dir) > 0)
	{
		m_dir = VNorm(m_dir);
	}

	// 速度を求める
	const VECTOR velecity = VScale(m_dir, speed);

	// 位置を変える
	m_pos = VAdd(m_pos, velecity);

	// 敵をそのまま追跡するかどうか
	if (isTracking)
	{
		m_isTracking = true;
	}
	else
	{
		m_isTracking = false;
	}

	// 距離を測る
	m_nowPosToNextPosX = static_cast<float>(sqrt(pow(m_pos.x - tagetPos.x, 2) + pow(m_pos.x - tagetPos.x, 2)));
	m_nowPosToNextPosZ = static_cast<float>(sqrt(pow(m_pos.z - tagetPos.z, 2) + pow(m_pos.z - tagetPos.z, 2)));
}
