#include "ParticleDrawer.h"
#include "Util/game.h"

namespace
{
	// �摜�p�X
	//const char* kFileNameMeat = "Data/Image/UI_Meat.png";
	const char* kFileNameMeat = "Data/Image/icon_jewel.png";
	// �z�����ݑ��x
	constexpr float kSpeed = 5.0f;
}

ParticleDrawer::ParticleDrawer(VECTOR pos)
{
	m_posMain = pos;

	m_pFunc = &ParticleDrawer::First;

	m_speed = kSpeed;

	m_count = 0;

	m_isErase = false;
}

ParticleDrawer::~ParticleDrawer()
{
}

void ParticleDrawer::Init(int no)
{
	// 3D���W����2D���W�ɕϊ�
	m_posMain = ConvWorldPosToScreenPos(m_posMain);

	// �摜�̓ǂݍ���
	m_hGraph = LoadGraph(kFileNameMeat);
	// �p�[�e�B�N���̏����ʒu
	m_pos = m_posMain;

	// �ړ���
	if (no % 2 == 0)
	{
		m_vec.x = (-GetRand(6));
	}
	else
	{
		m_vec.x = (GetRand(6));
	}

	m_vec.y = (-GetRand(24));

	m_vec.x += (m_vec.x * 3.0f);
}

void ParticleDrawer::End()
{
	DeleteGraph(m_hGraph);
}

void ParticleDrawer::Update()
{
	(this->*m_pFunc)();
}

void ParticleDrawer::Draw()
{
	DrawRotaGraph(m_pos.x, m_pos.y, 0.5f, DX_PI_F * 180.0f, m_hGraph, true);
}

bool ParticleDrawer::IsGetErase()
{
	return m_isErase;
}

void ParticleDrawer::First()
{
//	m_vec.x += (m_vec.x * 0.01f);
	// �x�N�g���̉��Z
	m_pos = VAdd(m_pos, m_vec);

	m_count++;
	if (m_count >= 1)
	{
		m_count = 0;
		//m_vec.x += (m_vec.x * 3.0f);
		m_pFunc = &ParticleDrawer::Jet;
	}
}

void ParticleDrawer::Jet()
{
	// �ړ�
	// �������Z�o
	VECTOR dir = VSub(VGet(1500, Game::kScreenHeight - 110, 0),VGet(m_pos.x, m_pos.y,0));
	// �v���C���[����G�l�~�[�܂ł̊p�x�����߂�
	const float angle = atan2(dir.y, dir.x);
	// �΂߂ɂȂ����Ƃ�((1, 1, 0)�Ȃ�)�ɂ������񒷂��P�ɖ߂�(���K��)
	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}
	
	m_speed += 0.9f;

	// ���x�����߂�
	const VECTOR velecity = VScale(VGet(dir.x, dir.y, dir.z), m_speed);

	// �ʒu��ς���
	m_pos = VAdd(m_pos, VGet(velecity.x, velecity.y, velecity.z));
	m_pos = VAdd(m_pos, m_vec);
	
	// ���菈��
	const VECTOR vec = VSub(VGet(m_pos.x, m_pos.y, 0), VGet(1500, Game::kScreenHeight - 110, 0));
	const float  del = VSize(vec);

	if (del < 15.0f + 15.0f)
	{
		m_isErase = true;
	}
}
