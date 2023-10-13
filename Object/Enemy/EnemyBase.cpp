#include "EnemyBase.h"
#include <cassert>

namespace
{
	// ����
	constexpr float kRange = 50.0f;
	// ���a
	constexpr float kRadius = 16.0f * 2.0f;
}

void EnemyBase::Init(VECTOR firstPos, int x, int z)
{
	// �����ʒu
	m_pos = firstPos;
	m_chipPosX = x;
	m_chipPosZ = z;
	// �ʂ������̂���ꏊ�̋L�^
	m_recordX.push_back(m_chipPosX);
	m_recordZ.push_back(m_chipPosZ);
	// ���̏ꏊ�ɍs�����ǂ���
	m_isNextMove = true;
	// ���f���̓ǂݍ���
	m_hModel = MV1LoadModel(m_filePathModel);
	// �����ʒu
	MV1SetPosition(m_hModel, m_pos);
	// �����p�x
	MV1SetRotationXYZ(m_hModel, VGet(0, 90.0f * DX_PI_F / 18.0f, 0));
	// �傫��
	MV1SetScale(m_hModel, VGet(m_collData.size, m_collData.size, m_collData.size));
	// �̗�
	m_hp = m_collData.hp;
}

void EnemyBase::End()
{
	// ���������
	MV1DeleteModel(m_hModel);
}

void EnemyBase::Update()
{
	Move();
}

// �G��`��
void EnemyBase::Draw()
{
	MV1DrawModel(m_hModel);
}

void EnemyBase::DrawUI()
{
	//�̗͂�`��
	//�O�g
	DrawBox(
		m_screenPos.x - 20.0f - 1,
		m_screenPos.y - 5 - 30.0f - 1,
		m_screenPos.x + 40 - 20.0f + 1,
		m_screenPos.y + 5 - 30.0f + 1,
		0xffffff,
		true);
	DrawBox(
		m_screenPos.x - 20.0f,
		m_screenPos.y - 5 - 30.0f,
		m_screenPos.x + 40 - 20.0f,
		m_screenPos.y + 5 - 30.0f,
		0xaaaaaa,
		true);
	//���[�^�[
	DrawBox(
		m_screenPos.x - 20.0f,
		m_screenPos.y - 5 - 30.0f,
	    m_screenPos.x + 40 * m_hp / m_collData.hp - 20.0f,	//���� * HP / HPMAX
		m_screenPos.y + 5 - 30.0f,
		0xaa0000,
		true);
}

void EnemyBase::SetHitDamage(int damage)
{
	m_hp -= damage;
}

bool EnemyBase::GetErase()const
{
	// ���ƂŏC��
	if (m_hp <= 0)
	{
		return true;
	}
	return false;
}

void EnemyBase::ChangeNextPos(bool& isMoveing)
{
	// �z�񂪖���������...
	assert(m_mapChip.data.size() != 0);

	m_pos.y = -m_mapChip.blockSizeY + 50.0f;

	int tempZ = 0;
	int tempX = 0;

	bool isBreak = false;

	// �ǂ̃}�b�v�`�b�v�̏�ɂ��邩
	bool isStop = false;
	bool isMove = false;

	int tempStopPosZ = 0;
	int tempStopPosX = 0;

	int tempMovePosZ = 0;
	int tempMovePosX = 0;

	if (isMoveing) {
		// �s
		for (int z = m_chipPosZ - 1; z <= m_chipPosZ + 1; z++)
		{
			// �S�Ă�for������E�o����
			if (isBreak)
			{
				isBreak = false;
				break;
			}
			// �z��̐���
			tempZ = z;
			if (z >= m_mapChip.chipMaxZ) { tempZ = m_mapChip.chipMaxZ - 1; }
			if (z <= 0) { tempZ = 0; }
			// ��
			for (int x = m_chipPosX - 1; x <= m_chipPosX + 1; x++)
			{
				// �z��̐���
				tempX = x;
				if (x >= m_mapChip.chipMaxX) { tempX = m_mapChip.chipMaxX - 1; }
				if (x <= 0) { tempX = 0; }

				// �����ňړ�������

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
				// ��΂�
				if (back)
				{
					back = false;
					continue;
				}

				// [���݂̗� + ���݂̗� * �`�b�v�ő��]
				if ((m_mapChip.data[tempX + tempZ * m_mapChip.chipMaxX] == m_mapChip.enemyStop))
				{
					// �~�܂邱�Ƃ�m�点��
					isStop = true;

					// �}�b�v�`�b�v�ł̏ꏊ���L�^
					tempStopPosX = tempX;
					tempStopPosZ = tempZ;

					// �~�܂�ꏊ�����܂����̂�braak
					isBreak = true;
					break;
				}
				// [���݂̗� + ���݂̗� * �`�b�v�ő��]
				else if ((m_mapChip.data[tempX + tempZ * m_mapChip.chipMaxX] == m_mapChip.enemyRoad))
				{
					// �������Ƃ�m�点��
					isMove = true;

					// �}�b�v�`�b�v�ł̏ꏊ���L�^
					tempMovePosX = tempX;
					tempMovePosZ = tempZ;

					// �������̂ł���������m�F
					m_moveDirX.push_back(tempX);
					m_moveDirZ.push_back(tempZ);
				}
			}
		}

		if (m_isRandMove && isMove)
		{
			// �i�ވʒu�������_���Ɍ��߂�
			tempMovePosX = m_moveDirX[GetRand(static_cast<int>(m_moveDirX.size()) - 1)];
			tempMovePosZ = m_moveDirZ[GetRand(static_cast<int>(m_moveDirZ.size()) - 1)];
			m_isRandMove = false;
		}
		else
		{
			// �v�f������
			for (int i = 0; i < m_moveDirX.size(); i++)
			{
				m_moveDirX.pop_back();
				m_moveDirZ.pop_back();
			}
		}

		// ����������ꍇ�̂�
		if (isMove || isStop)
		{
			// �����~�܂�ꏊ
			if (isStop)
			{
				// �����Ȃ�
				isMove = false;
			}

			// ���W���L�^
			// �������ꏊ
			if (isMove)
			{
				m_chipPosX = tempMovePosX;
				m_chipPosZ = tempMovePosZ;
			}
			// ���W���L�^
			// �����~�܂�ꏊ
			if (isStop)
			{
				m_chipPosX = tempStopPosX;
				m_chipPosZ = tempStopPosZ;

				m_isRandMove = true;

				isStop = false;
			}

			// �t���O�̃��Z�b�g
			isMove = false;
			isStop = false;

			// �ʂ������̂���ꏊ�̋L�^
			m_recordX.push_back(m_chipPosX);
			m_recordZ.push_back(m_chipPosZ);
			// �ʒu��ύX
			m_targetPos.x = (m_chipPosX * m_mapChip.blockSizeY);
			m_targetPos.z = (m_chipPosZ * m_mapChip.blockSizeZ);
			isMoveing = false;

			// �v�f������
			for (int i = 0; i < m_moveDirX.size(); i++)
			{
				m_moveDirX.pop_back();
				m_moveDirZ.pop_back();
			}
		}
		else
		{
			m_isEndPos = true;
		}
	}
}

void EnemyBase::Move()
{
	if (!m_isEndPos)
	{
		MV1SetPosition(m_hModel, m_pos);
		// �ǂ��Ɉړ����邩���l����
		ChangeNextPos(m_isNextMove);

		// �ړ�
		// �������Z�o
		m_dir = VSub(m_targetPos, m_pos);
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
		const VECTOR velecity = VScale(m_dir, m_collData.speed);
		// �ʒu��ς���
		m_pos = VAdd(m_pos, velecity);

		// �����𑪂�
		const float nowPosToNextPosX = static_cast<int>(sqrt(pow(m_pos.x - m_targetPos.x, 2) + pow(m_pos.x - m_targetPos.x, 2)));
		const float nowPosToNextPosZ = static_cast<int>(sqrt(pow(m_pos.z - m_targetPos.z, 2) + pow(m_pos.z - m_targetPos.z, 2)));

		// �ړ��܂ł̋������Z����
		if (nowPosToNextPosX < kRange &&
			nowPosToNextPosZ < kRange)
		{
			m_isNextMove = true;
		}

		// ���f���̉�]�s����v�Z���Đݒ�
		VECTOR dir2 = VSub(m_targetPos, m_pos);
		const float angle2 = atan2f(m_dir.x, m_dir.z) + -90.0f * DX_PI_F / 180.0f;
		MV1SetRotationXYZ(m_hModel, VGet(0.0f, angle2, 0.0f));
		m_moveCount = 0;
	}
	else
	{
		m_moveCount++;
	}


	if (m_moveCount > 30)
	{
		m_moveCount = 30;
		Attack();
	}

	// 3D���W����2D���W�ɕϊ�
	m_screenPos = ConvWorldPosToScreenPos(m_pos);

}
