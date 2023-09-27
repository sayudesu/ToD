#include "EnemyManager.h"
#include "EnemyMouse.h"
#include "EnemyMouseSpeed.h"
#include "EnemyMouseBig.h"

namespace
{
	// 通常のスポーンスピード
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

// 初期化
void EnemyManager::Init()
{
	
}

// メモリ解放
void EnemyManager::End()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->End();
		delete m_pEnemy[i];
		m_pEnemy[i] = nullptr;
	}
}

// 敵の初期設定
void EnemyManager::Create()
{
	VECTOR pos{};
	int forX = 0;
	int forZ = 0;
	int tempZ = 0;
	int tempX = 0;
	// 行
	for (int z = 0; z < m_mapChip.chipMaxZ; ++z)
	{
		// 配列の制御
		tempZ = z;
		if (z >= m_mapChip.chipMaxZ) { tempZ = m_mapChip.chipMaxZ; }
		if (z <= 0) { tempZ = 0; }
		// 列
		for (int x = 0; x < m_mapChip.chipMaxX; ++x)
		{
			// 配列の制御
			tempX = x;
			if (x >= m_mapChip.chipMaxX) { tempX = m_mapChip.chipMaxX; }
			if (x <= 0) { tempX = 0; }
			// [現在の列 + 現在の列 * チップ最大列]
			if (m_mapChip.data[x + z * m_mapChip.chipMaxX] == m_mapChip.enemySpawner)
			{
				forX = tempX;
				forZ = tempZ;
				//// 敵の位置に代入
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

	// 通常のバランス
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

// 敵の更新処理
void EnemyManager::Update()
{
	for (auto& enemyNormal : m_pEnemy)
	{
		enemyNormal->Update();
	}

	// 必要のないオブジェクトを削除
	EraseObject();
}

// 描画
void EnemyManager::Draw()
{
	for (auto& enemyNormal : m_pEnemy)
	{
		enemyNormal->Draw();
	}
}

// 2Dでの描画
void EnemyManager::DrawUI()
{
	for (auto& enemyNormal : m_pEnemy)
	{
		enemyNormal->DrawUI();
	}
}

// 番号を指定してノーマルエネミーの位置を受け取ります
VECTOR EnemyManager::SetNormalPos(int num)
{
	return m_pEnemy[num]->GetPos();
}

// ノーマルエネミーの数を返します
int EnemyManager::GetNormalNum()
{
	return static_cast<int>(m_pEnemy.size());
}

// マップチップの情報を受け取ります
void EnemyManager::SetMapChip(MapDatas mapChip)
{
	for (auto& normalEnemy : m_pEnemy)
	{
		normalEnemy->SetRoadPos(mapChip);
	}

	m_mapChip = mapChip;
}

// プレイヤーが設置したオブジェクトの判定データーを受け取ります
void EnemyManager::SetObjCollData(std::vector<ObjectData> collData)
{
	for (auto& normalEnemy : m_pEnemy)
	{
		normalEnemy->SetCollData(collData);
	}
}

// 自身の判定用データ
std::vector<ObjectData> EnemyManager::GetCollData()
{
	std::vector<ObjectData> collData;

	for (auto& normalEnemy : m_pEnemy)
	{
		collData.push_back(normalEnemy->GetCollDatas());
	}

	return collData;
}

// 受けるダメージを受け取る
void EnemyManager::SetHitDamage(int enemyNo, int damage)
{
	m_pEnemy[enemyNo]->SetHitDamage(damage);
}

// 必要のないオブジェクトを削除する
void EnemyManager::EraseObject()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i]->GetErase())
		{
			// メモリ解放
			m_pEnemy[i]->End();
			// デリート処理
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
			// 要素の削除
			m_pEnemy.erase(m_pEnemy.begin() + i);
			// メモリサイズの解放
			m_pEnemy.shrink_to_fit();
		}
	}
}
