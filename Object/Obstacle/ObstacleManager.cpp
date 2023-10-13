#include "ObstacleManager.h"
#include "../../Object/Obstacle/ObstacleCannon.h"
#include "../../Object/Obstacle/ObstacleCrossbow.h"
#include "../../Object/Obstacle/ObstacleHomingMissile.h"
#include "../../Util/ObstructSelectNo.h"


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
	for (int i = 0; i < m_pObstacle.size(); i++)
	{
		m_pObstacle[i]->End();
		delete m_pObstacle[i];
		m_pObstacle[i] = nullptr;
	} 
}

// 選択したオブジェクトを生成
void ObstacleManager::Create(VECTOR pos,int obsNo,int no,int mapCihpX, int mapCihpY)
{
	if (obsNo == ObstructSelectNo::NORMAL_RESULT)
	{
		m_pObstacle.push_back(new ObstacleCannon(pos, no, mapCihpX, mapCihpY));
		m_pObstacle.back()->Init();
	}
	if (obsNo == ObstructSelectNo::HRAVY_RESULT)
	{
		m_pObstacle.push_back(new ObstacleCrossbow(pos, no, mapCihpX, mapCihpY));
		m_pObstacle.back()->Init();
	}
	if (obsNo == ObstructSelectNo::MISSILE_RESULT)
	{
		m_pObstacle.push_back(new ObstacleHomingMissile(pos, no, mapCihpX, mapCihpY));
		m_pObstacle.back()->Init();
	}

}

void ObstacleManager::Update()
{
	for (auto& nomalObstacle : m_pObstacle)
	{
		nomalObstacle->Update();
	}
}

void ObstacleManager::Draw()
{
	for (auto& nomalObstacle : m_pObstacle)
	{
		nomalObstacle->Draw();
	}
}

// オブジェクトの数を返す
int ObstacleManager::GetNum()
{
	return static_cast<int>(m_pObstacle.size());
}

// ショットの数を返します
int ObstacleManager::GetShotNum(int objNum)
{
	return m_pObstacle[objNum]->GetShotNum();
}

// ショットのデータを受け取る
ObjectData ObstacleManager::GetCollShotDatas(int objNum,int shotNum)
{
	return m_pObstacle[objNum]->GetCollShotDatas(shotNum);
}

// 敵の判定用データを受け取る
void ObstacleManager::SetCollEnemyDatas(std::vector<ObjectData> collEnemyData)
{
	for (auto& normalObstacle : m_pObstacle)
	{
		normalObstacle->SetCollEnemyDatas(collEnemyData);
	}
}
// 必要の無いshotの番号を受け取る
void ObstacleManager::SetEraseShotData(std::vector<ObjectData> eraseShotData)
{
	for (auto& normalObstacle : m_pObstacle)
	{
		normalObstacle->SetEraseShotData(eraseShotData);
	}
}

// 必要のないショット番号を受け取る
void ObstacleManager::SetShotErase(int objNum,int shotNum, bool erase)
{
	m_pObstacle[objNum]->SetShotErase(shotNum, erase);
}

void ObstacleManager::SetPowerUpPos(ObstructSelectNo no, int mapChipX, int mapChipY)
{
	for (auto& obj : m_pObstacle)
	{
		obj->SetPowerUpPos(no,mapChipX, mapChipY);
	}
}
