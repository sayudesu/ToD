#include "NormalShot.h"
#include <cassert>

namespace
{
	// �V���b�g�̔��a
	constexpr float kRadius = 16.0f;
	// �V���b�g�̃��f���p�X
	const char* kFileNameShot = "Data/Model/ShotCat.mv1";
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
	m_IsEnabled = false;
}

NormalShot::~NormalShot()
{

}

// ������
void NormalShot::Init(VECTOR taegetPos,VECTOR scale, VECTOR rotation, float speed, bool isTracking)
{
	// 3D���f���̃��[�h
	m_hShot = MV1LoadModel(kFileNameShot);
	assert(m_hShot != -1);
	// �傫��
	MV1SetScale(m_hShot, scale);
	// �p�x
	MV1SetRotationXYZ(m_hShot, VGet(rotation.x * DX_PI_F / 180.0f, rotation.y * DX_PI_F / 180.0f, rotation.z * DX_PI_F / 180.0f));
	// �^�[�Q�b�g
	m_targetPos = taegetPos;
	// ���x
	m_speed = speed;
	// �����ʒu
	MV1SetPosition(m_hShot, m_pos);
}

// �������������
void NormalShot::End()
{
	// ���������
	MV1DeleteModel(m_hShot);
}

// �X�V����
void NormalShot::Update()
{
	// �e�̈ړ�
	VecCalculation(m_targetPos,m_speed, false);
	MV1SetPosition(m_hShot, m_pos);
}

// �`��
void NormalShot::Draw()
{
	MV1DrawModel(m_hShot);
//	DrawSphere3D(m_pos, kRadius, 4.0f, 0xffff00, 0xffff00, false);
}

// �I�u�W�F�N�g���������ǂ���
bool NormalShot::IsEnabled()const
{
	return m_IsEnabled;
}

// �I�u�W�F�N�g���������ǂ������󂯎��
void NormalShot::SetEnabled(bool isEnabled)
{
	m_IsEnabled = isEnabled;
}

// ����p�f�[�^
CollData NormalShot::GetCollData()
{
	m_collData.datage   = 3.0f;
	m_collData.pos      = m_pos;
	m_collData.radius   = kRadius;
	m_collData.isHit    = m_IsEnabled;

	return m_collData;
}
