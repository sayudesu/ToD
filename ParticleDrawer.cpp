#include "ParticleDrawer.h"
#include "Util/game.h"

namespace
{
	const char* kFileNameMeat = "Data/Image/UI_Meat.png";

	constexpr float kSpeed =10.0f;

	constexpr float kGravity = 0.2f;
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

void ParticleDrawer::Init()
{
	// 3D���W����2D���W�ɕϊ�
	m_posMain = ConvWorldPosToScreenPos(m_posMain);
	for (int i = 0; i < m_hGraph.size(); i++)
	{
		// �摜�̓ǂݍ���
		m_hGraph[i] = LoadGraph(kFileNameMeat);
		// �p�[�e�B�N���̏����ʒu
		m_pos[i] = m_posMain;
		
		// �ړ���
		m_vec[i].x = static_cast<float>(GetRand(6) - 3);
		m_vec[i].y = static_cast<float>(-GetRand(6) - 1);
	}
}

void ParticleDrawer::End()
{
	for (int i = 0; i < m_hGraph.size(); i++)
	{
		DeleteGraph(m_hGraph[i]);
	}
}

void ParticleDrawer::Update()
{
	(this->*m_pFunc)();
}

void ParticleDrawer::Draw()
{
	for (int i = 0; i < m_hGraph.size(); i++)
	{
		DrawRotaGraph(m_pos[i].x, m_pos[i].y, 0.5f, DX_PI_F * 180.0f, m_hGraph[i], true);
	}
}

bool ParticleDrawer::IsGetErase()
{
	return m_isErase;
}

void ParticleDrawer::First()
{
	for (int i = 0; i < m_hGraph.size(); i++)
	{
		// �d�͂�^����
		m_vec[i].y += kGravity;
		// �x�N�g���̉��Z
		m_pos[i] = VAdd(m_pos[i], m_vec[i]);
	}

	m_count++;
	if (m_count > 40)
	{
		m_count = 0;
		m_pFunc = &ParticleDrawer::Jet;
	}
}

void ParticleDrawer::Jet()
{
	for (int i = 0; i < m_hGraph.size(); i++)
	{
		// �ړ�
		// �������Z�o
		VECTOR dir = VSub(VGet(1500, Game::kScreenHeight - 110, 0),VGet(m_pos[i].x, m_pos[i].y,0));
		// �v���C���[����G�l�~�[�܂ł̊p�x�����߂�
		const float angle = atan2(dir.y, dir.x);
		// �΂߂ɂȂ����Ƃ�((1, 1, 0)�Ȃ�)�ɂ������񒷂��P�ɖ߂�(���K��)
		if (VSquareSize(dir) > 0)
		{
			dir = VNorm(dir);
		}
		// ���x�����߂�
		const VECTOR velecity = VScale(dir, kSpeed);
		// �ʒu��ς���
		m_pos[i] = VAdd(m_pos[i], velecity);		

		// ���菈��
		const VECTOR vec = VSub(m_pos[i], VGet(1500, Game::kScreenHeight - 110, 0));
		const float  del = VSize(vec);

		if (del < 4.0f + 1.0f)
		{
			m_isErase = true;
		}

		// �d�͂�^����
		m_vec[i].y += kGravity;
	}
}
