#include "EnemyNormal.h"
#include <cmath>
#include <cassert>

#include "../../Util/Pad.h"

namespace
{
	// ���x
	constexpr float kSpeed = 3.0f;
}

EnemyNormal::EnemyNormal() :
	m_dir(VGet(0, 0, 0)),
	m_targetPos(VGet(0, 0, 0)),
	m_count(-1),
	forX(0),
	forZ(0)
{
}
EnemyNormal::~EnemyNormal()
{
}

void EnemyNormal::Init(VECTOR firstPos, int x, int z)
{
	// �����ʒu
	m_pos = firstPos;
	forX = x;
	forZ = z;

	m_recordX.push_back(forX);
	m_recordZ.push_back(forZ);
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
	const int mapChipMaxZ = 13;// �s
	const int mapChipMaxX = 25;// ��
	// �}�b�v�`�b�v�i���o�[(�G�̓�)
	const int enemyRoad = 2;
	// �u���b�N1�̑傫��
	const float block = 50.0f;

	m_pos.y = -block + 50.0f;

	int tempZ = 0;
	int tempX = 0;
	
	int count = -1;
	if (Pad::isTrigger(PAD_INPUT_3)){
		// �s
		for (int z = forZ - 1; z <= forZ + 1; ++z){
			// ��
			for (int x = forX - 1; x <= forX + 1; ++x){
				// �z��̐���
				tempZ = z;
				if (z > mapChipMaxZ){tempZ = mapChipMaxZ;}
				if (z < 0){tempZ = 0;}
				// �z��̐���
				tempX = x;
				if (x > mapChipMaxX){tempX = mapChipMaxX;}
				if (x < 0){tempX = 0;}
				
				//count++;
				//m_checkPos[count].x = ((tempX)*block);
				//m_checkPos[count].z = ((tempZ)*block);
				//m_checkPos[count].y = 50.0f;

				// [���݂̗� + ���݂̗� * �`�b�v�ő��]
				if (m_mapChip[tempX + tempZ * mapChipMaxX] == enemyRoad)
				{				
					// ��x�ʂ������݂͂Ȃ�
					bool back = false;
					for (int i = 0; i < m_recordX.size(); i++)
					{
						// ���悤�Ƃ��Ă���ꍇ��continu
						if (m_recordX[i] == x && m_recordZ[i] == z)
						{
							back = true;
						}
					}
					if (back)
					{
						continue;
					}
					// ���W���L�^
					forX = x;
					forZ = z;

					// 1�܂��̏ꏊ
					m_recordX.push_back(x);
					m_recordZ.push_back(z);
					// �G�̈ʒu�ɑ��
					m_pos.x = ((x) * block);
					m_pos.z = ((z) * block);
					// ���W����
					if (x > mapChipMaxX)forX = mapChipMaxX;
					if (z > mapChipMaxZ)forZ = mapChipMaxZ;
					if (x < 0)forX = 0;
					if (z < 0)forZ = 0;
#if _DEBUG
					// �f�o�b�O�p
					//m_testPosX.push_back(m_pos.x);
					//m_testPosZ.push_back(m_pos.z);
					//printfDx("�ʉ�\n");
					printfDx(" x = %d  z = %d\n",x,z);
					printfDx("tx = %d tz = %d\n",tempX, tempZ);
					printfDx("fx = %d fz = %d\n", forX, forZ);
#endif
					break;
				}
			}
		}	
	}
}


void EnemyNormal::Draw()
{

	//for (int i = 0; i < m_testPosX.size(); i++)
	//{
	//	VECTOR pos = VGet(m_testPosX[i], 0.0f, m_testPosZ[i]);
	//	DrawSphere3D(pos, 16, 16, 0xff00ff, 0xff00ff, true);
	//}

	//for (int i = 0; i < 9; i++)
	//{
	//	DrawSphere3D(m_checkPos[i], 16, 16, 0xffffff, 0xffffff, true);
	//}


	DrawSphere3D(m_pos, 16, 16, 0xff0000, 0xff0000, true);
}
