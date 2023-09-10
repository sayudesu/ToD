#include "EnemyManager.h"
#include "EnemyNormal.h"

EnemyManager::EnemyManager() :
	m_countCreate(-1)
{
}

EnemyManager::~EnemyManager()
{
}

// 敵の初期化
void EnemyManager::Init()
{
	
}

// 敵のエンド処理
void EnemyManager::End()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->End();
	}
}

// 敵の初期設定
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

	m_countCreate++;
	m_pEnemyNormal.push_back(std::make_shared<EnemyNormal>());
	m_pEnemyNormal[m_countCreate]->Init(pos, forX, forZ);
}

// 敵の更新処理
void EnemyManager::Update()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->Update();
	}
}

// 敵の描画
void EnemyManager::Draw()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->Draw();
	}
}

void EnemyManager::DrawUI()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->DrawUI();
	}
}

// 番号を指定してノーマルエネミーの位置を受け取ります
VECTOR EnemyManager::SetNormalPos(int num)
{
	return m_pEnemyNormal[num]->GetPos();
}

// ノーマルエネミーの数を返します
int EnemyManager::GetNormalNum()
{
	return static_cast<int>(m_pEnemyNormal.size());
}

// マップチップの情報を受け取ります
void EnemyManager::SetMapChip(std::vector<int> mapChip)
{
	for (auto& normalEnemy : m_pEnemyNormal)
	{
		normalEnemy->SetRoadPos(mapChip);
	}

	m_mapChip = mapChip;
}

// プレイヤーが設置したオブジェクトの判定データーを受け取ります
void EnemyManager::SetObjCollData(std::vector<CollData> collData)
{
	for (auto& normalEnemy : m_pEnemyNormal)
	{
		normalEnemy->SetCollData(collData);
	}
}

// 自身の判定用データ
std::vector<CollData> EnemyManager::GetCollData()
{
	std::vector<CollData> collData;

	for (auto& normalEnemy : m_pEnemyNormal)
	{
		collData.push_back(normalEnemy->GetCollDatas());
	}

	return collData;
}
