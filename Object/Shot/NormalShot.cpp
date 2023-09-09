#include "NormalShot.h"
#include <cassert>

NormalShot::NormalShot(int no,VECTOR pos):
	ShotBase(pos)
{
	m_hShot = -1;
	m_targetPos = VGet(0, 0, 0);
	m_isScreenOut = false;
}

NormalShot::~NormalShot()
{

}

void NormalShot::Init(VECTOR taegetPos,VECTOR scale, VECTOR rotation, float speed, bool isTracking)
{
	// 3DÉÇÉfÉãÇÃÉçÅ[Éh
	m_hShot = MV1LoadModel("Data/Model/ShotCat.mv1");
	assert(m_hShot != -1);
	MV1SetScale(m_hShot, scale);
	MV1SetRotationXYZ(m_hShot, VGet(rotation.x * DX_PI_F / 180.0f, rotation.y * DX_PI_F / 180.0f, rotation.z * DX_PI_F / 180.0f));
	m_tagetPos = taegetPos;
	m_speed = speed;
}

void NormalShot::End()
{
	// ÉÅÉÇÉäâï˙
	MV1DeleteModel(m_hShot);
}

void NormalShot::Update()
{
	if (!IsGetEnd())
	{
		VecCalculation(m_tagetPos,m_speed, false);
		MV1SetPosition(m_hShot, m_pos);
	}
}

void NormalShot::Draw()
{
	if (!IsGetEnd())
	{
		MV1DrawModel(m_hShot);
		DrawSphere3D(m_pos, 16.0f, 4.0f, 0xffff00, 0xffff00, false);
	}
}

CollData NormalShot::GetCollData()
{

	m_collData.datage = 3.0f;
	m_collData.pos = m_pos;
	m_collData.radius = 16.0f;
	m_collData.isHit = true;

	return m_collData;
}
