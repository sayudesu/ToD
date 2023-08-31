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
	// マップチップサイズ
	const int mapChipMaxZ = 13;// 行
	const int mapChipMaxX = 25;// 列
	// マップチップナンバー(敵の道)
	
	// ブロック1つの大きさ
	const float block = 50.0f;
	VECTOR pos{};
	pos.y = 50.0f;

	int forX = 0;
	int forZ = 0;
	int tempZ = 0;
	int tempX = 0;
	// 行
	for (int z = 0; z < mapChipMaxZ; ++z)
	{
		// 配列の制御
		tempZ = z;
		if (z >= mapChipMaxZ) { tempZ = mapChipMaxZ; }
		if (z <= 0) { tempZ = 0; }
		// 列
		for (int x = 0; x < mapChipMaxX; ++x)
		{
			// 配列の制御
			tempX = x;
			if (x >= mapChipMaxX) { tempX = mapChipMaxX; }
			if (x <= 0) { tempX = 0; }
			// [現在の列 + 現在の列 * チップ最大列]
			if (m_mapChip[x + z * mapChipMaxX] == 3)
			{
				forX = tempX;
				forZ = tempZ;
				//// 敵の位置に代入
				pos.x = (forX * block);
				pos.z = (forZ * block);
				break;
			}
		}
	}

	m_count++;
	m_pEnemyNormal.push_back(std::make_shared<EnemyNormal>());
	m_pEnemyNormal[m_count]->Init(pos, forX, forZ);
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

VECTOR EnemyManager::SetNormalPos2(int num)
{
	return m_pEnemyNormal[num]->SetPos();
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

int EnemyManager::GetNormalNum()
{
	return m_pEnemyNormal.size();
}
