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
	//	// �J�E���g
	//	puls++;
	//	// �E�ɉ����l�߂�
	//	int x = -600;
	//	x += (puls * 50);

	//	// Z���ύX
	//	if (m_mapChip[i] == 0)
	//	{
	//		puls = -1;
	//		z -= 50;
	//	}

	//	// �����ʒu
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
	// �}�b�v�`�b�v�T�C�Y
	const int mapChipMaxZ = 13;// �s
	const int mapChipMaxX = 25;// ��
	// �}�b�v�`�b�v�i���o�[(�G�̓�)
	
	// �u���b�N1�̑傫��
	const float block = 50.0f;
	VECTOR pos{};
	pos.y = 50.0f;

	int forX = 0;
	int forZ = 0;
	int tempZ = 0;
	int tempX = 0;
	// �s
	for (int z = 0; z < mapChipMaxZ; ++z)
	{
		// �z��̐���
		tempZ = z;
		if (z >= mapChipMaxZ) { tempZ = mapChipMaxZ; }
		if (z <= 0) { tempZ = 0; }
		// ��
		for (int x = 0; x < mapChipMaxX; ++x)
		{
			// �z��̐���
			tempX = x;
			if (x >= mapChipMaxX) { tempX = mapChipMaxX; }
			if (x <= 0) { tempX = 0; }
			// [���݂̗� + ���݂̗� * �`�b�v�ő��]
			if (m_mapChip[x + z * mapChipMaxX] == 3)
			{
				forX = tempX;
				forZ = tempZ;
				//// �G�̈ʒu�ɑ��
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
