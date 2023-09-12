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
	// �C���X�^���X�̍쐬
	m_pNormalObstacle.push_back(new ObstacleNormalShot(pos, no));
	// ������
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

// �I�u�W�F�N�g�̐���Ԃ�
int ObstacleManager::GetNum()
{
	return static_cast<int>(m_pNormalObstacle.size());
}

// �V���b�g�̐���Ԃ��܂�
int ObstacleManager::GetShotNum(int objNum)
{
	return m_pNormalObstacle[objNum]->GetShotNum();
}

// �V���b�g�̃f�[�^���󂯎��
CollData ObstacleManager::GetCollShotDatas(int objNum,int shotNum)
{
	return m_pNormalObstacle[objNum]->GetCollShotDatas(shotNum);
}

// �G�̔���p�f�[�^���󂯎��
void ObstacleManager::SetCollEnemyDatas(std::vector<CollData> collEnemyData)
{
	for (auto& normalObstacle : m_pNormalObstacle)
	{
		normalObstacle->SetCollEnemyDatas(collEnemyData);
	}
}
// �K�v�̖���shot�̔ԍ����󂯎��
void ObstacleManager::SetEraseShotData(std::vector<CollData> eraseShotData)
{
	for (auto& normalObstacle : m_pNormalObstacle)
	{
		normalObstacle->SetEraseShotData(eraseShotData);
	}
}

// �K�v�̂Ȃ��V���b�g�ԍ����󂯎��
void ObstacleManager::SetShotErase(int objNum,int shotNum, bool erase)
{
	m_pNormalObstacle[objNum]->SetShotErase(shotNum, erase);
}
