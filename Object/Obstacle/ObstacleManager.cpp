#include "ObstacleManager.h"
#include "../../Object/Obstacle/ObstacleNormalShot.h"

ObstacleManager::ObstacleManager()
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
	for (int i = 0; i < m_pNormalObstacle.size(); i++)
	{
		m_pNormalObstacle[i]->End();
		delete m_pNormalObstacle[i];
		m_pNormalObstacle[i] = nullptr;
	} 
}

void ObstacleManager::Create(VECTOR pos,int no)
{
	// インスタンスの作成
	m_pNormalObstacle.push_back(new ObstacleNormalShot(pos, no));
	// 初期化
	m_pNormalObstacle.back()->Init();
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

// 敵の判定用データを受け取る
void ObstacleManager::SetCollEnemyDatas(std::vector<CollData> collEnemyData)
{
	for (auto& normalObstacle : m_pNormalObstacle)
	{
		normalObstacle->SetCollEnemyDatas(collEnemyData);
	}
}
// 必要の無いshotの番号を受け取る
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
