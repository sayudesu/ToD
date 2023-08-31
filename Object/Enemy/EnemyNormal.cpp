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

	// �ʂ������̂���ꏊ�̋L�^
	m_recordX.push_back(forX);
	m_recordZ.push_back(forZ);

	m_testPosX.push_back(m_pos.x);
	m_testPosZ.push_back(m_pos.z);
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
	const int enemyStop = 4;
	// �u���b�N1�̑傫��
	const float block = 50.0f;

	m_pos.y = -block + 50.0f;

	int tempZ = 0;
	int tempX = 0;

	bool isBreak = false;

	if (Pad::isTrigger(PAD_INPUT_3)){
		// �s
		for (int z = forZ - 1; z <= forZ + 1; z++){
			// �S�Ă�for������E�o����
			if (isBreak)
			{
				isBreak = false;
				break;
			}
			// �z��̐���
			tempZ = z;
			if (z >= mapChipMaxZ) { tempZ = mapChipMaxZ; }
			if (z <= 0) { tempZ = 0; }
			// ��
			for (int x = forX - 1; x <= forX + 1; x++){
				// �z��̐���
				tempX = x;
				if (x >= mapChipMaxX){tempX = mapChipMaxX;}
				if (x <= 0){tempX = 0;}
				bool isStop = false;
				bool isMove = false;
				if (m_mapChip[tempX + tempZ * mapChipMaxX] == enemyStop)
				{
					printfDx("����I�т܂��B\n");
				}
				// [���݂̗� + ���݂̗� * �`�b�v�ő��]
				if (m_mapChip[tempX + tempZ * mapChipMaxX] == enemyRoad)
				{			
					printfDx("�ړ����܂��B\n");

					// ��x�ʂ������݂͂Ȃ�
					bool back = false;
					for (int i = 0; i < m_recordX.size(); i++)
					{
						// ���悤�Ƃ��Ă���ꍇ��continu
						if (m_recordX[i] == tempX && m_recordZ[i] == tempZ)
						{
							back = true;
						}
					}

					if (back)
					{
						printfDx("continue\n");
						continue;
					}

					// ���W���L�^
					forX = tempX;
					forZ = tempZ;
					// �ʂ������̂���ꏊ�̋L�^
					m_recordX.push_back(forX);
					m_recordZ.push_back(forZ);
					// �G�̈ʒu���X�V
					m_pos.x = ((forX)*block);
					m_pos.z = ((forZ)*block);
					// �S�Ă�for������E�o����
					isBreak = true;
					break;			
				}
			}
		}	

		// �����ňړ�������

	}
}


void EnemyNormal::Draw()
{

	//for (int i = 0; i < m_testPosX.size(); i++)
	//{
	//	VECTOR pos = VGet(m_testPosX[i], 0.0f, m_testPosZ[i]);
	//	DrawSphere3D(pos, 16, 16, 0xff00ff, 0xff00ff, true);
	//}

	DrawSphere3D(m_pos, 16, 16, 0xff0000, 0xff0000, true);
}
