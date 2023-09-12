#include "NormalShot.h"
#include <cassert>

namespace
{
	// ショットの半径
	constexpr float kRadius = 16.0f;
	// ショットのモデルパス
	const char* kFileNameShot = "Data/Model/ShotCat.mv1";
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
	m_IsEnabled = false;
}

NormalShot::~NormalShot()
{

}

// 初期化
void NormalShot::Init(VECTOR taegetPos,VECTOR scale, VECTOR rotation, float speed, bool isTracking)
{
	// 3Dモデルのロード
	m_hShot = MV1LoadModel(kFileNameShot);
	assert(m_hShot != -1);
	// 大きさ
	MV1SetScale(m_hShot, scale);
	// 角度
	MV1SetRotationXYZ(m_hShot, VGet(rotation.x * DX_PI_F / 180.0f, rotation.y * DX_PI_F / 180.0f, rotation.z * DX_PI_F / 180.0f));
	// ターゲット
	m_targetPos = taegetPos;
	// 速度
	m_speed = speed;
	// 初期位置
	MV1SetPosition(m_hShot, m_pos);
}

// メモリ解放処理
void NormalShot::End()
{
	// メモリ解放
	MV1DeleteModel(m_hShot);
}

// 更新処理
void NormalShot::Update()
{
	// 弾の移動
	VecCalculation(m_targetPos,m_speed, false);
	MV1SetPosition(m_hShot, m_pos);
}

// 描画
void NormalShot::Draw()
{
	MV1DrawModel(m_hShot);
//	DrawSphere3D(m_pos, kRadius, 4.0f, 0xffff00, 0xffff00, false);
}

// オブジェクトを消すかどうか
bool NormalShot::IsEnabled()const
{
	return m_IsEnabled;
}

// オブジェクトを消すかどうかを受け取る
void NormalShot::SetEnabled(bool isEnabled)
{
	m_IsEnabled = isEnabled;
}

// 判定用データ
CollData NormalShot::GetCollData()
{
	m_collData.datage   = 3.0f;
	m_collData.pos      = m_pos;
	m_collData.radius   = kRadius;
	m_collData.isHit    = m_IsEnabled;

	return m_collData;
}
