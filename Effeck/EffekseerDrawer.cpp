#include "EffekseerDrawer.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <cassert>

EffekseerDrawer::EffekseerDrawer():
	m_pos(VGet(0,0,0)),
	m_hEff(-1),
	m_hPlayEff(-1),
	m_time(0)
{
}

EffekseerDrawer::~EffekseerDrawer()
{
}

void EffekseerDrawer::Init()
{
	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	m_hEff = LoadEffekseerEffect("Data/Effect/goal.efkefc",30.0f);
	assert(m_hEff != -1);
}

void EffekseerDrawer::End()
{
	// Effekseer�ɂ��Đ�����3D�G�t�F�N�g�̕`����I������B
	DrawEffekseer3D_End();
	// �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă�����)
	DeleteEffekseerEffect(m_hEff);
	// 3D�\���̃G�t�F�N�g���~����B
	StopEffekseer3DEffect(m_hPlayEff);

	m_pos = VGet(0, 0, 0);	
}

void EffekseerDrawer::Update()
{
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();
}

void EffekseerDrawer::Draw()
{
	// ����I�ɃG�t�F�N�g���Đ�����
	if (m_time % 60 == 0)
	{
		// �G�t�F�N�g���Đ�����B
		m_hPlayEff = PlayEffekseer3DEffect(m_hEff);
	}
	m_time++;

	// �Đ����̃G�t�F�N�g���ړ�����B
	SetPosPlayingEffekseer3DEffect(m_hPlayEff, m_pos.x, m_pos.y , m_pos.z);

	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
}

void EffekseerDrawer::GetPos(VECTOR pos)
{
	m_pos = pos;
}

int EffekseerDrawer::SetPlayingNow()
{
	return IsEffekseer3DEffectPlaying(m_hPlayEff);
}
