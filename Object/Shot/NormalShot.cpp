#include "NormalShot.h"
#include <cassert>

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
void NormalShot::Init(int handle, int shotFrameCount,VECTOR taegetPos,VECTOR scale, VECTOR rotation, float radius, float damage,float speed, bool isTracking)
{
	// 3D���f���̃��[�h
	m_hShot = MV1DuplicateModel(handle);
	assert(m_hShot != -1);
	// �����ʒu
	MV1SetPosition(m_hShot, m_pos);

	// �^�[�Q�b�g
	m_targetPos = taegetPos;
	// �傫��
	MV1SetScale(m_hShot, scale);
	// �p�x
	MV1SetRotationXYZ(m_hShot, VGet(rotation.x * DX_PI_F / 180.0f, rotation.y * DX_PI_F / 180.0f, rotation.z * DX_PI_F / 180.0f));
	// ���a
	m_radius = radius;
	// �_���[�W
	m_damage = damage;
	// ���x
	m_speed = speed;
	// �����ǐՈʒu
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
