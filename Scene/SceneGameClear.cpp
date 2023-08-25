#include "SceneGameClear.h"
#include "../Util/game.h"

#include <cassert>

SceneGameClear::SceneGameClear()
{
	m_handle = -1;
	m_shader = -1;
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::Init()
{
	// �摜�̓ǂݍ���
	m_handle = LoadGraph("end.png");
	GetGraphSize(m_handle, &m_handleSizeX, &m_handleSizeY);
	assert(m_handle != -1);

	// �s�N�Z���V�F�[�_�[�o�C�i���R�[�h�̓ǂݍ���
	m_shader = LoadPixelShader("Shader/SamplePS.pso");
	assert(m_shader != -1);

}

void SceneGameClear::End()
{
	// �V�F�[�_�[�폜
	DeleteShader(m_shader);
}

SceneBase* SceneGameClear::Update()
{
	m_hScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);

	// ���_�f�[�^�̏���
	Vert[0].pos = VGet(0.0f, 0.0f, 0.0f);
	Vert[1].pos = VGet(Game::kScreenWidth - 1, 0.0f, 0.0f);
	Vert[2].pos = VGet(0.0f, Game::kScreenHeight - 1, 0.0f);
	Vert[3].pos = VGet(Game::kScreenWidth - 1, Game::kScreenHeight - 1, 0.0f);
	Vert[0].dif = GetColorU8(255, 255, 255, 255);
	Vert[0].spc = GetColorU8(0, 0, 0, 0);
	Vert[0].u = 0.0f; Vert[0].v = 0.0f;
	Vert[1].u = 1.0f; Vert[1].v = 0.0f;
	Vert[2].u = 0.0f; Vert[2].v = 1.0f;
	Vert[3].u = 1.0f; Vert[3].v = 1.0f;
	Vert[0].su = 0.0f; Vert[0].sv = 0.0f;
	Vert[1].su = 1.0f; Vert[1].sv = 0.0f;
	Vert[2].su = 0.0f; Vert[2].sv = 1.0f;
	Vert[3].su = 1.0f; Vert[3].sv = 1.0f;
	Vert[0].rhw = 1.0f;
	Vert[1].rhw = 1.0f;
	Vert[2].rhw = 1.0f;
	Vert[3].rhw = 1.0f;
	Vert[4] = Vert[2];
	Vert[5] = Vert[1];

	// �g�p����e�N�X�`�����Z�b�g
	SetUseTextureToShader(0, m_hScreen);

	// �g�p����s�N�Z���V�F�[�_�[���Z�b�g
	SetUsePixelShader(m_shader);

	return this;
}

void SceneGameClear::Draw()
{
	// �`��
	DrawPrimitive2DToShader(Vert, 6, DX_PRIMTYPE_TRIANGLELIST);

//	SetDrawScreen(DX_SCREEN_BACK);

	DrawGraph(0, 0, m_hScreen, false);
}
