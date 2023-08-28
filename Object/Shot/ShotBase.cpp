#include "ShotBase.h"
#include <cmath>
#include "../../Util/SoundFunctions.h"

namespace
{
	constexpr float kSpeed = 10.0f;
}

ShotBase::ShotBase(VECTOR pos):
	m_hShot(-1),
	m_pos(pos),
	m_targetPos(VGet(0,0,0)),
	m_isScreenOut(false)
{
//	SoundFunctions::Play(SoundFunctions::SoundIdShot);
	// 3D���f���̃��[�h
	m_hShot = MV1LoadModel("Data/Model/cat_Ver0.0.1.mv1");
	MV1SetScale(m_hShot, VGet(0.1f, 0.1f, 0.1f));
}

ShotBase::~ShotBase()
{
	// ���������
	MV1DeleteModel(m_hShot);
}

void ShotBase::Update()
{
	if (!m_isScreenOut)
	{
		VecCalculation();
		MV1SetPosition(m_hShot,m_pos);
	}
}

void ShotBase::Draw()
{
	if (!m_isScreenOut)
	{
	//	DrawSphere3D(m_pos, 8, 8, 0x00ff00, 0x00ff00, true);
		MV1DrawModel(m_hShot);
	}
}

// �ړ��̌v�Z�����Ă��܂�
void ShotBase::VecCalculation()
{
	//**** �Ǐ]��AI ****//
	// �������Z�o
	m_dir = VSub(m_targetPos, m_pos);
	// �v���C���[����G�l�~�[�܂ł̊p�x�����߂�
	const float angle = atan2(m_dir.y, m_dir.x);
	// ���ݓG�������Ă�������̃x�N�g���𐶐�����
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
	m_pos = VAdd(m_pos, velecity);
	//	m_pModel->SetPos(m_pos);
	//	m_pModel->SetRot(VGet(0, m_pPlayer->GetDir().y, 0));
}
