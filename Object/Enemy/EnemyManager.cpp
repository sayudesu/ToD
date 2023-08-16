#include "EnemyManager.h"
#include "EnemyNormal.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->Init();
	}
}

void EnemyManager::End()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->End();
	}
}

void EnemyManager::Create(int num)
{
	for (int i = 0; i < num; i++)
	{
		m_pEnemyNormal.push_back(std::make_shared<EnemyNormal>());
		m_pEnemyNormal[i]->Init();
	}
}

void EnemyManager::Update()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->Update();
	}

	// �}�b�v�`�b�v�T�C�Y
	const int mapChipMaxZ = 26;
	const int mapChipMaxX = 13;
	// �}�b�v�`�b�v�i���o�[(�G�̓�)
	const int enemyRoad = 2;
	// �u���b�N1�̑傫��
	const float block = 50.0f;

	for (int z = 0; z < mapChipMaxZ; ++z)
	{
		for (int x = 0; x < mapChipMaxX; ++x)
		{
			if (m_mapChip[x + z * mapChipMaxZ] == enemyRoad)
			{
				// �G�̈ʒu�ɑ��
				m_pos.x = x * block;
				m_pos.z = z * block;
			}

		}
	}

	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->GetPos()
	}
}

void EnemyManager::Draw()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->Draw();
	}
}

VECTOR EnemyManager::SetNormalPos(int num)
{
	for (int i = 0; i < num; i++)
	{
		return m_pEnemyNormal[i]->SetPos();
	}
}

int EnemyManager::SetNormalNum()
{
	for (auto& size : m_pEnemyNormal)
	{
		return m_pEnemyNormal.size();
	}
}

void EnemyManager::SetMapChip(std::vector<int> mapChip)
{
	for (auto& normalEnemy : m_pEnemyNormal)
	{
		normalEnemy->SetRoadPos(mapChip);
	}

	m_mapChip = mapChip;
}
