#include "EnemyNormal.h"
#include <cmath>
#include <cassert>

#include "../../Util/Pad.h"

namespace
{
	// ���x
	constexpr float kSpeed = 3.0f;
	// �ړ��ʒu
	const VECTOR kNextPos1 = VGet(300, 0, 200);
	const VECTOR kNextPos2 = VGet(0, 0, 200);
}

EnemyNormal::EnemyNormal():
	m_dir(VGet(0,0,0)),
	m_targetPos(VGet(0,0,0)),
	m_count(-1)
{
}
EnemyNormal::~EnemyNormal()
{
}

void EnemyNormal::Init(VECTOR firstPos)
{
	// �����ʒu
	m_pos = firstPos;
}

void EnemyNormal::End()
{
}

void EnemyNormal::Update()
{
	////**** �Ǐ]��AI ****//
	//// �������Z�o
	//m_dir = VSub(m_targetPos, m_pos);
	//// �v���C���[����G�l�~�[�܂ł̊p�x�����߂�
	//const float angle = atan2(m_dir.y, m_dir.x);
	//// ���ݓG�������Ă�������̃x�N�g���𐶐�����
	//const MATRIX enemyRotMtx = MGetRotY(angle);
	//const VECTOR dir = VTransform(VGet(0, 0, 0), enemyRotMtx);
	////printfDx("%2d\n",dir.z);
	//// �΂߂ɂȂ����Ƃ�((1, 1, 0)�Ȃ�)�ɂ������񒷂��P�ɖ߂�(���K��)
	//if (VSquareSize(m_dir) > 0)
	//{
	//	m_dir = VNorm(m_dir);
	//}
	//// ���x�����߂�
	//const VECTOR velecity = VScale(m_dir, kSpeed);
	//// �ʒu��ς���
	//m_pos = VAdd(m_pos, velecity);
	////	m_pModel->SetPos(m_pos);
	////	m_pModel->SetRot(VGet(0, m_pPlayer->GetDir().y, 0));

	NextPosChange();
}

void EnemyNormal::NextPosChange()
{
	// �z�񂪖���������...
	assert(m_mapChip.size() != 0);

		// �}�b�v�`�b�v�T�C�Y
		const int mapChipMaxZ = 12;// �s
		const int mapChipMaxX = 25;// ��
		// �}�b�v�`�b�v�i���o�[(�G�̓�)
		const int enemyRoad = 2;
		// �u���b�N1�̑傫��
		const float block = 50.0f;

		m_count = -1;

		// �s
		for (int z = 0; z < mapChipMaxZ; ++z)
		{	
			// ��
			for (int x = 0; x < mapChipMaxX; ++x)
			{
					// [���݂̗� + ���݂̗� * �`�b�v�ő��]
					if (m_mapChip[x + z * mapChipMaxX] == enemyRoad)
					{
						//// �G�̈ʒu�ɑ��
						m_pos.x = (x * block);
						m_pos.z = (z * block);
					}
			}
		}	
}

void EnemyNormal::Draw()
{
	DrawSphere3D(m_pos, 16, 16, 0xff0000, 0xff0000, true);
}
