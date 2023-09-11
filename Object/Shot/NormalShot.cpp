#include "NormalShot.h"
#include <cassert>

namespace
{
	// ショットの半径
	constexpr float kRadius = 16.0f * 2.0f;
}

NormalShot::NormalShot(VECTOR pos, int originNo, int no):
	ShotBase(pos)
{
	m_hShot = -1;
	m_targetPos = VGet(0, 0, 0);
	m_isScreenOut = false;

	// 判定データの初期数値
	m_originNo = originNo;
	m_no	   = no;
	m_IsEnabled = true;
}

NormalShot::~NormalShot()
{

}

void NormalShot::Init(VECTOR taegetPos,VECTOR scale, VECTOR rotation, float speed, bool isTracking)
{
	// 3Dモデルのロード
	m_hShot = MV1LoadModel("Data/Model/ShotCat.mv1");
	assert(m_hShot != -1);
	MV1SetScale(m_hShot, scale);
	MV1SetRotationXYZ(m_hShot, VGet(rotation.x * DX_PI_F / 180.0f, rotation.y * DX_PI_F / 180.0f, rotation.z * DX_PI_F / 180.0f));
	m_targetPos = taegetPos;
	m_speed = speed;
}

void NormalShot::End()
{
	// メモリ解放
	MV1DeleteModel(m_hShot);
}

void NormalShot::Update()
{
	if (!IsGetEnd())
	{
		VecCalculation(m_targetPos,m_speed, false);
		MV1SetPosition(m_hShot, m_pos);
	}
}

void NormalShot::Draw()
{
	if (!IsGetEnd())
	{
		MV1DrawModel(m_hShot);
		DrawSphere3D(m_pos, kRadius, 4.0f, 0xffff00, 0xffff00, false);
	}
}

bool NormalShot::IsEnabled()const
{
	return m_IsEnabled;
}

void NormalShot::SetEnabled(bool isEnabled)
{
	m_IsEnabled = isEnabled;
}

CollData NormalShot::GetCollData()
{

	m_collData.datage   = 3.0f;
	m_collData.pos      = m_pos;
	m_collData.radius   = kRadius;
	m_collData.isHit    = true;
	m_collData.originNo = m_originNo;
	m_collData.no       = m_no;

	return m_collData;
}
