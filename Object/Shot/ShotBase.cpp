#include "ShotBase.h"
#include <cmath>
#include "../../Util/SoundFunctions.h"

ShotBase::ShotBase(VECTOR pos):
	m_dir(VGet(0,0,0)),
	m_targetPos(VGet(0, 0, 0)),
	m_scale(VGet(0,0,0)),
	m_damage(0),
	m_isScreenOut(false),
	m_nowPosToNextPosX(0),
	m_nowPosToNextPosZ(0),
	m_speed(0.0f),
	m_radius(0.0f),
	m_isTracking(false),
	m_isTrackingNow(false)
{
	// 3D���f���n���h��
	m_hShot = -1;
	// �ʒu
	m_pos = pos;
	m_isTracking = true;
	m_originNo = 0;
	m_no = 0;
	m_isEnabled = false;
	m_collData = {};
//	SoundFunctions::Play(SoundFunctions::SoundIdShot);
	m_collData.datage = 0;
	m_collData.pos = pos;
	m_collData.radius = 0;
}

// �������������
void ShotBase::End()
{
	// ���������
	MV1DeleteModel(m_hShot);
}

// �X�V����
void ShotBase::Update()
{
	// �e�̈ړ�
	VecCalculation(m_targetPos, m_speed, m_isTrackingNow);
	MV1SetPosition(m_hShot, VGet(m_pos.x, m_pos.y + 30.0f, m_pos.z));

	// ���f���̉�]�s����v�Z���Đݒ�
	VECTOR dir2 = VSub(m_targetPos, m_pos);
	const float angle2 = atan2f(dir2.x, dir2.z) + -90.0f * DX_PI_F / 180.0f;
	MV1SetRotationXYZ(m_hShot, VGet(0.0f, angle2, 0.0f));
	// �T�C�Y
	MV1SetScale(m_hShot, VGet(3,3,3));

}

// �`��
void ShotBase::Draw()
{
	MV1DrawModel(m_hShot);
	//	DrawSphere3D(m_pos, kRadius, 4.0f, 0xffff00, 0xffff00, false);
}

// �I�u�W�F�N�g���������ǂ���
bool ShotBase::IsEnabled()const
{
	return m_isEnabled;
}

// �I�u�W�F�N�g���������ǂ������󂯎��
void ShotBase::SetEnabled(bool isEnabled)
{
	m_isEnabled = isEnabled;
}

// �ړ��̌v�Z�����Ă��܂�
void ShotBase::VecCalculation(VECTOR tagetPos,float speed,bool isTracking)
{	
	if (m_isTracking)
	{
		// �������Z�o
		m_dir = VSub(tagetPos, m_pos);
	}

	// �v���C���[����G�l�~�[�܂ł̊p�x�����߂�
	const float angle = atan2(m_dir.y, m_dir.x);

	// ���ݓG�������Ă�������̃x�N�g���𐶐�����
	const MATRIX enemyRotMtx = MGetRotY(angle);

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
	if (isTracking)
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
