#include "CutInDrawer.h"
#include <DxLib.h>
#include <cassert>
#include "game.h"

namespace
{
	// �X���C�h�X�s�[�h
	constexpr int kSlideSpeed = 10.0f;
	// �ő�`��t���[����
	constexpr int kDrawFrameCount = 60;
}

CutInDrawer::CutInDrawer():
	m_hNewChallenger(-1),
	m_hSpacialAttack(-1),
	m_hSpShot(-1),
	m_countFrameSleep(0),
	m_slidePos(0),
	m_isEnd(false),
	m_pos(Game::kScreenWidth, 0)
{
}

CutInDrawer::~CutInDrawer()
{
}

void CutInDrawer::Init()
{
	// �摜�̓ǂݍ���
	m_hNewChallenger = LoadGraph("Data/Image/NewChallenger.png");
	assert(m_hNewChallenger != -1);
	m_hSpacialAttack = LoadGraph("Data/Image/SpacialAttack.png");
	assert(m_hSpacialAttack != -1);
	m_hSpShot        = LoadGraph("Data/Image/FrameCat0.png");
	assert(m_hSpShot        != -1);
}

void CutInDrawer::End()
{
	// �摜�̃f���[�g
	DeleteGraph(m_hNewChallenger);
	DeleteGraph(m_hSpacialAttack);
}

void CutInDrawer::Update()
{
	// �X���C�h����
	UpdateSlide();
}

// �X���C�h����
void CutInDrawer::UpdateSlide()
{
	m_isEnd = false;
	// ���t���[���`�悷��ƃX���C�h�ĊJ
	if (m_countFrameSleep > kDrawFrameCount)
	{
		m_slidePos = -Game::kScreenWidth;
		if (m_pos.x <= -Game::kScreenWidth)
		{
			m_isEnd = true;
		}
	}
	// �n�߂̃X���C�h
	if (m_pos.x > m_slidePos)
	{
		m_pos.x -= Game::kScreenWidth/kSlideSpeed;
	}
	else
	{
		m_countFrameSleep++;
	}

#if _DEBUG
	if(DxLib::CheckHitKey(KEY_INPUT_Q))
	{
		Reset();
	}
#endif

}
// ���Z�b�g
void CutInDrawer::Reset()
{
	m_pos.x = Game::kScreenWidth;
	m_slidePos = 0;
	m_countFrameSleep = 0;
}


void CutInDrawer::Draw()
{
	// �摜�̕`��
	DrawGraph(m_pos.x, m_pos.y, m_hSpacialAttack, true);
	DrawRotaGraph(
		m_pos.x + Game::kScreenWidth - 500.0f,
		m_pos.y + 500.0f,
		2,
		DX_PI_F * 180.0f,
		m_hSpShot,
		true);
}

bool CutInDrawer::IsGetEnd()
{
	return m_isEnd;
}

// ���Z�b�g
void CutInDrawer::IsSetEndReset()
{
	m_isEnd = false;
}
