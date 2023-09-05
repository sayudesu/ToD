#include "ObstacleManager.h"
#include "../../Object/Obstacle/ObstacleNormalShot.h"

ObstacleManager::ObstacleManager():
	m_count(-1)
{
}

ObstacleManager::~ObstacleManager()
{

}

void ObstacleManager::Init()
{
}

void ObstacleManager::End()
{
}

void ObstacleManager::Create(VECTOR pos)
{
	m_count++;
	m_pNormalObstacle.push_back(std::make_shared<ObstacleNormalShot>(pos));
	m_pNormalObstacle[m_count]->Init();
}

void ObstacleManager::Update()
{
	for (auto& nomalObstacle : m_pNormalObstacle)
	{
		nomalObstacle->Update();
	}
}

void ObstacleManager::Draw()
{
	for (auto& nomalObstacle : m_pNormalObstacle)
	{
		nomalObstacle->Draw();
	}
}

VECTOR ObstacleManager::GetPos(int num)
{
	return m_pNormalObstacle[num]->GetPos();
}

// 二次元配列を一次元配列にしてを返す
std::vector<CollData> ObstacleManager::GetCollDatas()
{
	// 一時的に格納する用の配列を用意する
	std::vector < std::vector<CollData>> tempArray2D{};
	std::vector<CollData> tempArray{};

	// 二次元配列でデータを受け取る
	for (auto& nomalObstacle : m_pNormalObstacle)
	{
		tempArray2D.push_back(nomalObstacle->GetCollDatas());
	}

	// オブジェクトの数
	for (int i = 0; i < m_pNormalObstacle.size(); i++)
	{
		// ショットの数
		for (int j = 0; j < m_pNormalObstacle[i]->SetShotNum(); j++)
		{
			// 一次元配列にしてデータを受け取る
			tempArray.push_back(tempArray2D[i][j]);
		}
	}

	// 一次元配列でデータを渡す
	return tempArray;
}

void ObstacleManager::SetCollEnemyDatas(std::vector<CollData> collEnemyData)
{
	for (auto& normalObstacle : m_pNormalObstacle)
	{
		normalObstacle->SetCollEnemyDatas(collEnemyData);
	}
}

int ObstacleManager::GetNormalNum()
{
	return static_cast<int>(m_pNormalObstacle.size());
}
