#include "ObstacleNormalShot.h"
#include "../../Object/Shot/ShotBase.h"
#include "../../Util/SoundFunctions.h"

namespace
{
	// �V���b�g�ł��o���܂ł̃t���[��
	constexpr int kShotFrameCount = 60 * 2;
	// ���f���̑傫��
	const VECTOR kScale = VGet(1, 1, 1);
	// �p�x
	const VECTOR kRotation = VGet(0, 0, 0);
	// ���a
	constexpr float kRadius = 16.0f;
	// �U����
	constexpr float kDamage = 150.0f;
	// ���x
	constexpr float kSpeed = 20.0f;
	// �ǐ�
	constexpr bool kIsTracking = false;
	// �t�@�C���p�X
	const char* kFilePath = "Data/Model/Cannon1.mv1";
}

ObstacleNormalShot::ObstacleNormalShot(VECTOR pos,int no):
	ObstacleBase::ObstacleBase(pos,no)
{
	m_pos = pos;
	m_myNo = no;
}

void ObstacleNormalShot::Init()
{
	// �V���b�g�f�[�^
	m_shotData.shotFrameCount = kShotFrameCount;
	m_shotData.targetPos = VGet(1000, 0, 300);
	m_shotData.rotation = kRotation;
	m_shotData.scale = kScale;
	m_shotData.radius = kRadius;
	m_shotData.damage = kDamage;
	m_shotData.speed = kSpeed;
	m_shotData.isTracking = kIsTracking;
	// �ݒu��
	SoundFunctions::Play(SoundFunctions::SoundIdSet);
	// ��C���f���̃��[�h
	m_handle = MV1LoadModel(kFilePath);
	// ��C���f���̈ʒu
	MV1SetPosition(m_handle, m_pos);
	// ��C���f���̃T�C�Y�ύX
	MV1SetScale(m_handle, kScale);
	// �ݒu�p�֐��Ɉړ�
	m_updateFunc = &ObstacleBase::UpdateSetting;
}
