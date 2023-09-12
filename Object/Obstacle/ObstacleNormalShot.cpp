#include "ObstacleNormalShot.h"
#include "../../Object/Shot/ShotBase.h"
#include "../../Object/Shot/NormalShot.h"
#include "../../Effeck/EffekseerDrawer.h"
#include "../../Util/SoundFunctions.h"
#include <math.h>

const bool ef = false;

namespace
{
	// �V���b�g�ŏ��ł��o���܂ł̃t���[���ރJ�E���g
	constexpr int kShotFirstFrameMax = 30;
	// �V���b�g�ĕ��o����܂ł̃t���[��
	constexpr int kShootFrameMax = 3;
	// �V���b�g�̑��x
	constexpr float kShootSpeed = 20.0f;

	// �I�u�W�F�N�g�J���[(��)
	constexpr int kObjColor1 = 0x00ff00;
	// �I�u�W�F�N�g�J���[(���F)
	constexpr int kObjColor2 = 0xffff00;

	// ��C���f���̃p�X�̈ʒu
	const char* kCannonBasePathName = "Data/Model/CannonBase.mv1";
	const char* kCannonPathName     = "Data/Model/Cannon.mv1";
	
	// ��C�̑傫��
	const VECTOR kConnonScale  = VGet(1.0f, 1.0f, 1.0f);
	// �V���b�g�̑傫��
	const VECTOR kShotScale    = VGet(1.0f, 1.0f, 1.0f);
	// �V���b�g�̏����p�x
	const VECTOR kShotRotation = VGet(0.0f, 180.0f, 0.0f);
}

ObstacleNormalShot::ObstacleNormalShot(VECTOR pos, int no):
	m_hCannon(-1),
	m_hCannonBaes(-1),
	m_shotFirstDelayFrameCount(0),
	m_countShotNum(-1),
	m_isShot(false),
	m_shootFrameCount(0),
	m_objColor(kObjColor1),
	m_isTargetChange(false),
	m_tempTargetNo(-1),
	m_myNo(no)
{
	m_pos = pos;

	m_isTargetChange = true;

	m_targetPos = VGet(1000, 0, 300);

	// �ݒu�p�֐��Ɉړ�
	m_updateFunc = &ObstacleNormalShot::UpdateSetting;

	if(ef)m_pEffect = new EffekseerDrawer;
}

ObstacleNormalShot::~ObstacleNormalShot()
{
}

void ObstacleNormalShot::Init()
{
	if (ef)m_pEffect->Init();
	// �ݒu��
	SoundFunctions::Play(SoundFunctions::SoundIdSet);

	// ��C���f���̃��[�h
	m_hCannonBaes = MV1LoadModel(kCannonBasePathName);
	m_hCannon = MV1LoadModel(kCannonPathName);
	// ��C���f���̈ʒu
	MV1SetPosition(m_hCannonBaes, VGet(m_pos.x, m_pos.y + 12.0f, m_pos.z));
	MV1SetPosition(m_hCannon, VGet(m_pos.x, m_pos.y + 20.0f, m_pos.z));
	// ��C���f���̃T�C�Y�ύX
	MV1SetScale(m_hCannonBaes, kConnonScale);
	MV1SetScale(m_hCannon, kConnonScale);
}

void ObstacleNormalShot::End()
{
	if (ef)
	{
		m_pEffect->End();
		delete m_pEffect;
		m_pEffect = nullptr;
	}

	// ���f���̃f���[�g
	MV1DeleteModel(m_hCannonBaes);
	MV1DeleteModel(m_hCannon);

	for (int i = 0; i < m_pShot.size(); i++)
	{
		delete m_pShot[i];
		m_pShot[i] = nullptr;
	}
}

void ObstacleNormalShot::Update()
{
	(this->*m_updateFunc)();
}

void ObstacleNormalShot::UpdateSetting()
{

	if (ef)
	{
		m_pEffect->Update();
		m_pEffect->GetPos(m_pos);
	}

	// �V���b�g�̑ł��o���܂ł̃t���[�����J�E���g����
	m_shotFirstDelayFrameCount++;
	if (m_shotFirstDelayFrameCount > kShotFirstFrameMax)
	{
		// �V���b�g�p�֐��Ɉړ�
		m_updateFunc = &ObstacleNormalShot::UpdateShot;
		// �I�u�W�F�N�g�̐F�ύX
		m_objColor = kObjColor2;
		// �J�E���g���Z�b�g
		m_shotFirstDelayFrameCount = 0;

		if (ef)
		{
			// �G�t�F�N�g�N���X�̃��������
			m_pEffect->End();
			delete m_pEffect;
			m_pEffect = nullptr;
		}
	}
}

void ObstacleNormalShot::UpdateShot()
{
	for (auto& shot : m_pShot)
	{
		shot->Update();
	}

	TargetPos();

	m_shootFrameCount++;
	// �V���b�g���o���X�s�[�g
	if (m_shootFrameCount > kShootFrameMax && (m_isShot))
	{
		m_countShotNum++;
		m_pShot.push_back(new NormalShot(m_pos, m_myNo, m_countShotNum));
		m_pShot.back()->Init(m_targetPos, kShotScale, kShotRotation, kShootSpeed, false);
		m_shootFrameCount = 0;
	}

	// ���f���̉�]�s����v�Z���Đݒ�
	VECTOR dir2 = VSub(m_targetPos, m_pos);
	const float angle2 = atan2f(dir2.x, dir2.z) + -90.0f * DX_PI_F / 180.0f;
	MV1SetRotationXYZ(m_hCannon, VGet(0.0f, angle2, 0.0f));


	// �폜����
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// �K���Ȕ͈͊O����
		if (m_pShot[i]->GetCollData().pos.x < -100.0f)
		{
			m_pShot[i]->SetEnabled(true);
		}
		if (m_pShot[i]->GetCollData().pos.x > 1300.0f)
		{
			m_pShot[i]->SetEnabled(true);
		}
		if (m_pShot[i]->GetCollData().pos.z < 0.0f)
		{
			m_pShot[i]->SetEnabled(true);
		}
		if (m_pShot[i]->GetCollData().pos.z > 700.0f)
		{
			m_pShot[i]->SetEnabled(true);
		}


		if (m_pShot[i]->IsEnabled())
		{
			m_pShot[i]->End();
			m_pShot.erase(m_pShot.begin() + i);
		}
	}
}

void ObstacleNormalShot::Draw()
{
	// �U���͈�
#if false
	DrawSphere3D(m_pos, 300, 4, m_objColor, m_objColor, false);
#endif

	for (auto& shot : m_pShot)
	{
		shot->Draw();
	}

	if (ef)
	{
		// �G�t�F�N�g�`��
		if (m_updateFunc == &ObstacleNormalShot::UpdateSetting)
		{
			m_pEffect->Draw();
		}
	}

	// 3D�`�惂�f��
	MV1DrawModel(m_hCannonBaes);
	MV1DrawModel(m_hCannon);

	DrawFormatString(500, 200, 0xffff00, "%d", m_pShot.size());
	
}

// ����f�[�^��n��
CollData ObstacleNormalShot::GetCollShotDatas(int shotNum)
{
	return m_pShot[shotNum]->GetCollData();
}

// �G�l�~�[�̔���p�f�[�^
void ObstacleNormalShot::SetCollEnemyDatas(std::vector<CollData> collEnemyData)
{
	m_collEnemyData = collEnemyData;
}

// �N��_����
void ObstacleNormalShot::TargetPos()
{
	// �����͌�ł��ꂢ�ɂ��܂��B
	// �G�̐���
	m_isShot = false;
	for (int i = 0; i < m_collEnemyData.size(); i++)
	{
		// �߂��G������
		const VECTOR toPlayer = VSub(m_pos, m_collEnemyData[i].pos);
		const float length = sqrtf((toPlayer.x * toPlayer.x) + (toPlayer.y * toPlayer.y) + (toPlayer.z * toPlayer.z));
		if (length < 300)
		{
			// �^�[�Q�b�g�w��
			m_targetPos = m_collEnemyData[i].pos;
			m_isShot = true;
		}
	}
}

// �V���b�g�̔��ː���n��
int ObstacleNormalShot::GetShotNum()
{
	return static_cast<int>(m_pShot.size());
}

// �^�[�Q�b�g�ʒu���󂯎��
void ObstacleNormalShot::SetTarGetPos(VECTOR pos)
{
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i]->SetTargetPos(pos);
	}
}

// �e�̔�����Ȃ������ǂ���
void ObstacleNormalShot::SetShotErase(int shotNum,bool erase)
{
	m_pShot[shotNum]->SetEnabled(erase);
}