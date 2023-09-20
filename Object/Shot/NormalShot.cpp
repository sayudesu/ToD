#include "NormalShot.h"
#include <cassert>

NormalShot::NormalShot(VECTOR pos, int originNo, int no):
	ShotBase(pos)
{
	// モデルハンドル初期化
	m_hShot = -1;
	// 判定データの初期数値
	m_originNo  = originNo;
	// 固有の生成番号
	m_no	    = no;
	// オブジェクトを消したい際にtrue
	m_isEnabled = false;
}

NormalShot::~NormalShot()
{

}

// 初期化
void NormalShot::Init(int handle, int shotFrameCount,VECTOR taegetPos,VECTOR scale, VECTOR rotation, float radius, float damage,float speed, bool isTracking)
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
	// 初期追跡位置
	m_isTrackingNow = isTracking;
}
// 判定用データ
ObjectData NormalShot::GetCollData()
{
	m_collData.datage   = m_damage;
	m_collData.pos      = m_pos;
	m_collData.radius   = m_radius;
	m_collData.isHit    = m_isEnabled;

	return m_collData;
}
