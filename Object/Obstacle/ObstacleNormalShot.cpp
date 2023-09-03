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
	constexpr int kShootFrameMax = 30;
	// �I�u�W�F�N�g�J���[(��)
	constexpr int kObjColor1 = 0x00ff00;
	// �I�u�W�F�N�g�J���[(���F)
	constexpr int kObjColor2 = 0xffff00;

	// ��C���f���̃p�X�̈ʒu
	const char* kCannonBasePathName = "Data/Model/CannonBase.mv1";
	const char* kCannonPathName = "Data/Model/Cannon.mv1";

	//const VECTOR kConnonScale = VGet(0.1f, 0.1f, 0.1f);
	const VECTOR kConnonScale = VGet(1.0f, 1.0f, 1.0f);
}

ObstacleNormalShot::ObstacleNormalShot(VECTOR pos):
	m_hCannon(-1),
	m_hCannonBaes(-1),
	m_shotFirstDelayFrameCount(0),
	m_countShotNum(-1),
	m_shootFrameCount(0),
	m_objColor(kObjColor1)
{
	m_pos = pos;
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
	m_shootFrameCount++;
	// �V���b�g���o���X�s�[�g
	if (m_shootFrameCount > kShootFrameMax)
	{
		m_countShotNum++;
		m_pShot.push_back(std::make_shared<NormalShot>(m_countShotNum,m_pos));
		m_pShot[m_countShotNum]->Init(m_targetPos,VGet(1.0f, 1.0f, 1.0f), VGet(0.0f, 180.0f, 0.0f),10.0f);
		m_shootFrameCount = 0;
	}

	for (auto& shot : m_pShot)
	{
		shot->Update();
	}	

	// ���f���̉�]�s����v�Z���Đݒ�
	VECTOR dir2 = VSub(m_targetPos, m_pos);
	const float angle2 = atan2f(dir2.x, dir2.z) + -90.0f * DX_PI_F / 180.0f;
	MV1SetRotationXYZ(m_hCannon, VGet(0.0f, angle2, 0.0f));
}

void ObstacleNormalShot::Draw()
{
	// �I�u�W�F�N�g�`��
	DrawSphere3D(m_pos, 16, 16, m_objColor, m_objColor, true);

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
}

// ����f�[�^��n��
std::vector<CollData> ObstacleNormalShot::GetCollDatas()
{
	std::vector<CollData> collData;

	if (m_countShotNum != -1)
	{
		for(auto& shotData : m_pShot)
		{
			collData.push_back(shotData->GetCollData());
		}
	}

	return collData;
}

int ObstacleNormalShot::SetShotNum()
{
	return static_cast<int>(m_pShot.size());
}

void ObstacleNormalShot::SetTarGetPos(VECTOR pos)
{
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i]->SetTargetPos(pos);
	}
}
