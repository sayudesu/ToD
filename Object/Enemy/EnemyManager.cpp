#include "EnemyManager.h"
#include "EnemyNormal.h"

EnemyManager::EnemyManager() :
	m_count(-1)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	//VECTOR pos = VGet(0, 0, 0);
	//int z = 250;
	//int puls = -1;

	//for (int i = 0; i < m_mapChip.size(); i++)
	//{
	//	// カウント
	//	puls++;
	//	// 右に押し詰める
	//	int x = -600;
	//	x += (puls * 50);

	//	// Z軸変更
	//	if (m_mapChip[i] == 0)
	//	{
	//		puls = -1;
	//		z -= 50;
	//	}

	//	// 初期位置
	//	if (m_mapChip[i] == 3)
	//	{
	//		pos = VGet(x, 0.0f, z);
	//	}
	//}

	//for (auto& enemyNormal : m_pEnemyNormal)
	//{
	//	enemyNormal->Init(pos);
	//}
}

void EnemyManager::End()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->End();
	}
}

void EnemyManager::Create()
{
	VECTOR pos = VGet(0, 0, 0);
	int z = 250;
	int puls = -1;

	for (int i = 0; i < m_mapChip.size(); i++)
	{
		// カウント
		puls++;
		// 右に押し詰める
		int x = -600;
		x += (puls * 50);

		// Z軸変更
		if (m_mapChip[i] == 0)
		{
			puls = -1;
			z -= 50;
		}

		// 初期位置
		if (m_mapChip[i] == 3)
		{
			pos = VGet(x, 0.0f, z);
		}
	}

	m_count++;
	m_pEnemyNormal.push_back(std::make_shared<EnemyNormal>());
	m_pEnemyNormal[m_count]->Init(pos);
}

void EnemyManager::Update()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->Update();
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
