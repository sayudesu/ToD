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

void NormalShot::Init(VECTOR taegetPos,VECTOR scale, float speed)
{
	// 3DÉÇÉfÉãÇÃÉçÅ[Éh
	m_hShot = MV1LoadModel("Data/Model/ShotCat.mv1");
	assert(m_hShot != -1);
	MV1SetScale(m_hShot, scale);
	MV1SetRotationXYZ(m_hShot,VGet(0, 180.0f * DX_PI_F / 180.0f, 0));
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
	if (!m_isScreenOut)
	{
		VecCalculation(m_tagetPos,m_speed);
		MV1SetPosition(m_hShot, m_pos);
	}
}

void NormalShot::Draw()
{
	if (!m_isScreenOut)
	{
		MV1DrawModel(m_hShot);
	}
}
