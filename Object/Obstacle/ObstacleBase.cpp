#include "ObstacleBase.h"
#include "../../Util/SoundFunctions.h"
#include "../../Object/Shot/NormalShot.h"
#include "../../Object/Shot/MissileShot.h"

#include <stack>

namespace
{
	// �ݒu���Ă���ł��o���܂ł̃t���[��
	constexpr int kShotFirstFrameMax = 60;

	// �V���b�g�̑ł��o�����x�����p
	constexpr int kShotSpeedChange = 2;
	constexpr float kShotDamageChange = 0.2f;

	// �I�u�W�F�N�g�̍U���͈�
	constexpr float kObjectAttackRadius = 300.0f;
}

ObstacleBase::ObstacleBase(VECTOR pos, int no, int mapCihpX, int mapCihpY)
{
	m_pos  = pos;
	m_myNo = no;
	m_shotData.shotFrameCount = 0;
	m_shotData.targetPos      = VGet(0,0,0);
	m_shotData.scale          = VGet(0, 0, 0);
	m_shotData.rotation       = VGet(0,0,0);
	m_shotData.radius         = 0.0f;
	m_shotData.damage         = 0.0f;
	m_shotData.speed          = 0.0f;
	m_shotData.isTracking     = false;

	m_mapCihpX = mapCihpX;
	m_mapCihpZ = mapCihpY;
}

void ObstacleBase::End()
{
	// ���f���̃f���[�g
	MV1DeleteModel(m_handle);
	MV1DeleteModel(m_shotData.handle);

	for (auto& shot : m_pShot)
	{
		shot->End();
		delete shot;
		if (shot != nullptr)
		{
			shot = nullptr;
		}
	}
}

void ObstacleBase::Update()
{
	(this->*m_updateFunc)();
}

void ObstacleBase::UpdateSetting()
{
	// �V���b�g�̑ł��o���܂ł̃t���[�����J�E���g����
	m_shotFirstDelayFrameCount++;
	if (m_shotFirstDelayFrameCount > kShotFirstFrameMax)
	{
		// �V���b�g�p�֐��Ɉړ�
		m_updateFunc = &ObstacleBase::UpdateShot;
		// �J�E���g���Z�b�g
		m_shotFirstDelayFrameCount = 0;
	}
}

void ObstacleBase::UpdateShot()
{
	m_shootFrameCount++;
	// �V���b�g���o���X�s�[�g

	if (m_shotData.id == 0)
	{
		if (m_shootFrameCount > m_shotData.shotFrameCount && (m_isShot))
		{
			m_countShotNum++;
			m_pShot.push_back(new NormalShot(VGet(m_pos.x, m_pos.y + 15.0f, m_pos.z), m_myNo, m_countShotNum));
			m_pShot.back()->Init(
				m_shotData.handle,
				m_shotData.shotFrameCount,
				m_shotData.targetPos,
				m_shotData.scale,
				m_shotData.rotation,
				m_shotData.radius,
				m_shotData.damage,
				m_shotData.speed,
				m_shotData.isTracking);

			m_shootFrameCount = 0;
		}
		m_countShotNum = 0;
	}
	if (m_shotData.id == 1)
	{
		if (m_shootFrameCount > m_shotData.shotFrameCount && (m_isShot))
		{
			for (int i = 0; i < 2; i++)
			{
				m_countShotNum++;
				m_pShot.push_back(new MissileShot(VGet(m_pos.x, m_pos.y + 15.0f, m_pos.z), m_myNo, m_countShotNum));
				m_pShot.back()->Init(
					m_shotData.handle,
					m_shotData.shotFrameCount,
					m_shotData.targetPos,
					m_shotData.scale,
					m_shotData.rotation,
					m_shotData.radius,
					m_shotData.damage,
					m_shotData.speed,
					m_shotData.isTracking);

				m_shootFrameCount = 0;
			}
		}
		m_countShotNum = 0;
	}


	for (auto& shot : m_pShot)
	{
		shot->Update();
		shot->SetTargetPos(m_shotData.targetPos);
	}

	TargetPos();

	// ���f���̉�]�s����v�Z���Đݒ�
	VECTOR dir2 = VSub(m_shotData.targetPos, m_pos);
	const float angle2 = atan2f(dir2.x, dir2.z) + -90.0f * DX_PI_F / 180.0f;
	MV1SetRotationXYZ(m_handle, VGet(0.0f, angle2, 0.0f));
	
	// �K���Ȕ͈͊O����
	for (auto& shot: m_pShot)
	{
		if (shot->GetCollData().pos.x < -1000.0f)
		{
			shot->SetEnabled(false);
		}
		if (shot->GetCollData().pos.x > 13000.0f)
		{
			shot->SetEnabled(false);
		}
		if (shot->GetCollData().pos.z < -1000.0f)
		{
			shot->SetEnabled(false);
		}
		if (shot->GetCollData().pos.z > 7000.0f)
		{
			shot->SetEnabled(false);
		}
		if (shot->GetCollData().pos.y < 0.0f)
		{
			shot->SetEnabled(false);
		}
	}

	// ��x�Փ˔��]���������V���b�g�͂���Ȃ�
	// �������߂����A���ۂɂ͏����ĂȂ��āA������ɂ悯�Ă��邾��
	// �����ɍ��v�������̂�����
	// �Ώۂ�m_pShot�̍ŏ�����Ō�܂�
	// �����Ă��炤������\�������_��
	// false���Ə�����Btrue���Ə����Ȃ�
	auto rmIt = std::remove_if        
	(m_pShot.begin(),			
		m_pShot.end(),			
		[](const ShotBase* shot)
		{
			return !shot->IsEnabled();
		});
	for (auto& shot : m_pShot)
	{
		if (shot != nullptr)
		{
			if (!shot->IsEnabled())
			{
				shot->End();
				delete shot;
				shot = nullptr;					
			}
		}
	}
	m_pShot.erase(rmIt, m_pShot.end());
}

// �N��_����
void ObstacleBase::TargetPos()
{
	m_isShot = false;
	// �����͌�ł��ꂢ�ɂ��܂��B
	// �G�̐���
	for (int i = 0; i < m_collEnemyData.size(); i++)
	{
		// �߂��G������
		const VECTOR toPlayer = VSub(m_pos, m_collEnemyData[i].pos);
		const float length = sqrtf((toPlayer.x * toPlayer.x) + (toPlayer.y * toPlayer.y) + (toPlayer.z * toPlayer.z));
		if (length < kObjectAttackRadius && isDead)
		{	
			no = i;
			isDead = false;
			m_isShot = true;
			printfDx("�͈͒�\n");
		}
	}
	for (int i = 0; i < m_collEnemyData.size(); i++)
	{
		// �߂��G������
		const VECTOR toPlayer = VSub(m_pos, m_collEnemyData[i].pos);
		const float length = sqrtf((toPlayer.x * toPlayer.x) + (toPlayer.y * toPlayer.y) + (toPlayer.z * toPlayer.z));
		if (length < kObjectAttackRadius)
		{
			// ���̔ԍ������݂���Ȃ�
			if (i == no)
			{
				printfDx("�^�[�Q�b�g�͈͒�\n");
				// �^�[�Q�b�g�w��
				m_shotData.targetPos = m_collEnemyData[i].pos;
				m_isShot = true;
				// �_���Ă���G�����񂾏ꍇ
				if (m_collEnemyData[i].isHit)
				{
					isDead = true;
				
				}
			}
		}
		else
		{
			isDead = true;
		}
	}
}

VECTOR ObstacleBase::GetPos() const
{
	return m_pos;
}

ObjectData ObstacleBase::GetCollShotDatas(int shotNum)
{
	std::list<ShotBase*>::iterator it = m_pShot.begin();
	std::advance(it, shotNum); 
	ObjectData objData = (*it)->GetCollData();
	return objData;	
}

void ObstacleBase::SetCollEnemyDatas(std::vector<ObjectData> collEnemyData)
{
	m_collEnemyData = collEnemyData;
}

int ObstacleBase::GetShotNum()
{
	return static_cast<int>(m_pShot.size());
}

void ObstacleBase::SetTarGetPos(VECTOR pos)
{
	for (auto& shot : m_pShot)
	{
		shot->SetTargetPos(pos);
	}
}

void ObstacleBase::SetShotErase(int shotNum, bool erase)
{
	std::list<ShotBase*>::iterator it = m_pShot.begin();
	std::advance(it, shotNum);
    (*it)->SetEnabled(erase);
}

void ObstacleBase::SetPowerUpPos(ObstructSelectNo objNo,int mapChipX, int mapChipZ)
{
	// ��������󂯎�����}�b�v�`�b�v���W�̈ʒu�ɃI�u�W�F�N�g���ݒu����Ă�����
	if ((m_mapCihpX == mapChipX) && (m_mapCihpZ == mapChipZ))
	{
		if (objNo == ObstructSelectNo::SPEED_RESULT)
		{
			// �V���b�g�̍đł��o���J�n���x�𑁂�����
			m_shotData.shotFrameCount -= (m_shotData.shotFrameCount / kShotSpeedChange);

		}
		if (objNo == ObstructSelectNo::DAMAGE_RESULT)
		{
			// �_���[�W����������
			m_shotData.damage += (m_shotData.damage * kShotDamageChange);
		}
	}
}

void ObstacleBase::Draw()
{
#if _DEBUG
	// �U���͈�
	DrawSphere3D(m_pos, 300, 4, 0xffffff, 0xffffff, false);
#endif
#if true
	for (auto& shot : m_pShot)
	{
		shot->Draw();
	}
#endif

	// 3D�`�惂�f��
	MV1DrawModel(m_handle);
}