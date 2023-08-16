#include "EnemyNormal.h"
#include <cmath>

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
	m_targetPos(VGet(0,0,0))
{
}
EnemyNormal::~EnemyNormal()
{
}

void EnemyNormal::Init()
{
	int z = 250;
	int puls = -1;

	for (int i = 0; i < m_mapChip.size(); i++)
	{
		// �J�E���g
		puls++;
		// �E�ɉ����l�߂�
		int x = -600;
		x += (puls * 50);

		// Z���ύX
		if (m_mapChip[i] == 0)
		{
			puls = -1;
			z -= 50;
		}

		// �����ʒu
		if (m_mapChip[i] == 3)
		{
			m_pos = VGet(x, 0.0f, z);
		}

	}
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

	//}
	//for (int y = 0; y < 13; ++y)
	//{

	//	for (int x = 0; x < 26; ++x) 
	//	{

	//		if (m_mapChip[x + y * 26] == 2) 
	//		{

	//			m_targetPos.x = x * m_mapChip[x], y* m_mapChip[y];
	//			m_targetPos.y = x * m_mapChip[x], y* m_mapChip[y];
	//			m_targetPos.z = x * m_mapChip[x], y* m_mapChip[y];

	//		}

	//	}

	//}
}

void EnemyNormal::Draw()
{
	//int z = 250;
	//int puls = -1;

	//for (int i = 0; i < m_mapChip.size(); i++)
	//{
	//	// �J�E���g
	//	puls++;
	//	// �E�ɉ����l�߂�
	//	int x = -600;
	//	x += (puls * 50);

	//	// Z���ύX
	//	if (m_mapChip[i] == 0)
	//	{
	//		puls = -1;
	//		z -= 50;
	//	}

	//	if (m_mapChip[i] == 2)
	//	{
	//		VECTOR pos = VGet(x, 0.0f, z);
	//		DrawSphere3D(pos, 16, 16, 0xffff00, 0xffff00, true);
	//	}
	//}

	DrawSphere3D(m_pos, 16, 16, 0xff0000, 0xff0000, true);
}
