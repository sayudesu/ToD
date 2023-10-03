#include "MissileShot.h"
#include <cmath>

MissileShot::MissileShot(VECTOR pos, int originNo, int no):
	ShotBase(pos)
{
	// モデルハンドル初期化
	m_hShot = -1;
	// 判定データの初期数値
	m_originNo = originNo;
	// 固有の生成番号
	m_no = no;
	// オブジェクトを消したい際にfalse
	m_isEnabled = true;

	m_frameCount = 0;

	m_num = no;
}

MissileShot::~MissileShot()
{

}

void MissileShot::Init(int handle, int shotFrameCount, VECTOR taegetPos, VECTOR scale, VECTOR rotation, float radius, float damage, float speed, bool isTracking)
{
	// 3Dモデルのロード
	m_hShot = MV1DuplicateModel(handle);
	assert(m_hShot != -1);
	// 初期位置
	MV1SetPosition(m_hShot, m_pos);
	// ターゲット
	m_targetPos = taegetPos;
	// 大きさ
	MV1SetScale(m_hShot, scale);
	// 角度
	MV1SetRotationXYZ(m_hShot, VGet(rotation.x * DX_PI_F / 180.0f, rotation.y * DX_PI_F / 180.0f, rotation.z * DX_PI_F / 180.0f));
	// 半径
	m_radius = radius;
	// ダメージ
	m_damage = damage;
	// 速度
	m_speed = speed;
	// 追跡
//	m_isTracking = isTracking;
	m_isTrackingNow = isTracking;

	m_updateFunc = &ShotBase::FirstMove;

	m_fspeed = 15.0f;
}

void MissileShot::FirstMove()
{

	// プレイヤーから左右にショットを発射
	float angle = atan2(m_targetPos.z - m_pos.z, m_targetPos.x - m_pos.x);

	if (m_num % 2 == 0)
	{
		// 右方向
		dirX = 6.0f * cos(angle + DX_PI_F / 2); 
		dirZ = 6.0f * sin(angle + DX_PI_F / 2);
	}
	else
	{
		// 左方向
		dirX = 6.0f * cos(angle - DX_PI_F / 2);
		dirZ = 6.0f * sin(angle - DX_PI_F / 2);
	}

	m_frameCount++;
	if (m_frameCount == 1)
	{
		m_pos.x += dirX;
		m_pos.z += dirZ;
	}

	if (m_fspeed <= 1)
	{
		m_fspeed = 1.0f;
	}
	else
	{
		m_fspeed -= 1.0f;
		m_pos.x += dirX * 0.5f;
		m_pos.z += dirZ * 0.5f;
	}

	m_pos.y += m_fspeed;

	MV1SetPosition(m_hShot, m_pos);

	// モデルの回転を計算して設定
	VECTOR dir2 = VSub(m_targetPos, m_pos);
	const float angle2 = atan2f(dir2.x, dir2.z) + -90.0f * DX_PI_F / 180.0f;

	MV1SetRotationXYZ(m_hShot, VGet(0.0f, angle2, 0.0f));

	if (m_frameCount == 20)
	{
		m_updateFunc = &ShotBase::UpdateMain;
	}

}

// 移動の計算をしています
void MissileShot::VecCalculation(VECTOR tagetPos, float speed, bool isTracking)
{
	if (m_isTracking)
	{
		// 向きを算出
		m_dir = VSub(tagetPos, m_pos);
	}

	// プレイヤーからエネミーまでの角度を求める
	const float angle = atan2(m_dir.y, m_dir.x);

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
	if (true)
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

ObjectData MissileShot::GetCollData()
{
	m_collData.datage = m_damage;
	m_collData.pos = m_pos;
	m_collData.radius = m_radius;
	m_collData.isHit = m_isEnabled;

	return m_collData;
}
