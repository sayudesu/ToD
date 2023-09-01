#include "SettingDrawer.h"
#include <DxLib.h>
#include "../Util/game.h"
#include "../Util/Pad.h"
#include "../Util/SelectDrawer.h"
#include "../Util/SoundFunctions.h"
#include "../Save/SaveDataFunctions.h"
#include "../Util/LoadGraphFunction.h"
#include "SoundSettingDrawer.h"
#include "ManualDrawer.h"
#include "UserSettingDrawer.h"

namespace
{
	// �L�̉摜�̑���
	constexpr int kVolCatSpeed = 20;
	// �X���C�h�̑���
	constexpr int kSlideSpeed = 50;

	// �I��p�\������
	// 1
	constexpr int kFrame1PosX = Game::kScreenWidth / 2;
	constexpr int kFrame1PosY = Game::kScreenHeight / 2 - 100;
	constexpr int kString1PosX = -200;
	constexpr int kString1PosY = -25;
	const char* kStringGameStert = "���[�U�[�ݒ�";
	constexpr int kString1Color = 0xffffff;
	constexpr int kString1Size = 52;
	// 2
	constexpr int kFrame2PosX = Game::kScreenWidth / 2;
	constexpr int kFrame2PosY = Game::kScreenHeight / 2;
	constexpr int kString2PosX = -200;
	constexpr int kString2PosY = -25;
	const char* kStringGameStert2 = "�T�E���h";
	constexpr int kString2Color = 0xffffff;
	constexpr int kString2Size = 52;
	// 3
	constexpr int kFrame3PosX = Game::kScreenWidth / 2;
	constexpr int kFrame3PosY = Game::kScreenHeight / 2 + 100;
	constexpr int kString3PosX = -200;
	constexpr int kString3PosY = -25;
	const char* kStringGameManual = "������@";
	constexpr int kString3Color = 0xffffff;
	constexpr int kString3Size = 52;
	// 4
	constexpr int kFrame4PosX = Game::kScreenWidth / 2;
	constexpr int kFrame4PosY = Game::kScreenHeight / 2 + 350;
	constexpr int kString4PosX = -200;
	constexpr int kString4PosY = -25;
	const char* kStringSettingEnd = "���違�ۑ�";
	constexpr int kString4Color = 0xffffff;
	constexpr int kString4Size = 52;
}

SettingDrawer::SettingDrawer():
	m_isSetingEnd(false),
	m_slideY(-Game::kScreenHeight),
	m_isSoundSetting(false),
	m_isManualDraw(false),
	m_isUserSetting(false)
{
	// �I��p�N���X�̃C���X�^���X
	m_pSelect = new SelectDrawer;
	m_pSoundSetting = new SoundSettingDrawer;
	m_pManual = new ManualDrawer;
	m_pUserSettig = new UserSettingDrawer;

	// �ݒu�p�֐��Ɉړ�
	m_updateFunc = &PauseBase::UpdateStart;
}

SettingDrawer::~SettingDrawer()
{
	delete m_pSelect;
	delete m_pSoundSetting;
	delete m_pManual;
	delete m_pUserSettig;
}

void SettingDrawer::Init()
{
	m_pSelect->Add(
		kFrame1PosX,
		kFrame1PosY,
		kString1PosX,
		kString1PosY,
		kStringGameStert,
		kString1Color,
		kString1Size
		);

	m_pSelect->Add(
		kFrame2PosX,
		kFrame2PosY,
		kString2PosX,
		kString2PosY,
		kStringGameStert2,
		kString2Color,
		kString2Size
	);

	m_pSelect->Add(
		kFrame3PosX,
		kFrame3PosY,
		kString3PosX,
		kString3PosY,
		kStringGameManual,
		kString3Color,
		kString3Size
	);

	m_pSelect->Add(
		kFrame4PosX,
		kFrame4PosY,
		kString4PosX,
		kString4PosY,
		kStringSettingEnd,
		kString4Color,
		kString4Size
	);

	m_pSoundSetting->Init();
	m_pManual->Init();
	m_pUserSettig->Init();
}

void SettingDrawer::End()
{
	m_pSoundSetting->End();
	m_pManual->End();
	m_pUserSettig->End();
}

void SettingDrawer::Update()
{
	(this->*m_updateFunc)();
}

void SettingDrawer::Draw()
{
	// �w�i�摜
	DrawExtendGraph(
		0,
		0 + m_slideY,
		Game::kScreenWidth - 0,
		Game::kScreenHeight + 100 + m_slideY,
		LoadGraphFunction::GraphData(LoadGraphFunction::Wood),
		true);

	m_pSelect->Draw();

	if (m_isSoundSetting)
	{
		m_pSoundSetting->Draw();
	}
	if (m_isManualDraw)
	{
		m_pManual->Draw();
	}
	if (m_isUserSetting)
	{
		m_pUserSettig->Draw();
	}
}

/// <returns>�ݒ��ʂ��I������ǂ���</returns>
bool SettingDrawer::GetSettingEnd()
{
	return m_isSetingEnd;
}


void SettingDrawer::UpdateStart()
{
	// �X���C�h���܂�
	m_slideY += kSlideSpeed;

	m_pSelect->UpdatePos(0,m_slideY);

	// �X���C�h���I���Ɗ֐����ړ�
	if (m_slideY > 0)
	{
		// �X���C�h�̒l��0�ɒ���
		m_slideY = 0;
		// Main�p�֐��Ɉړ�
		m_updateFunc = &PauseBase::UpdateMain;
	}
	m_isSetingEnd = false;	
}

void SettingDrawer::UpdateMain()
{

	// �����I�����Ă��Ȃ��ꍇ
	if (m_pSelect->GetSelectNo() == -1)
	{
		m_pSelect->Update();

		if (Pad::isTrigger(PAD_INPUT_2))
		{
			// �T�E���h�Đ�
			SoundFunctions::Play(SoundFunctions::SoundIdSelct);
			// End�p�֐��Ɉړ�
			m_updateFunc = &PauseBase::UpdateEnd;
		}

		// �����I������Ɛݒ��ʂ��I�������Ɉڍs���܂�
		if (m_pSelect->GetSelectNo() == 3)
		{
			// End�p�֐��Ɉړ�
			m_updateFunc = &PauseBase::UpdateEnd;
		}
		else
		{
			m_isSetingEnd = false;
		}
	}
	// ���[�U�[�ݒ��I�������ꍇ
	if (m_pSelect->GetSelectNo() == 0)
	{
		m_pUserSettig->Update();
		m_isUserSetting = true;

		// �T�E���h�̑I������߂��ꍇ
		if (m_pUserSettig->GetSettingEnd())
		{
			m_pSelect->ResetSelectNo();
			m_isUserSetting = false;
		}
	}
	// �T�E���h��I�������ꍇ
	if (m_pSelect->GetSelectNo() == 1)
	{
		m_pSoundSetting->Update();
		m_isSoundSetting = true;

		// �T�E���h�̑I������߂��ꍇ
		if (m_pSoundSetting->GetSettingEnd())
		{
			m_pSelect->ResetSelectNo();
			m_isSoundSetting = false;
		}
	}
	// ������@��I�������ꍇ
	if (m_pSelect->GetSelectNo() == 2)
	{
		m_pManual->Update();
		m_isManualDraw = true;

		// ������@�̑I������߂��ꍇ
		if (m_pManual->GetSettingEnd())
		{
			m_pSelect->ResetSelectNo();
			m_isManualDraw = false;
		}
	}
}

void SettingDrawer::UpdateEnd()
{
	m_slideY -= kSlideSpeed;

	m_pSelect->UpdatePos(0, m_slideY);

	if (m_slideY < -Game::kScreenHeight)
	{
		// �ϐ��̏�����
		Reset();

		// �G���h�������I����Ă��邩�ǂ���
		m_isSetingEnd = true;

		// �I�������Z�b�g���܂�
		m_pSelect->ResetSelectNo();

		// �f�[�^��ۑ����܂�
		GameData::Input save{};

		save.Icon_ = m_pUserSettig->GetIcon().Icon;
		save.Bgm_ = m_pSoundSetting->GetSoundVol().Bgm;
		save.SE_ = m_pSoundSetting->GetSoundVol().SE;

		SaveDataFunctions::Save(save);
	}

}

void SettingDrawer::Reset()
{
	// Main�p�֐��Ɉړ�
	m_updateFunc = &PauseBase::UpdateStart;
	// �X���C�h�̒l��������
	m_slideY = -Game::kScreenHeight;
}


