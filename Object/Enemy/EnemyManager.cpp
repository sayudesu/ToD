#include "EnemyManager.h"
#include "EnemyMouse.h"
#include "EnemyMouseSpeed.h"
#include "EnemyMouseBig.h"

namespace
{
	// �ʏ�̃X�|�[���X�s�[�h
	constexpr int kMouseSpawnFrame = 60 * 2;
	//
	constexpr int kMouseSpeedSpawnFrame = 60 * 5;
	//
	constexpr int kMouseBigSpawnFrame = 60 * 10;
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

// ������
void EnemyManager::Init()
{
	
}

// ���������
void EnemyManager::End()
{
	for (auto& enemy : m_pEnemy)
	{
		enemy->End();
		delete enemy;
		if (enemy != nullptr)
		{
			enemy = nullptr;
		}
	}
}

// �G�̏����ݒ�
void EnemyManager::Create()
{
	VECTOR pos{};
	int forX = 0;
	int forZ = 0;
	int tempZ = 0;
	int tempX = 0;
	// �s
	for (int z = 0; z < m_mapChip.chipMaxZ; ++z)
	{
		// �z��̐���
		tempZ = z;
		if (z >= m_mapChip.chipMaxZ) { tempZ = m_mapChip.chipMaxZ; }
		if (z <= 0) { tempZ = 0; }
		// ��
		for (int x = 0; x < m_mapChip.chipMaxX; ++x)
		{
			// �z��̐���
			tempX = x;
			if (x >= m_mapChip.chipMaxX) { tempX = m_mapChip.chipMaxX; }
			if (x <= 0) { tempX = 0; }
			// [���݂̗� + ���݂̗� * �`�b�v�ő��]
			if (m_mapChip.data[x + z * m_mapChip.chipMaxX] == m_mapChip.enemySpawner)
			{
				forX = tempX;
				forZ = tempZ;
				//// �G�̈ʒu�ɑ��
				pos.x = (forX * m_mapChip.blockSizeY);
				pos.z = (forZ * m_mapChip.blockSizeZ);
				break;
			}
		}
	}

	static int countN = 0;
	static int countS = 0;
	static int countB = 0;
	countN++;
	countS++;
	countB++;

	// �ʏ�̃o�����X
	if(countN == kMouseSpawnFrame)
	{
		m_pEnemy.push_back(new EnemyMouse());
		m_pEnemy.back()->Init(pos, forX, forZ);

		countN = 0;
	}

	// 
	if(countS == kMouseSpeedSpawnFrame)
	{
		m_pEnemy.push_back(new EnemyMouseSpeed());
		m_pEnemy.back()->Init(pos, forX, forZ);
		countS = 0;
	}

	// 
	if (countB == kMouseBigSpawnFrame)
	{
		m_pEnemy.push_back(new EnemyMouseBig());
		m_pEnemy.back()->Init(pos, forX, forZ);
		countB = 0;
	}
}

// �G�̍X�V����
void EnemyManager::Update()
{
	for (auto& enemyNormal : m_pEnemy)
	{
		enemyNormal->Update();
	}

	// �K�v�̂Ȃ��I�u�W�F�N�g���폜
	EraseObject();
}

// �`��
void EnemyManager::Draw()
{
	for (auto& enemyNormal : m_pEnemy)
	{
		enemyNormal->Draw();
	}
}

// 2D�ł̕`��
void EnemyManager::DrawUI()
{
	for (auto& enemyNormal : m_pEnemy)
	{
		enemyNormal->DrawUI();
	}
}

// �ԍ����w�肵�ăm�[�}���G�l�~�[�̈ʒu���󂯎��܂�
VECTOR EnemyManager::SetNormalPos(int num)
{
	std::list<EnemyBase*>::iterator it = m_pEnemy.begin();
	std::advance(it, num);

	return (*it)->GetPos();
}

// �m�[�}���G�l�~�[�̐���Ԃ��܂�
int EnemyManager::GetNormalNum()
{
	return static_cast<int>(m_pEnemy.size());
}

// �}�b�v�`�b�v�̏����󂯎��܂�
void EnemyManager::SetMapChip(MapDatas mapChip)
{
	for (auto& normalEnemy : m_pEnemy)
	{
		normalEnemy->SetRoadPos(mapChip);
	}

	m_mapChip = mapChip;
}

// �v���C���[���ݒu�����I�u�W�F�N�g�̔���f�[�^�[���󂯎��܂�
void EnemyManager::SetObjCollData(std::vector<ObjectData> collData)
{
	for (auto& normalEnemy : m_pEnemy)
	{
		normalEnemy->SetCollData(collData);
	}
}

// ���g�̔���p�f�[�^
std::vector<ObjectData> EnemyManager::GetCollData()
{
	std::vector<ObjectData> collData;

	for (auto& normalEnemy : m_pEnemy)
	{
		collData.push_back(normalEnemy->GetCollDatas());
	}

	return collData;
}

// �󂯂�_���[�W���󂯎��
void EnemyManager::SetHitDamage(int enemyNo, int damage)
{
	std::list<EnemyBase*>::iterator it = m_pEnemy.begin();
	std::advance(it, enemyNo);
	(*it)->SetHitDamage(damage);
}

// �K�v�̂Ȃ��I�u�W�F�N�g���폜����
void EnemyManager::EraseObject()
{
	// HP�̂Ȃ��Ȃ����G�l�~�[�͂���Ȃ�
	// �������߂����A���ۂɂ͏����ĂȂ��āA������ɂ悯�Ă��邾��
	// �����ɍ��v�������̂�����
	// �Ώۂ�m_pEnemy�̍ŏ�����Ō�܂�
	// �����Ă��炤������\�������_��
	// false���Ə�����Btrue���Ə����Ȃ�
	auto rmIt = std::remove_if
	(m_pEnemy.begin(),
		m_pEnemy.end(),
		[](const EnemyBase* enemy)
		{
			return enemy->GetErase();
		});
	// �f���[�g����
	for (auto& enemy : m_pEnemy)
	{
		if (enemy != nullptr)
		{
			if (enemy->GetErase())
			{
				enemy->End();
				delete enemy;
				enemy = nullptr;
			}
		}
	}
	// �z��̍폜
	m_pEnemy.erase(rmIt, m_pEnemy.end());
}
