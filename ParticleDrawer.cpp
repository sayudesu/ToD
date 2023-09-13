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
		m_vec[i].y = static_cast<float>(GetRand(2) - 1);
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
	if (m_count > 30)
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
		VECTOR m_dir = VSub(VGet(Game::kScreenWidth, Game::kScreenHeight, 0), m_pos[i]);
		// �v���C���[����G�l�~�[�܂ł̊p�x�����߂�
		const float angle = atan2(m_dir.y, m_dir.x);
		// ���݌����Ă�������̃x�N�g���𐶐�����
		const MATRIX enemyRotMtx = MGetRotY(angle);
		const VECTOR dir = VTransform(VGet(0, 0, 0), enemyRotMtx);
		// �΂߂ɂȂ����Ƃ�((1, 1, 0)�Ȃ�)�ɂ������񒷂��P�ɖ߂�(���K��)
		if (VSquareSize(m_dir) > 0)
		{
			m_dir = VNorm(m_dir);
		}
		// ���x�����߂�
		const VECTOR velecity = VScale(m_dir, kSpeed);
		// �ʒu��ς���
		m_pos[i] = VAdd(m_pos[i], velecity);

		//// �����𑪂�
		//const float nowPosToNextPosX = static_cast<int>(sqrt(pow(m_pos[i].x - Game::kScreenWidth, 2) + pow(m_pos[i].x - Game::kScreenWidth, 2)));
		//const float nowPosToNextPosZ = static_cast<int>(sqrt(pow(m_pos[i].y - Game::kScreenHeight, 2) + pow(m_pos[i].y - Game::kScreenHeight, 2)));

		//// �ړ��܂ł̋������Z����
		//if (nowPosToNextPosX < 3.0f &&
		//	nowPosToNextPosZ < 3.0f)
		//{
		//	m_pFunc = &ParticleDrawer::Jet;
		//}
	}
}
