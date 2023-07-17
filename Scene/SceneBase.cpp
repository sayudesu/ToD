#include "SceneBase.h"
#include <DxLib.h>
#include "game.h"

namespace
{
	// �X���C�h�X�s�[�h
	constexpr int kSliderSpeed = 20;
}

SceneBase::SceneBase()
{
	// �X���C�_�[�֘A
	m_hDoor = LoadGraph("Data/Image/DoorH.png");
	m_sliderPos = 0;
	m_pos = { 0.0f,0.0f };
	m_isSliderOpen = false;
	m_isChangeScene = false;
}
void SceneBase::UpdateSlider(bool& open)
{
	// �X���C�h���J����
	if (!open)
	{
		if (SceneBase::UpdateSliderOpen())
		{
			open = true;
		}
	}
}

// �X���C�h���J����Ƃ�
bool SceneBase::UpdateSliderOpen()
{
	// ��ʂ̒[�ŃX���C�h���~�߂�
	if (m_sliderPos < Game::kScreenWidth / 2)
	{
		m_sliderPos += kSliderSpeed;
		return false;
	}
	return true;
}

// �X���C�h�����Ƃ�
bool SceneBase::UpdateSliderClose()
{
	if (m_sliderPos > 0)
	{
		m_sliderPos -= kSliderSpeed;
		return false;
	}

	return true;
}

// �X���C�h�֘A
void SceneBase::DrawSliderDoor()
{
	DrawRotaGraph(Game::kScreenWidth / 2 - ((Game::kScreenWidth / 2) / 2) - m_sliderPos,
		Game::kScreenHeight / 2,
		1, DX_PI_F * 180.0f,
		m_hDoor, true, false);

	DrawRotaGraph(Game::kScreenWidth / 2 + ((Game::kScreenWidth / 2) / 2) + m_sliderPos,
		Game::kScreenHeight / 2,
		1, DX_PI_F * 180.0f,
		m_hDoor, true, true);
}