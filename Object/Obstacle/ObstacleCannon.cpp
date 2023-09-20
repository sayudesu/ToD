#include "ObstacleCannon.h"
#include "../../Object/Shot/ShotBase.h"
#include "../../Util/SoundFunctions.h"

namespace
{
	// �V���b�g�ł��o���܂ł̃t���[��
	constexpr int kShotFrameCount = 60 * 2;
	// �V���b�g���f���̑傫��
	const VECTOR kShotScale = VGet(1.5, 1.5, 1.5);
	// �p�x
	const VECTOR kRotation = VGet(0, 0, 0);
	// ���a
	constexpr float kRadius = 16.0f;
	// �U����
	constexpr float kDamage = 200.0f;
	// ���x
	constexpr float kSpeed = 20.0f;
	// �ǐ�
	constexpr bool kIsTracking = false;
	// �t�@�C���p�X
	const char* kFilePath = "Data/Model/Cannon1.mv1";
	const char* kFilePathShot = "Data/Model/ShotCat.mv1";

	// ���f���̑傫��
	const VECTOR kScale = VGet(1, 1, 1);
}

ObstacleCannon::ObstacleCannon(VECTOR pos,int no):
	ObstacleBase::ObstacleBase(pos,no)
{
	m_pos = pos;
	m_myNo = no;
}

void ObstacleCannon::Init()
{
	// �V���b�g�f�[�^
	m_shotData.handle = MV1LoadModel(kFilePathShot);
	m_shotData.shotFrameCount = kShotFrameCount;
	m_shotData.targetPos      = VGet(1000, 0, 300);
	m_shotData.rotation       = kRotation;
	m_shotData.scale          = kShotScale;
	m_shotData.radius         = kRadius;
	m_shotData.damage         = kDamage;
	m_shotData.speed          = kSpeed;
	m_shotData.isTracking     = kIsTracking;
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
