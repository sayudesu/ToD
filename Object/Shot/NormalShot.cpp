#include "NormalShot.h"
#include <cassert>

namespace
{
	// �V���b�g�̃��f���p�X
	//const char* kFileNameShot = "Data/Model/ShotCat.mv1";
	const char* kFileNameShot = "Data/Model/Arrow.mv1";
}

NormalShot::NormalShot(VECTOR pos, int originNo, int no):
	ShotBase(pos)
{
	// ���f���n���h��������
	m_hShot = -1;
	// ����f�[�^�̏������l
	m_originNo  = originNo;
	// �ŗL�̐����ԍ�
	m_no	    = no;
	// �I�u�W�F�N�g�����������ۂ�true
	m_isEnabled = false;
}

NormalShot::~NormalShot()
{

}

// ������
void NormalShot::Init(VECTOR taegetPos,VECTOR scale, VECTOR rotation, float radius, float damage,float speed, bool isTracking)
{
	// 3D���f���̃��[�h
	m_hShot = MV1LoadModel(kFileNameShot);
	assert(m_hShot != -1);
	// �傫��
	m_scale = scale;
	// �p�x
	MV1SetRotationXYZ(m_hShot, VGet(rotation.x * DX_PI_F / 180.0f, rotation.y * DX_PI_F / 180.0f, rotation.z * DX_PI_F / 180.0f));
	// �^�[�Q�b�g
	m_targetPos = taegetPos;
	// ���x
	m_speed = speed;
	// �����ʒu
	MV1SetPosition(m_hShot, m_pos);

	m_radius = radius;
	m_damage = damage;
	m_isTrackingNow = isTracking;
}
// ����p�f�[�^
ObjectData NormalShot::GetCollData()
{
	m_collData.datage   = m_damage;
	m_collData.pos      = m_pos;
	m_collData.radius   = m_radius;
	m_collData.isHit    = m_isEnabled;

	return m_collData;
}
