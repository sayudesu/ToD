#include "CutInDrawer.h"
#include <DxLib.h>
#include <cassert>
#include "Util/game.h"

namespace
{
	// スライドスピード
//	constexpr int kSlideSpeed = 200.0f;
	constexpr int kSlideSpeed = 10.0f;
}

CutInDrawer::CutInDrawer():
	m_hNewChallenger(-1),
	m_hSpacialAttack(-1),
	m_countFrameSleep(0),
	m_slidePos(0),
	m_pos(Game::kScreenWidth, 0)
{
}

CutInDrawer::~CutInDrawer()
{
}

void CutInDrawer::Init()
{
	// 画像の読み込み
	m_hNewChallenger = LoadGraph("Data/Image/NewChallenger.png");
	assert(m_hNewChallenger != -1);
	m_hSpacialAttack = LoadGraph("Data/Image/SpacialAttack.png");
	assert(m_hSpacialAttack != -1);
}

void CutInDrawer::End()
{
	// 画像のデリート
	DeleteGraph(m_hNewChallenger);
	DeleteGraph(m_hSpacialAttack);
}

void CutInDrawer::Update()
{
	// スライド処理
	UpdateSlide();
}

// スライド処理
void CutInDrawer::UpdateSlide()
{
	if (m_countFrameSleep > 60)
	{
		m_slidePos = -Game::kScreenWidth;
	}
	if (m_pos.x > m_slidePos)
	{
		m_pos.x -= Game::kScreenWidth/kSlideSpeed;
	}
	else
	{
		//m_pos.x = 0;
		m_countFrameSleep++;
	}

#if _DEBUG
	if(DxLib::CheckHitKey(KEY_INPUT_Q))
	{
		Reset();
	}
#endif

}
// リセット
void CutInDrawer::Reset()
{
	m_pos.x = Game::kScreenWidth;
	m_slidePos = 0;
	m_countFrameSleep = 0;
}

void CutInDrawer::Draw()
{
	// 画像の描画
	DrawGraph(m_pos.x, m_pos.y, m_hSpacialAttack, true);
}
