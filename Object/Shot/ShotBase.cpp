#include "ShotBase.h"
#include <cmath>
#include "../../Util/SoundFunctions.h"

namespace
{
	constexpr float kSpeed = 30.0f;
}

ShotBase::ShotBase(VECTOR pos):
	m_pos(pos),
	m_isTracking(true)
{
//	SoundFunctions::Play(SoundFunctions::SoundIdShot);
	m_collData.datage = 0;
	m_collData.pos = VGet(0,0,0);
	m_collData.radius = 0;

}

bool ShotBase::IsGetEnd()
{
	if (m_nowPosToNextPosX < 30.0f &&
		m_nowPosToNextPosZ < 30.0f)
	{
	//	return true;
	}

	return false;
}

// �ړ��̌v�Z�����Ă��܂�
void ShotBase::VecCalculation(VECTOR tagetPos,float speed,bool isTracking)
{	
	if (m_isTracking)
	{
		// �������Z�o
		m_dir = VSub(tagetPos, m_pos);
	}

	// �v���C���[����G�l�~�[�܂ł̊p�x�����߂�
	const float angle = atan2(m_dir.y, m_dir.x);

	// ���ݓG�������Ă�������̃x�N�g���𐶐�����
	const MATRIX enemyRotMtx = MGetRotY(angle);

	// �΂߂ɂȂ����Ƃ�((1, 1, 0)�Ȃ�)�ɂ������񒷂��P�ɖ߂�(���K��)
	if (VSquareSize(m_dir) > 0)
	{
		m_dir = VNorm(m_dir);
	}

	// ���x�����߂�
	const VECTOR velecity = VScale(m_dir, speed);

	// �ʒu��ς���
	m_pos = VAdd(m_pos, velecity);

	// �G�����̂܂ܒǐՂ��邩�ǂ���
	if (isTracking)
	{
		m_isTracking = true;
	}
	else
	{
		m_isTracking = false;
	}

	// �����𑪂�
	m_nowPosToNextPosX = static_cast<float>(sqrt(pow(m_pos.x - tagetPos.x, 2) + pow(m_pos.x - tagetPos.x, 2)));
	m_nowPosToNextPosZ = static_cast<float>(sqrt(pow(m_pos.z - tagetPos.z, 2) + pow(m_pos.z - tagetPos.z, 2)));
}
