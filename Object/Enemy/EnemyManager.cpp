#include "EnemyManager.h"
#include "EnemyMouse.h"
#include "EnemyMouseSpeed.h"
#include "EnemyMouseBig.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

// ������
void EnemyManager::Init()
{
	
}

// ���������
void EnemyManager::End()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i]->End();
		delete m_pEnemy[i];
		m_pEnemy[i] = nullptr;
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
	static int count = 0;
	count++;
	if (count == 1)
	{
		m_pEnemy.push_back(new EnemyMouse());
		m_pEnemy.back()->Init(pos, forX, forZ);
	}

	if(count == 2)
	{
		m_pEnemy.push_back(new EnemyMouseSpeed());
		m_pEnemy.back()->Init(pos, forX, forZ);
	}

	if (count == 3)
	{
		m_pEnemy.push_back(new EnemyMouseBig());
		m_pEnemy.back()->Init(pos, forX, forZ);
		count = 0;
	}
}

// �G�̍X�V����
void EnemyManager::Update()
{
	for (auto& enemyNormal : m_pEnemy)
	{
		enemyNormal->Update();
	}

	EraseObject();
}

// �`��
void EnemyManager::Draw()
{
	for (auto& enemyNormal : m_pEnemy)
	{
		enemyNormal->Draw();
	}
}

// 2D�ł̕`��
void EnemyManager::DrawUI()
{
	for (auto& enemyNormal : m_pEnemy)
	{
		enemyNormal->DrawUI();
	}
}

// �ԍ����w�肵�ăm�[�}���G�l�~�[�̈ʒu���󂯎��܂�
VECTOR EnemyManager::SetNormalPos(int num)
{
	return m_pEnemy[num]->GetPos();
}

// �m�[�}���G�l�~�[�̐���Ԃ��܂�
int EnemyManager::GetNormalNum()
{
	return static_cast<int>(m_pEnemy.size());
}

// �}�b�v�`�b�v�̏����󂯎��܂�
void EnemyManager::SetMapChip(std::vector<int> mapChip)
{
	for (auto& normalEnemy : m_pEnemy)
	{
		normalEnemy->SetRoadPos(mapChip);
	}

	m_mapChip = mapChip;
}

// �v���C���[���ݒu�����I�u�W�F�N�g�̔���f�[�^�[���󂯎��܂�
void EnemyManager::SetObjCollData(std::vector<ObjectData> collData)
{
	for (auto& normalEnemy : m_pEnemy)
	{
		normalEnemy->SetCollData(collData);
	}
}

// ���g�̔���p�f�[�^
std::vector<ObjectData> EnemyManager::GetCollData()
{
	std::vector<ObjectData> collData;

	for (auto& normalEnemy : m_pEnemy)
	{
		collData.push_back(normalEnemy->GetCollDatas());
	}

	return collData;
}

// �󂯂�_���[�W���󂯎��
void EnemyManager::SetHitDamage(int enemyNo, int damage)
{
	m_pEnemy[enemyNo]->SetHitDamage(damage);
}

// �K�v�̂Ȃ��I�u�W�F�N�g���폜����
void EnemyManager::EraseObject()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i]->GetErase())
		{
			// ���������
			m_pEnemy[i]->End();
			// �f���[�g����
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
			// �v�f�̍폜
			m_pEnemy.erase(m_pEnemy.begin() + i);
			// �������T�C�Y�̉��
			m_pEnemy.shrink_to_fit();
		}
	}
}
