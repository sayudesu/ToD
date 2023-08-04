#include "SceneBase.h"
#include <DxLib.h>
#include <cassert>
#include "../Util/game.h"

namespace
{
	// スライドスピード
	constexpr int kSliderSpeed = 20;
}

SceneBase::SceneBase()
{
	// スライダー関連
	m_hDoor = LoadGraph("Data/Image/DoorH.png");
	assert(m_hDoor != -1);
	m_sliderPosX = 0;
	m_isSliderOpen = false;
	m_isChangeScene = false;
}
void SceneBase::UpdateSlider(bool& open)
{
	// スライドを開ける
	if (!open)
	{
		if (SceneBase::UpdateSliderOpen())
		{
			open = true;
		}
	}
}

// スライドを開けるとき
bool SceneBase::UpdateSliderOpen()
{
	// 画面の端でスライドを止める
	if (m_sliderPosX < Game::kScreenWidth / 2)
	{
		m_sliderPosX += kSliderSpeed;
		return false;
	}
	return true;
}

// スライドを閉じるとき
bool SceneBase::UpdateSliderClose()
{
	if (m_sliderPosX > 0)
	{
		m_sliderPosX -= kSliderSpeed;
		return false;
	}

	return true;
}

// スライド関連
void SceneBase::DrawSliderDoor()
{
	DrawRotaGraph(Game::kScreenWidth / 2 - ((Game::kScreenWidth / 2) / 2) - m_sliderPosX,
		Game::kScreenHeight / 2,
		1, DX_PI_F * 180.0f,
		m_hDoor, true, false);

	DrawRotaGraph(Game::kScreenWidth / 2 + ((Game::kScreenWidth / 2) / 2) + m_sliderPosX,
		Game::kScreenHeight / 2,
		1, DX_PI_F * 180.0f,
		m_hDoor, true, true);
}