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
	// 3Dモデルのロード
	m_hShot = MV1LoadModel("Data/Model/ShotCat.mv1");
	assert(m_hShot != -1);
	MV1SetScale(m_hShot, scale);
	MV1SetRotationXYZ(m_hShot,VGet(0, 180.0f * DX_PI_F / 180.0f, 0));
	m_tagetPos = taegetPos;
	m_speed = speed;
}

void NormalShot::End()
{
	// メモリ解放
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
	if (!IsGetEnd())
	{
		MV1DrawModel(m_hShot);
		DrawSphere3D(m_pos, 16.0f, 16.0f, 0xffff00, 0xffff00, true);
	}
}

CollData NormalShot::GetCollData()
{
	m_collData.datage = 30.0f;
	m_collData.pos = m_pos;
	m_collData.radius = 16.0f;
	return m_collData;
}
