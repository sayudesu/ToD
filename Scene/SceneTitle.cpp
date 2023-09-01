#include "SceneTitle.h"
#include "SceneMain.h"
#include <DxLib.h>
#include "../Util/Pad.h"
#include "../Util/game.h"
#include "../Util/SelectDrawer.h"
#include "../Menus/SettingDrawer.h"
#include "../Util/SoundFunctions.h"
#include "../Save/SaveDataFunctions.h"

namespace
{
	// �^�C�g���֘A
	// �p�X
	const char* kTitlePath = "Data/Image/VitalFortress2.png";
	// �ʒu
	constexpr int kTitlePosX = Game::kScreenWidth / 2;
	constexpr int kTitlePosY = Game::kScreenHeight / 2 - 150;
	// �傫��
	constexpr float kTitleScale = 0.8f;
	// �p�x
	constexpr int kAngle = DX_PI / 180;

	// �I��p�\������
	// 1
	constexpr int kFrame1PosX = Game::kScreenWidth / 2;
	constexpr int kFrame1PosY = Game::kScreenHeight / 2 + 250;
	constexpr int kString1PosX = -200;
	constexpr int kString1PosY = -25;
	const char* kStringGameStert = "�Q�[���X�^�[�g";
	constexpr int kString1Color = 0xffffff;
	constexpr int kString1Size = 52;
	// 2
	constexpr int kFrame2PosX = Game::kScreenWidth / 2;
	constexpr int kFrame2PosY = Game::kScreenHeight / 2 + 350;
	constexpr int kString2PosX = -65;
	constexpr int kString2PosY = -25;
	const char* kStringSetting = "�ݒ�";
	constexpr int kString2Color = 0xffffff;
	constexpr int kString2Size = 52;
	// 3
	constexpr int kFrame3PosX = Game::kScreenWidth / 2;
	constexpr int kFrame3PosY = Game::kScreenHeight / 2 + 450;
	constexpr int kString3PosX = -150;
	constexpr int kString3PosY = -25;
	const char* kStringCredit = "�N���W�b�g";
	constexpr int kString3Color = 0xffffff;
	constexpr int kString3Size = 52;
}

SceneTitle::SceneTitle():
	m_hTitleLogo(-1),
	m_isSlectSetting(false)
{
	// �I��p�N���X�̃C���X�^���X
	m_pSelect = new SelectDrawer;
	// �ݒ�p�N���X
	m_pGameSetting = new SettingDrawer;


	m_hCatAnim = LoadGraph("Data/Image/CatAnim.png");
}

SceneTitle::~SceneTitle()
{
	// ���������
	delete m_pSelect;
	m_pSelect = nullptr;
	delete m_pGameSetting;
	m_pGameSetting = nullptr;

	// BGM��~
	SoundFunctions::StopBgm(SoundFunctions::SoundIdTitle);
}

void SceneTitle::Init()
{
	// �摜�t�@�C�����������Ƀ��[�h���܂��B
	m_hTitleLogo = LoadGraph(kTitlePath);
	// �摜�T�C�Y���擾
	GetGraphSize(m_hTitleLogo, &m_logoImageSizeX, &m_logoImageSizeY);


	// BGM�Đ�
	SoundFunctions::StartBgm(SoundFunctions::SoundIdTitle);
	SoundFunctions::SetVolume(SoundFunctions::SoundIdTitle, SaveDataFunctions::GetSoundData().Bgm);

	// �I������ǉ�
	// 1
	m_pSelect->Add(
		kFrame1PosX,
		kFrame1PosY,
		kString1PosX,
		kString1PosY,
		kStringGameStert,
		kString1Color,
		kString1Size);
	// 2
	m_pSelect->Add(
		kFrame2PosX,
		kFrame2PosY,
		kString2PosX,
		kString2PosY,
		kStringSetting,
		kString2Color,
		kString2Size);
	// 3
	m_pSelect->Add(
		kFrame3PosX,
		kFrame3PosY,
		kString3PosX,
		kString3PosY,
		kStringCredit,
		kString3Color,
		kString3Size);

	m_pGameSetting->Init();
}

void SceneTitle::End()
{
	// ���������
	m_pSelect->End();
	m_pGameSetting->End();
	DeleteGraph(m_hTitleLogo);
}

SceneBase* SceneTitle::Update()
{
	// �����I�����Ă��Ȃ��ꍇ
	if (m_pSelect->GetSelectNo() == -1)
	{
		// �Z���N�g�֘A�X�V����
		m_pSelect->Update();
	}

	// �Q�[���X�^�[�g���������ꍇ
	if(m_pSelect->GetSelectNo() == 0)
	{
		m_isChangeScene = true;
		m_isSliderOpen = true;
	}

	if (m_pSelect->GetSelectNo() == 1)
	{
		m_isSlectSetting = true;
		// �ݒ菈��
		m_pGameSetting->Update();
		if (m_pGameSetting->GetSettingEnd())
		{
			m_isSlectSetting = false;
			// �Z���N�g�i���o�[�����Z�b�g����
			m_pSelect->ResetSelectNo();
		}
	}

	// �܂���������܂���
	if (m_pSelect->GetSelectNo() == 2)
	{
		// �Z���N�g�i���o�[�����Z�b�g����
		m_pSelect->ResetSelectNo();
	}

	if (m_isChangeScene)
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneMain;
		}
	}
	
	// BGM���~�܂����������x�Đ�
	SoundFunctions::ReStartBgm(SoundFunctions::SoundIdTitle);

	// �X���C�h���J����
	SceneBase::UpdateSlider(m_isSliderOpen);

	static bool isRev = false;
	static bool isMove = false;

	isMove = false;	

	
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		x -= 3;
		isMove = true;

	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		x += 3;
		isMove = true;
	}

	if (isMove)
	{
		m_count++;
		if (m_count == 3)
		{
			if (!isRev)
			{
				m_imagePosX += 321;
				if (m_imagePosX == 321 * 5)
				{
					isRev = true;
				}
			}
			if (isRev)
			{
				m_imagePosX -= 321;
				if (m_imagePosX <= 0)
				{
					isRev = false;
				}
			}

			m_count = 0;

		}
	}


	return this;
}

void SceneTitle::Draw()
{
	// �w�i�F
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaaaa, true);

	// �^�C�g�����S��`��
	DrawRotaGraph(kTitlePosX, kTitlePosY, kTitleScale, kAngle, m_hTitleLogo, true);

	// �Z���N�g�֘A�`��
	m_pSelect->Draw();

	DrawRectRotaGraph(
		Game::kScreenWidth/2,
		Game::kScreenHeight/2,//�v���C���[�̈ʒu
		m_imagePosX + 4, 0,// �摜�̍���
		322, 192,    // �摜�̉E��
		0.8,	   // �T�C�Y
		DX_PI_F * 180.0f,			   // ��]�p�x
		m_hCatAnim,		   // �n���h��
		true,		       // �摜����
		false      // �摜���]
	);

	if (m_isSlectSetting)
	{
		// �ݒ���
		m_pGameSetting->Draw();
	}

	SceneBase::DrawSliderDoor();
}
