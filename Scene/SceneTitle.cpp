#include "SceneTitle.h"
#include "Scene/SceneMain.h"
#include <DxLib.h>
#include "Util/Pad.h"
#include "Util/game.h"

namespace
{
	// �^�C�g�����S�̃p�X
	const char* titlePath = "Data/Image/VitalFortress.png";
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
	m_hTitleLogo = LoadGraph(titlePath);
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
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return new SceneMain;
	}
	return this;
}

void SceneTitle::Draw()
{
	// �w�i�F
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaaaa, true);
	static int x = Game::kScreenWidth/2;
	static int y = Game::kScreenHeight/2 - 200.0f;
	static int scale = 2;
	// �^�C�g�����S��`��
	DrawRotaGraph(x, y, scale, DX_PI * 180, m_hTitleLogo, true);
}
