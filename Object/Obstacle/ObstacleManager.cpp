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

// �񎟌��z����ꎟ���z��ɂ��Ă�Ԃ�
std::vector<CollData> ObstacleManager::GetCollDatas()
{
	// �ꎞ�I�Ɋi�[����p�̔z���p�ӂ���
	std::vector < std::vector<CollData>> tempArray2D{};
	std::vector<CollData> tempArray{};

	// �񎟌��z��Ńf�[�^���󂯎��
	for (auto& nomalObstacle : m_pNormalObstacle)
	{
		tempArray2D.push_back(nomalObstacle->GetCollDatas());
	}

	// �I�u�W�F�N�g�̐�
	for (int i = 0; i < m_pNormalObstacle.size(); i++)
	{
		// �V���b�g�̐�
		for (int j = 0; j < m_pNormalObstacle[i]->SetShotNum(); j++)
		{
			// �ꎟ���z��ɂ��ăf�[�^���󂯎��
			tempArray.push_back(tempArray2D[i][j]);
		}
	}

	// �ꎟ���z��Ńf�[�^��n��
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
