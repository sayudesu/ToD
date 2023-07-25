#include "ShotBase.h"
#include <cmath>

namespace
{
	constexpr float kSpeed = 10.0f;
}

ShotBase::ShotBase(VECTOR pos):
	m_pos(pos),
	m_isScreenOut(false)
{
}

ShotBase::~ShotBase()
{
}

void ShotBase::Update()
{
	// ��ʊO�̏��������Ȃ�
	if (m_pos.x > 500.0f)
	{
	//	m_isScreenOut = true;
	}

	if (!m_isScreenOut)
	{
		//m_pos.x += 30.0f;
	}

	VECTOR m_dir = VGet(0, 0, 0);
	VECTOR Player = VGet(300, 0, 0);
	//**** �v���C���[�Ǐ]��AI ****//
	// �������Z�o
	m_dir = VSub(Player, m_pos);

	// �v���C���[����G�l�~�[�܂ł̊p�x�����߂�
	float angle = atan2(m_dir.y, m_dir.x);

	// ���ݓG�������Ă�������̃x�N�g���𐶐�����
	MATRIX enemyRotMtx = MGetRotY(angle);
	VECTOR dir = VTransform(VGet(0, 0, 0), enemyRotMtx);

	// �΂߂ɂȂ����Ƃ�((1, 1, 0)�Ȃ�)�ɂ������񒷂��P�ɖ߂�(���K��)
	if (VSquareSize(m_dir) > 0)
	{
		m_dir = VNorm(m_dir);
	}

	// ���x�����߂�
	VECTOR velecity = VScale(m_dir, kSpeed);
	// 
	m_pos = VAdd(m_pos, velecity);

	//	m_pModel->SetPos(m_pos);
	//	m_pModel->SetRot(VGet(0, m_pPlayer->GetDir().y, 0));

}

void ShotBase::Draw()
{
	if (!m_isScreenOut)
	{
		DrawSphere3D(m_pos, 8, 8, 0x00ff00, 0x00ff00, true);
		DrawFormatString(100, 100, 0xffffff, "x = %f,y = %f,z = %f", m_pos.x, m_pos.y, m_pos.z);
	}

}
