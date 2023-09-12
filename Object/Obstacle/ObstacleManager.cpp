#include "ObstacleManager.h"
#include "../../Object/Obstacle/ObstacleNormalShot.h"

ObstacleManager::ObstacleManager():
	m_countCreate(-1)
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

void ObstacleManager::Create(VECTOR pos,int no)
{
	m_countCreate++;
	m_pNormalObstacle.push_back(std::make_shared<ObstacleNormalShot>(pos, no));
	m_pNormalObstacle[m_countCreate]->Init();
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

// オブジェクトの数を返す
int ObstacleManager::GetNum()
{
	return static_cast<int>(m_pNormalObstacle.size());
}

// ショットの数を返します
int ObstacleManager::GetShotNum(int objNum)
{
	return m_pNormalObstacle[objNum]->GetShotNum();
}

// ショットのデータを受け取る
CollData ObstacleManager::GetCollShotDatas(int objNum,int shotNum)
{
	return m_pNormalObstacle[objNum]->GetCollShotDatas(shotNum);
}

void ObstacleManager::SetCollEnemyDatas(std::vector<CollData> collEnemyData)
{
	for (auto& normalObstacle : m_pNormalObstacle)
	{
		normalObstacle->SetCollEnemyDatas(collEnemyData);
	}
}

void ObstacleManager::SetEraseShotData(std::vector<CollData> eraseShotData)
{
	for (auto& normalObstacle : m_pNormalObstacle)
	{
		normalObstacle->SetEraseShotData(eraseShotData);
	}
}

// 必要のないショット番号を受け取る
void ObstacleManager::SetShotErase(int objNum,int shotNum, bool erase)
{
	m_pNormalObstacle[objNum]->SetShotErase(shotNum, erase);
}
