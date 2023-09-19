#include "BloodDrawer.h"
#include "Util/game.h"

namespace
{
	// �摜�p�X
	const char* kFileNameMeat = "Data/Image/UI_Meat.png";
	// �z�����ݑ��x
	constexpr float kSpeed =10.0f;
	// �d��
	constexpr float kGravity = 0.2f;
}

BloodDrawer::BloodDrawer(VECTOR pos)
{
	// �p�[�e�B�N���̏����ʒu
	m_pos = pos;

	m_pFunc = &BloodDrawer::First;

	m_speed = kSpeed;

	m_count = 0;

	m_isErase = false;
}

BloodDrawer::~BloodDrawer()
{
}

void BloodDrawer::Init()
{		
	// �ړ���
	m_vec.x = static_cast<float>(GetRand(3) - 1);
	m_vec.y = static_cast<float>(-GetRand(2) - 1);
	m_vec.z = static_cast<float>(GetRand(3) - 1);
}

void BloodDrawer::End()
{
}

void BloodDrawer::Update()
{
	(this->*m_pFunc)();
}

void BloodDrawer::Draw()
{
	// �R�c��ԏ�ɋ���`�悷��
	DrawSphere3D(m_pos, 2, 4, 0xff0000, 0xff0000, true);

}

bool BloodDrawer::IsGetErase()
{
	return m_isErase;
}

void BloodDrawer::First()
{
	// �d�͂�^����
	m_vec.y += kGravity;
	// �x�N�g���̉��Z
	m_pos = VSub(m_pos, m_vec);

	m_count++;
	if (m_pos.y < -10.0f)
	{
		m_isErase = true;
	}
}

void BloodDrawer::Jet()
{

	//// �ړ�
	//// �������Z�o
	//VECTOR dir = VSub(VGet(1500, Game::kScreenHeight - 110, 0),VGet(m_pos.x, m_pos.y,0));
	//// �v���C���[����G�l�~�[�܂ł̊p�x�����߂�
	//const float angle = atan2(dir.y, dir.x);
	//// �΂߂ɂȂ����Ƃ�((1, 1, 0)�Ȃ�)�ɂ������񒷂��P�ɖ߂�(���K��)
	//if (VSquareSize(dir) > 0)
	//{
	//	dir = VNorm(dir);
	//}
	//// ���x�����߂�
	//const VECTOR velecity = VScale(dir, kSpeed);
	//// �ʒu��ς���
	//m_pos = VAdd(m_pos, velecity);		

	//// ���菈��
	//const VECTOR vec = VSub(VGet(m_pos.x, m_pos.y, 0), VGet(1500, Game::kScreenHeight - 110, 0));
	//const float  del = VSize(vec);

	//if (del < 5.0f + 5.0f)
	//{
	//	m_isErase = true;
	//}

	// �d�͂�^����
	m_vec.y += kGravity;
}
