#include "ObstacleNormalShot.h"
#include "../../Object/Shot/ShotBase.h"
#include "../../Effeck/EffekseerDrawer.h"

namespace
{
	// �V���b�g�ŏ��ł��o���܂ł̃t���[���ރJ�E���g
	constexpr int kShotFirstFrameMax = 60;
	// �V���b�g�ĕ��o����܂ł̃t���[��
	constexpr int kShootFrameMax = 10;
	// �I�u�W�F�N�g�J���[(��)
	constexpr int kObjColor1 = 0x00ff00;
	// �I�u�W�F�N�g�J���[(���F)
	constexpr int kObjColor2 = 0xffff00;
}

ObstacleNormalShot::ObstacleNormalShot(VECTOR pos):
	m_shotFirstDelayFrameCount(0),
	m_shootFrameCount(0),
	m_objColor(kObjColor1)
{
	m_pos = pos;
	// �ݒu�p�֐��Ɉړ�
	m_updateFunc = &ObstacleNormalShot::UpdateSetting;
	m_pEffect = new EffekseerDrawer;
}

ObstacleNormalShot::~ObstacleNormalShot()
{
}

void ObstacleNormalShot::Init()
{
	m_pEffect->Init();
}

void ObstacleNormalShot::End()
{

}

void ObstacleNormalShot::Update()
{
	(this->*m_updateFunc)();
}

void ObstacleNormalShot::UpdateSetting()
{
	m_pEffect->Update();
	m_pEffect->GetPos(m_pos);

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

		// �G�t�F�N�g�N���X�̃��������
		m_pEffect->End();
		delete m_pEffect;
		m_pEffect = nullptr;
	}
}

void ObstacleNormalShot::UpdateShot()
{
	m_shootFrameCount++;
	// �V���b�g���o���X�s�[�g
	if (m_shootFrameCount > kShootFrameMax)
	{
		m_pShot.push_back(std::make_shared<ShotBase>(m_pos));
		m_shootFrameCount = 0;
	}

	for (auto& shot : m_pShot)
	{
		shot->Update();
	}

	static int a = 0;
	a++;
	if (a > 60 * 5)
	{
		test = true;
	//	a = 0;
	}
	
}

void ObstacleNormalShot::Draw()
{
	// �I�u�W�F�N�g�`��
	DrawSphere3D(m_pos, 16, 16, m_objColor, m_objColor, true);

	for (auto& shot : m_pShot)
	{
		shot->Draw();
	}

	if (m_updateFunc == &ObstacleNormalShot::UpdateSetting)
	{
		m_pEffect->Draw();
	}
}

void ObstacleNormalShot::GetTarGetPos(VECTOR pos)
{
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i]->GetTargetPos(pos);
	}
}
