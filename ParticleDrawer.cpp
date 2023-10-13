#include "ParticleDrawer.h"
#include "Util/game.h"

namespace
{
	// �摜�p�X
	const char* kFileNameMeat = "Data/Image/UI_Meat.png";
	// �摜�T�C�Y
	constexpr float kMeatSize = 0.5f;
	// �摜�p�x
	constexpr float kMeatRota = DX_PI_F * 180.0f;
	// �z�����ݑ��x
	constexpr float kSpeed = 5.0f;
	// �摜�̔��a
	constexpr float kMeatRadius = 20.0f;
	// �R�X�g�摜�ʒu�̔��a
	constexpr float kCostRadius = 20.0f;
	// �R�X�g�摜�ʒu
	const VECTOR kCostPos = VGet(1500, 110, 0);
}

ParticleDrawer::ParticleDrawer(VECTOR pos)
{
	m_pos = pos;

	m_pFunc = &ParticleDrawer::FirstMove;

	m_speed = kSpeed;

	m_isErase = false;
}

ParticleDrawer::~ParticleDrawer()
{
}

void ParticleDrawer::Init(int no)
{
	// 3D���W����2D���W�ɕϊ�
	// �p�[�e�B�N���̏����ʒu
	m_pos = ConvWorldPosToScreenPos(m_pos);

	// �摜�̓ǂݍ���
	m_hGraph = LoadGraph(kFileNameMeat);

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
	DrawRotaGraph(m_pos.x, m_pos.y, kMeatSize, kMeatRota, m_hGraph, true);
}

bool ParticleDrawer::IsGetErase()
{
	return m_isErase;
}

void ParticleDrawer::FirstMove()
{
	// �x�N�g���̉��Z
	m_pos = VAdd(m_pos, m_vec);

	m_pFunc = &ParticleDrawer::Suction;
}

void ParticleDrawer::Suction()
{
	// �ړ�
	// �������Z�o
	VECTOR dir = VSub(kCostPos,VGet(m_pos.x, m_pos.y,0));
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
	const VECTOR vec = VSub(VGet(m_pos.x, m_pos.y, 0), kCostPos);
	const float  del = VSize(vec);

	if (del < kMeatRadius + kCostRadius)
	{
		m_isErase = true;
	}
}
