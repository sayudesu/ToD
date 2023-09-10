#include "EnemyManager.h"
#include "EnemyNormal.h"

EnemyManager::EnemyManager() :
	m_countCreate(-1)
{
}

EnemyManager::~EnemyManager()
{
}

// �G�̏�����
void EnemyManager::Init()
{
	
}

// �G�̃G���h����
void EnemyManager::End()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->End();
	}
}

// �G�̏����ݒ�
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

	m_countCreate++;
	m_pEnemyNormal.push_back(std::make_shared<EnemyNormal>());
	m_pEnemyNormal[m_countCreate]->Init(pos, forX, forZ);
}

// �G�̍X�V����
void EnemyManager::Update()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->Update();
	}
}

// �G�̕`��
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

// �ԍ����w�肵�ăm�[�}���G�l�~�[�̈ʒu���󂯎��܂�
VECTOR EnemyManager::SetNormalPos(int num)
{
	return m_pEnemyNormal[num]->GetPos();
}

// �m�[�}���G�l�~�[�̐���Ԃ��܂�
int EnemyManager::GetNormalNum()
{
	return static_cast<int>(m_pEnemyNormal.size());
}

// �}�b�v�`�b�v�̏����󂯎��܂�
void EnemyManager::SetMapChip(std::vector<int> mapChip)
{
	for (auto& normalEnemy : m_pEnemyNormal)
	{
		normalEnemy->SetRoadPos(mapChip);
	}

	m_mapChip = mapChip;
}

// �v���C���[���ݒu�����I�u�W�F�N�g�̔���f�[�^�[���󂯎��܂�
void EnemyManager::SetObjCollData(std::vector<CollData> collData)
{
	for (auto& normalEnemy : m_pEnemyNormal)
	{
		normalEnemy->SetCollData(collData);
	}
}

// ���g�̔���p�f�[�^
std::vector<CollData> EnemyManager::GetCollData()
{
	std::vector<CollData> collData;

	for (auto& normalEnemy : m_pEnemyNormal)
	{
		collData.push_back(normalEnemy->GetCollDatas());
	}

	return collData;
}
