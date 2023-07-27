#include "SceneTitle.h"
#include "Scene/SceneMain.h"
#include <DxLib.h>
#include "Util/Pad.h"
#include "Util/game.h"

namespace
{
	// �^�C�g���֘A
	// �p�X
	const char* kTitlePath = "Data/Image/VitalFortress.png";
	// �ʒu
	constexpr int kTitlePosX = Game::kScreenWidth / 2;
	constexpr int kTitlePosY = Game::kScreenHeight / 2 - 200;
	// �傫��
	constexpr int kTitleScale = 2;
	// �p�x
	constexpr int kAngle = DX_PI / 180;
}

SceneTitle::SceneTitle():
	m_hTitleLogo(-1)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	// �摜�t�@�C�����������Ƀ��[�h���܂��B
	m_hTitleLogo = LoadGraph(kTitlePath);
	// �摜�T�C�Y���擾
	GetGraphSize(m_hTitleLogo, &m_logoImageSizeX, &m_logoImageSizeY);
}

void SceneTitle::End()
{
	// ���������
	DeleteGraph(m_hTitleLogo);
}

SceneBase* SceneTitle::Update()
{
	if (Pad::isTrigger(PAD_INPUT_8))
	{
		m_isChangeScene = true;
		//m_isSliderOpen = true;
	}

	if (m_isChangeScene)
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneMain;
		}
	}


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

	SceneBase::DrawSliderDoor();
}
