#include "UserSettingDrawer.h"
#include <DxLib.h>
#include "../Util/game.h"
#include "../Util/Pad.h"
#include "../Util/SelectDrawer.h"
#include "../Util/SoundFunctions.h"
#include "../Save/SaveDataFunctions.h"
#include "../Util/LoadGraphFunction.h"

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
	const char* kStringGameStert = "�A�C�R����ύX";
	constexpr int kString1Color = 0xffffff;
	constexpr int kString1Size = 52;
	// 2
	constexpr int kFrame2PosX = Game::kScreenWidth / 2;
	constexpr int kFrame2PosY = Game::kScreenHeight / 2 + 100;
	constexpr int kString2PosX = -200;
	constexpr int kString2PosY = -25;
	const char* kStringGameStert2 = "�f�[�^�[��������...";
	constexpr int kString2Color = 0xffffff;
	constexpr int kString2Size = 52;
	// 3
	constexpr int kFrame3PosX = Game::kScreenWidth / 2;
	constexpr int kFrame3PosY = Game::kScreenHeight / 2 + 350;
	constexpr int kString3PosX = -200;
	constexpr int kString3PosY = -25;
	const char* kStringSettingEnd = "����";
	constexpr int kString3Color = 0xffffff;
	constexpr int kString3Size = 52;
}

UserSettingDrawer::UserSettingDrawer():
	m_isSetingEnd(false),
	m_slideY(-Game::kScreenHeight),
	m_iconSelect(SaveDataFunctions::GetIconData().Icon),
	m_iconSelectLeft(0),
	m_iconSelectRight(0)
{
	// �I��p�N���X�̃C���X�^���X
	m_pSelect = new SelectDrawer;

	// �ݒu�p�֐��Ɉړ�
	m_updateFunc = &PauseBase::UpdateStart;
}

UserSettingDrawer::~UserSettingDrawer()
{
	delete m_pSelect;
}

void UserSettingDrawer::Init()
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
		kStringSettingEnd,
		kString3Color,
		kString3Size
	);

	m_hIcon[0] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon0);
	m_hIcon[1] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon1);
	m_hIcon[2] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon2);
	m_hIcon[3] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon3);
	m_hIcon[4] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon4);
	m_hIcon[5] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon5);
	m_hIcon[6] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon6);
	m_hIcon[7] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon7);
}

void UserSettingDrawer::End()
{
}

void UserSettingDrawer::Update()
{
	(this->*m_updateFunc)();
}

void UserSettingDrawer::Draw()
{
	// �w�i�摜
	DrawExtendGraph(
		0,
		0 + m_slideY,
		Game::kScreenWidth - 0,
		Game::kScreenHeight + 100 + m_slideY,
		LoadGraphFunction::GraphData(LoadGraphFunction::Wood),
		true);

	DrawRotaGraph(
		kFrame1PosX,
		kFrame1PosY + 120 + m_slideY,
		0.6,
		DX_PI_F * 180.0f,
		m_hIcon[m_iconSelect],
		true);

	DrawRotaGraph(
		kFrame1PosX - 130,
		kFrame1PosY + 120 + m_slideY,
		0.4,
		DX_PI_F * 180.0f,
		m_hIcon[m_iconSelect + m_iconSelectLeft],
		true);

	DrawRotaGraph(
		kFrame1PosX + 130,
		kFrame1PosY + 120 + m_slideY,
		0.4,
		DX_PI_F * 180.0f,
		m_hIcon[m_iconSelect + m_iconSelectRight],
		true);

	m_pSelect->Draw();
}

/// <returns>�ݒ��ʂ��I������ǂ���</returns>
bool UserSettingDrawer::GetSettingEnd()
{
	return m_isSetingEnd;
}

GameData::Icon UserSettingDrawer::GetIcon()
{
	return m_iconData;
}


void UserSettingDrawer::UpdateStart()
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

void UserSettingDrawer::UpdateMain()
{
	m_pSelect->Update();

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		// �T�E���h�Đ�
		SoundFunctions::Play(SoundFunctions::SoundIdSelct);
		// End�p�֐��Ɉړ�
		m_updateFunc = &PauseBase::UpdateEnd;
	}

	if (m_pSelect->GetSelectNowNo() == 0)
	{
		if (Pad::isTrigger(PAD_INPUT_LEFT))
		{
			SoundFunctions::Play(SoundFunctions::SoundIdChange);
			if (m_iconSelect > 0)
			{
				m_iconSelect--;
			}
			else
			{
				m_iconSelect = 7;
			}
		}
		if (Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			SoundFunctions::Play(SoundFunctions::SoundIdChange);
			if (m_iconSelect < 7)
			{
				m_iconSelect++;
			}
			else
			{
				m_iconSelect = 0;
			}
		}
	}

	if (m_iconSelect == 0)
	{
		m_iconSelectLeft = 7;
	}
	else
	{
		m_iconSelectLeft = -1;
	}
	if (m_iconSelect == 7)
	{
		m_iconSelectRight = -7;
	}
	else
	{
		m_iconSelectRight = 1;
	}
	// �f�[�^�[�����Z�b�g
	if (m_pSelect->GetSelectNo() == 1)
	{
		SoundFunctions::Play(SoundFunctions::SoundIdDwon);
		GameData::Input data{};
		data.Icon_ = 0;
		data.Bgm_  = 255;
		data.SE_   = 255;
		SaveDataFunctions::Save(data);
		m_pSelect->ResetSelectNo();
	}


	// �����I������Ɛݒ��ʂ��I�������Ɉڍs���܂�
	if (m_pSelect->GetSelectNo() == 2)
	{
		// End�p�֐��Ɉړ�
		m_updateFunc = &PauseBase::UpdateEnd;
	}
	else
	{
		m_isSetingEnd = false;
	}
}

void UserSettingDrawer::UpdateEnd()
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
		printfDx("_Icon = %d\n", m_iconSelect);
		// �A�C�R���̃f�[�^��ۊ�
		m_iconData.Icon = m_iconSelect;
	}
}


void UserSettingDrawer::Reset()
{
	// Main�p�֐��Ɉړ�
	m_updateFunc = &PauseBase::UpdateStart;
	// �X���C�h�̒l��������
	m_slideY = -Game::kScreenHeight;
}


