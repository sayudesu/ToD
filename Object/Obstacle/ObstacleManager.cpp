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

void ObstacleManager::Create(VECTOR pos,int obsNo,int no)
{
	if (obsNo == ObstructSelectNo::NORMAL_RESULT)
	{
		// �C���X�^���X�̍쐬
//		m_pNormalObstacle.push_back(new ObstacleCannon(pos, no));
		m_pObstacle.push_back(new ObstacleHomingMissile(pos, no));
		// ������
		m_pObstacle.back()->Init();
	}
	if (obsNo == ObstructSelectNo::HRAVY_RESULT)
	{
		// �C���X�^���X�̍쐬
		m_pObstacle.push_back(new ObstacleCrossbow(pos, no));
		// ������
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

// �I�u�W�F�N�g�̐���Ԃ�
int ObstacleManager::GetNum()
{
	return static_cast<int>(m_pObstacle.size());
}

// �V���b�g�̐���Ԃ��܂�
int ObstacleManager::GetShotNum(int objNum)
{
	return m_pObstacle[objNum]->GetShotNum();
}

// �V���b�g�̃f�[�^���󂯎��
ObjectData ObstacleManager::GetCollShotDatas(int objNum,int shotNum)
{
	return m_pObstacle[objNum]->GetCollShotDatas(shotNum);
}

// �G�̔���p�f�[�^���󂯎��
void ObstacleManager::SetCollEnemyDatas(std::vector<ObjectData> collEnemyData)
{
	for (auto& normalObstacle : m_pObstacle)
	{
		normalObstacle->SetCollEnemyDatas(collEnemyData);
	}

	//if (m_pObstacle.size() != 0)
	//{
	//	for (int i = 0; i < m_pObstacle.size()-1; i++)
	//	{
	//		m_pObstacle[i]->SetTarGetPos(collEnemyData[i].pos);
	//	}
	//}
}
// �K�v�̖���shot�̔ԍ����󂯎��
void ObstacleManager::SetEraseShotData(std::vector<ObjectData> eraseShotData)
{
	for (auto& normalObstacle : m_pObstacle)
	{
		normalObstacle->SetEraseShotData(eraseShotData);
	}
}

// �K�v�̂Ȃ��V���b�g�ԍ����󂯎��
void ObstacleManager::SetShotErase(int objNum,int shotNum, bool erase)
{
	m_pObstacle[objNum]->SetShotErase(shotNum, erase);
}
