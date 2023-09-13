#include "SceneGameClear.h"
#include "../Util/game.h"

#include <cassert>

SceneGameClear::SceneGameClear(int a)
{
	m_handle = -1;
	
	// 画像の読み込み
	if (a == 0)
	{
		m_handle = LoadGraph("Data/image/W.png");
	}
	if (a == 1)
	{
		m_handle = LoadGraph("Data/image/L.png");
	}
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::Init()
{

	GetGraphSize(m_handle, &m_handleSizeX, &m_handleSizeY);
	assert(m_handle != -1);
}

void SceneGameClear::End()
{

}

SceneBase* SceneGameClear::Update()
{

	// スライドを開ける
	SceneBase::UpdateSlider(m_isSliderOpen);

	

	return this;
}

void SceneGameClear::Draw()
{
	DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 1, DX_PI_F * 180.0f, m_handle, true);

	SceneBase::DrawSliderDoor();
}
