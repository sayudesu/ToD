#include "SceneTitle.h"
#include "SceneMain.h"
#include <DxLib.h>
#include "../Util/Pad.h"
#include "../Util/game.h"
#include "../Util/SelectDrawer.h"
#include <string>

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
}

SceneTitle::SceneTitle():
	m_hTitleLogo(-1)
{
	// �I��p�N���X�̃C���X�^���X
	m_pSelect = new SelectDrawer;
}

SceneTitle::~SceneTitle()
{
	// ���������
	delete m_pSelect;
	m_pSelect = nullptr;
}

void SceneTitle::Init()
{
	// �摜�t�@�C�����������Ƀ��[�h���܂��B
	m_hTitleLogo = LoadGraph(kTitlePath);
	// �摜�T�C�Y���擾
	GetGraphSize(m_hTitleLogo, &m_logoImageSizeX, &m_logoImageSizeY);

	// �I������ǉ�
	m_pSelect->Add(
		Game::kScreenWidth / 2,
		Game::kScreenHeight / 2 + 250,
		-200,
		-25,
		"�Q�[���X�^�[�g",
		0xffffff,
		52);

	m_pSelect->Add(
		Game::kScreenWidth / 2,
		Game::kScreenHeight / 2 + 350,
		-150,
		-25,
		"�N���W�b�g",
		0xffffff,
		52);
}

void SceneTitle::End()
{
	// ���������
	m_pSelect->End();
	DeleteGraph(m_hTitleLogo);
}

SceneBase* SceneTitle::Update()
{
	// �Q�[���X�^�[�g���������ꍇ
	if(m_pSelect->GetSelectNo() == 0)
	{
		m_isChangeScene = true;
		m_isSliderOpen = true;
	}

	if (m_isChangeScene)
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneMain;
		}
	}

	// �Z���N�g�֘A�X�V����
	m_pSelect->Update();

	// �X���C�h���J����
	SceneBase::UpdateSlider(m_isSliderOpen);

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

	SceneBase::DrawSliderDoor();
}
