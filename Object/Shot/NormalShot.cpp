#include "NormalShot.h"
#include <cassert>

namespace
{
	// ショットのモデルパス
	//const char* kFileNameShot = "Data/Model/ShotCat.mv1";
	const char* kFileNameShot = "Data/Model/Arrow.mv1";
}

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
void NormalShot::Init(VECTOR taegetPos,VECTOR scale, VECTOR rotation, float radius, float damage,float speed, bool isTracking)
{
	// 3Dモデルのロード
	m_hShot = MV1LoadModel(kFileNameShot);
	assert(m_hShot != -1);
	// 大きさ
	m_scale = scale;
	// 角度
	MV1SetRotationXYZ(m_hShot, VGet(rotation.x * DX_PI_F / 180.0f, rotation.y * DX_PI_F / 180.0f, rotation.z * DX_PI_F / 180.0f));
	// ターゲット
	m_targetPos = taegetPos;
	// 速度
	m_speed = speed;
	// 初期位置
	MV1SetPosition(m_hShot, m_pos);

	m_radius = radius;
	m_damage = damage;
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
