#include "MissileShot.h"
#include <cmath>

MissileShot::MissileShot(VECTOR pos, int originNo, int no):
	ShotBase(pos)
{
	// ���f���n���h��������
	m_hShot = -1;
	// ����f�[�^�̏������l
	m_originNo = originNo;
	// �ŗL�̐����ԍ�
	m_no = no;
	// �I�u�W�F�N�g�����������ۂ�false
	m_isEnabled = true;

	m_frameCount = 0;

	m_num = no;
}

MissileShot::~MissileShot()
{

}

void MissileShot::Init(int handle, int shotFrameCount, VECTOR taegetPos, VECTOR scale, VECTOR rotation, float radius, float damage, float speed, bool isTracking)
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
	// �ǐ�
//	m_isTracking = isTracking;
	m_isTrackingNow = isTracking;

	m_updateFunc = &ShotBase::FirstMove;

	m_fspeed = 15.0f;
}

void MissileShot::FirstMove()
{

	// �v���C���[���獶�E�ɃV���b�g�𔭎�
	float angle = atan2(m_targetPos.z - m_pos.z, m_targetPos.x - m_pos.x);

	if (m_num % 2 == 0)
	{
		// �E����
		dirX = 6.0f * cos(angle + DX_PI_F / 2); 
		dirZ = 6.0f * sin(angle + DX_PI_F / 2);
	}
	else
	{
		// ������
		dirX = 6.0f * cos(angle - DX_PI_F / 2);
		dirZ = 6.0f * sin(angle - DX_PI_F / 2);
	}

	m_frameCount++;
	if (m_frameCount == 1)
	{
		m_pos.x += dirX;
		m_pos.z += dirZ;
	}

	if (m_fspeed <= 1)
	{
		m_fspeed = 1.0f;
	}
	else
	{
		m_fspeed -= 1.0f;
		m_pos.x += dirX * 0.5f;
		m_pos.z += dirZ * 0.5f;
	}

	m_pos.y += m_fspeed;

	MV1SetPosition(m_hShot, m_pos);

	// ���f���̉�]���v�Z���Đݒ�
	VECTOR dir2 = VSub(m_targetPos, m_pos);
	const float angle2 = atan2f(dir2.x, dir2.z) + -90.0f * DX_PI_F / 180.0f;

	MV1SetRotationXYZ(m_hShot, VGet(0.0f, angle2, 0.0f));

	if (m_frameCount == 20)
	{
		m_updateFunc = &ShotBase::UpdateMain;
	}

}

// �ړ��̌v�Z�����Ă��܂�
void MissileShot::VecCalculation(VECTOR tagetPos, float speed, bool isTracking)
{
	if (m_isTracking)
	{
		// �������Z�o
		m_dir = VSub(tagetPos, m_pos);
	}

	// �v���C���[����G�l�~�[�܂ł̊p�x�����߂�
	const float angle = atan2(m_dir.y, m_dir.x);

	// �΂߂ɂȂ����Ƃ�((1, 1, 0)�Ȃ�)�ɂ������񒷂��P�ɖ߂�(���K��)
	if (VSquareSize(m_dir) > 0)
	{
		m_dir = VNorm(m_dir);
	}

	// ���x�����߂�
	const VECTOR velecity = VScale(m_dir, speed);

	// �ʒu��ς���
	m_pos = VAdd(m_pos, velecity);

	// �G�����̂܂ܒǐՂ��邩�ǂ���
	if (true)
	{
		m_isTracking = true;
	}
	else
	{
		m_isTracking = false;
	}

	// �����𑪂�
	m_nowPosToNextPosX = static_cast<float>(sqrt(pow(m_pos.x - tagetPos.x, 2) + pow(m_pos.x - tagetPos.x, 2)));
	m_nowPosToNextPosZ = static_cast<float>(sqrt(pow(m_pos.z - tagetPos.z, 2) + pow(m_pos.z - tagetPos.z, 2)));
}

ObjectData MissileShot::GetCollData()
{
	m_collData.datage = m_damage;
	m_collData.pos = m_pos;
	m_collData.radius = m_radius;
	m_collData.isHit = m_isEnabled;

	return m_collData;
}
