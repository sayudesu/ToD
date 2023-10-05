#include "Player.h"
#include <DxLib.h>
#include "../../Util/Pad.h"
#include "../../Util/game.h"
#include "../../Save/SaveDataFunctions.h"
#include "../../Util/SoundFunctions.h"
#include "ObjectMenuDrawer.h"
#include "../Shot/NormalShot.h"
#include "../../Util/ObstructSelectNo.h"

namespace
{
	constexpr int kFirstCost = 400;
	// �I�u�W�F�N�g�ݒu����ۂ̃R�X�g
	constexpr int kSetCost = 200;
	// ����U�����鎞�̃J�[�\���ړ����x
	constexpr float kSpecialAttackPosMoveSpeed = 20.0f;

	// �K�E�Z
	const char* kFilePathShot = "Data/Model/ShotCat.mv1";

#if _DEBUG
	constexpr  int kCostPuls = 200;// ��
#else
	constexpr  int kCostPuls = 1;// ��
#endif
}

Player::Player() :
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_specialAttackPos(VGet(0.0f, 0.0f, 0.0f)),
	m_isSpecialAttack(false),
	m_isResultObject(false),
	m_isSetObject(false),
	m_objectCostNum(kFirstCost),
	m_isShot(false),
	m_countShotNo(-1),
	m_deleteFrameCountShot(0),
	m_isTrackingShot(false),
	m_checkMapChipNo(VGet(0,0,0))
{
	
}

Player::~Player()
{
}

// ����������
void Player::Init(MapDatas mapChip)
{
	// �C���X�^���X����
	m_pObjMenu = new ObjectMenuDrawer();

	m_pObjMenu->Init();

	m_posHistory.push_back(VGet(0.0f, 0.0f, 0.0f));

	m_mapData = mapChip;
	// �v���C���[�̏����ʒu
	m_checkMapChipNo.x = (m_mapData.chipMaxX / 2) + ((m_mapData.chipMaxX / 2)/2) + 1;
	m_checkMapChipNo.z = m_mapData.chipMaxZ / 2;

	// �ʒu�ɑ��
	m_pos.x = (m_checkMapChipNo.x * 50.0f);
	m_pos.z = (m_checkMapChipNo.z * 50.0f);
}

// �������J������
void Player::End()
{
	m_pObjMenu->End();
	// ���������
	delete m_pObjMenu;
	m_pObjMenu = nullptr;
}

// �X�V����
void Player::Update()
{	
	// �I�u�W�F�N�g���j���[���J���Ă���ꍇ
	if (!m_pObjMenu->IsSetMenu() && (m_pObjMenu->SelectNo() == -1))
	{
		if (!m_isResultObject)
		{
			// ����̐���
			UpdateControl();
		}
		UpdateObjSelect();
		// �v���C���[�̈ʒu��n��
		m_specialAttackPos = m_pos;
	}
	if (m_pObjMenu->SelectNo() != -1)
	{
		UpdateSpecialAttack();
		// �Z���o������
		if (m_isSpecialAttack)
		{
			// �I�������ԍ������Z�b�g
			m_pObjMenu->ResetSelectNo();
		}
	}
	// �V���b�g
	UpdateShot();


	static int count = 0;
	count++;
	if (count > 3)
	{
		// �I�u�W�F�N�g�̐ݒu�R�X�g
		ObjectCost();
		count = 0;
	}

	m_pObjMenu->Update();

	// ����
	ObjectUp();
}

// �`��
void Player::Draw()
{
	DrawCapsule3D(
		m_pos,
		VGet(m_pos.x, m_pos.y + 25.0f, m_pos.z),
		18.0f,
		8,
		0x0000ff,
		0x0000ff,
		true);

	if (m_pObjMenu->SelectNo() == 0)
	{
		DrawCapsule3D(
			m_specialAttackPos,
			VGet(m_specialAttackPos.x, m_specialAttackPos.y, m_specialAttackPos.z),
			100.0f,
			8,
			0x0000ff,
			0x0000ff,
			false);
	}

	if (m_countShotNo == 0)
	{
		m_pShot->Draw();
		DrawSphere3D(m_pShot->GetCollData().pos,m_pShot->GetCollData().radius, 8, 0xffffff, 0xffffff, false);
		
	}


}

// UI��p�`��
void Player::DrawUI()
{
	// ����U���̃��j���[
	m_pObjMenu->Draw();
}

// �Q�[���̐i�s���~�߂邩�ǂ���
bool Player::IsGetGameStop()
{
	if (m_pObjMenu->SelectNo()!= -1)
	{
		return true;
	}

	return false;
}

// ����U���������Ȃ������ǂ���
bool Player::isSpecialAttack()
{
	return m_isSpecialAttack;
}

// ����U���̏�Ԃ����Z�b�g����
void Player::SpecialAttackReset()
{
	m_isSpecialAttack = false;
}

// �V���b�g�������ǂ���
void Player::IsSetShot(bool isShot)
{
	m_isShot = isShot;
}

// �J�����N���X�ɓn��
Tracking Player::GetTracingData()
{
	return m_trackingData;
}

// ���݂̃I�u�W�F�N�g�R�X�g��n��
int Player::GetObjectCostNum()
{
	return m_objectCostNum;
}

// ����𐧌�
void Player::UpdateControl()
{
	// �f�o�b�O�p
	static int pressCount = 0;
	static int press2Count = 0;
	static bool isPress = false;

	static const int pressCountMax          = 30 - 10;
	static const int press2CountMax         = 3;
	static const int pressDiagonalCountMax  = 20;
	static const int pressDiagonal2CountMax = 3 * 2;

	static bool isUp    = false;
	static bool isDown  = false;
	static bool isLeft  = false;
	static bool isRight = false;

	static bool isUpRight   = false;
	static bool isUpLeft    = false;
	static bool isDownRight = false;
	static bool isDownLeft  = false;



	isUp        = false;
	isDown      = false;
	isLeft      = false;
	isRight     = false;

	isUpRight   = false;
	isUpLeft    = false;
	isDownRight = false;
	isDownLeft  = false;

	float speed = 25.0f/2.0f;

	isPress = false;

	// �ݒu����w��
	if (Pad::isPress(PAD_INPUT_UP))
	{
		isUp = true;
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		isDown = true;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		isLeft = true;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		isRight = true;
	}

	// �E��
	if (isUp && isRight)
	{
		pressCount++;
		if (pressCount == 1)
		{
			m_checkMapChipNo.z += 1;
			m_checkMapChipNo.x += 1;
		}
		if (pressCount > pressDiagonalCountMax)
		{
			press2Count++;
			if (press2Count > pressDiagonal2CountMax)
			{
				m_checkMapChipNo.z += 1;
				m_checkMapChipNo.x += 1;
				press2Count = 0;
			}
		}
		isUpRight = true;
	}
	// ����
	if (isUp && isLeft)
	{
		pressCount++;
		if (pressCount == 1)
		{
			m_checkMapChipNo.z += 1;
			m_checkMapChipNo.x -= 1;
		}
		if (pressCount > pressDiagonalCountMax)
		{
			press2Count++;
			if (press2Count > pressDiagonal2CountMax)
			{
				m_checkMapChipNo.z += 1;
				m_checkMapChipNo.x -= 1;
				press2Count = 0;
			}
		}
		isUpLeft = true;
	}
	// �E��
	if (isDown && isRight)
	{
		pressCount++;
		if (pressCount == 1)
		{
			m_checkMapChipNo.z -= 1;
			m_checkMapChipNo.x += 1;
		}
		if (pressCount > pressDiagonalCountMax)
		{
			press2Count++;
			if (press2Count > pressDiagonal2CountMax)
			{
				m_checkMapChipNo.z -= 1;
				m_checkMapChipNo.x += 1;
				press2Count = 0;
			}
		}
		isDownRight = true;
	}
	// ����
	if (isDown && isLeft)
	{
		pressCount++;
		if (pressCount == 1)
		{
			m_checkMapChipNo.z -= 1;
			m_checkMapChipNo.x -= 1;
		}
		if (pressCount > pressDiagonalCountMax)
		{
			press2Count++;
			if (press2Count > pressDiagonal2CountMax)
			{
				m_checkMapChipNo.z -= 1;
				m_checkMapChipNo.x -= 1;
				press2Count = 0;
			}
		}
		isDownLeft = true;
	}


	if (isUp && !isUpRight && !isUpLeft)
	{
		pressCount++;
		if (pressCount == 1)m_checkMapChipNo.z += 1;
		if (pressCount > pressCountMax)
		{
			press2Count++;
			if (press2Count > press2CountMax)
			{
				m_checkMapChipNo.z += 1;
				press2Count = 0;
			}
		}
	}
	if (isDown && !isDownRight && !isDownLeft)
	{
		pressCount++;
		if (pressCount == 1)m_checkMapChipNo.z -= 1;
		if (pressCount > pressCountMax)
		{
			press2Count++;
			if (press2Count > press2CountMax)
			{
				m_checkMapChipNo.z -= 1;
				press2Count = 0;
			}
		}
	}
	if (isLeft && !isUpLeft && !isDownLeft)
	{
		pressCount++;
		if (pressCount == 1)m_checkMapChipNo.x -= 1;
		if (pressCount > pressCountMax)
		{
			press2Count++;
			if (press2Count > press2CountMax)
			{
				m_checkMapChipNo.x -= 1;
				press2Count = 0;
			}
		}
	}
	if (isRight && !isUpRight && !isDownRight)
	{
		pressCount++;
		if (pressCount == 1)m_checkMapChipNo.x += 1;
		if (pressCount > pressCountMax)
		{
			press2Count++;
			if (press2Count > press2CountMax)
			{
				m_checkMapChipNo.x += 1;
				press2Count = 0;
			}
		}
	}

	if (!isUp && !isDown && !isLeft && !isRight)
	{
		pressCount = 0;
		press2Count = 0;
	}

	// �͈͊O����
	if (!CheckOutSide())
	{
		VECTOR tempPos{};
		tempPos.x = (m_checkMapChipNo.x * 50.0f);
		tempPos.z = (m_checkMapChipNo.z * 50.0f);

		if (m_pos.x > tempPos.x)
		{
			m_pos.x -= speed;
		}
		if (m_pos.x < tempPos.x)
		{
			m_pos.x += speed;
		}
		if (m_pos.z > tempPos.z)
		{
			m_pos.z -= speed;
		}
		if (m_pos.z < tempPos.z)
		{
			m_pos.z += speed;
		}
	}
	else
	{
		// �ʒu�ɑ��
		m_pos.x = (m_checkMapChipNo.x * 50.0f);
		m_pos.z = (m_checkMapChipNo.z * 50.0f);
	}
}

void Player::UpdateObjSelect()
{
	// �ݒu�p�ϐ�������
	m_isSetObject = false;
	static bool isBreak = false;

	if (!m_isResultObject &&
		m_selectObstructData.no != ObstructSelectNo::SELECT_RESULT)
	{
		m_selectObstructData.no = ObstructSelectNo::EMPTY_RESULT;
	}

	if (Pad::isTrigger(PAD_INPUT_1) &&
		!m_isResultObject)
	{
		// �I�u�W�F�N�g���ݒu�\�Ȃ̂�
		if (m_mapData.data[m_checkMapChipNo.x + m_checkMapChipNo.z * m_mapData.chipMaxX] == m_mapData.road)
		{
			// �I�u�W�F�N�g�ݒu����
			m_isResultObject = true;
			// ���łɐݒu���Ă��邩�̊m�F
			for (int i = 0; i < m_posHistory.size(); i++)
			{
				if (m_posHistory[i].x == m_checkMapChipNo.x &&
					m_posHistory[i].z == m_checkMapChipNo.z)
				{
					isBreak = true;
					break;
				}
				else
				{
					m_selectObstructData.no = ObstructSelectNo::SELECT_RESULT;
					isBreak = false;
				}
			}
		}

	}

	static bool isSelect1 = false;
	static bool isSelectUp = false;

	static int  selectDeleteFrameCount = 0;
	
	// �ݒu�I�u�W�F�N�g�̑I��
	if (isSelect1 && m_objectCostNum > kSetCost)
	{
		if (Pad::isPress(PAD_INPUT_4))
		{
			m_selectObstructData.no = ObstructSelectNo::HRAVY_PRESS;
		}
		if (Pad::isRelase(PAD_INPUT_4))
		{
			// �ݒu�I�u�W�F�N�g��ID����
			m_selectObstructData.no = ObstructSelectNo::HRAVY_RESULT;
			isSelect1 = false;
			// �I�u�W�F�N�g�ݒu���߂����Ȃ�
			m_isResultObject = false;
			// �I�u�W�F�N�g�R�X�g������
			m_objectCostNum -= kSetCost;
			// �I�u�W�F�N�g�ݒu�ʒu���L�^
			m_posHistory.push_back(m_checkMapChipNo);
		}

		if (Pad::isPress(PAD_INPUT_2))
		{
			m_selectObstructData.no = ObstructSelectNo::NORMAL_PRESS;
		}
		if (Pad::isRelase(PAD_INPUT_2))
		{
			// �ݒu�I�u�W�F�N�g��ID����
			m_selectObstructData.no = ObstructSelectNo::NORMAL_RESULT;
			isSelect1 = false;
			// �I�u�W�F�N�g�ݒu���߂����Ȃ�
			m_isResultObject = false;
			// �I�u�W�F�N�g�R�X�g������
			m_objectCostNum -= kSetCost;
			// �I�u�W�F�N�g�ݒu�ʒu���L�^
			m_posHistory.push_back(m_checkMapChipNo);
		}

		if (Pad::isPress(PAD_INPUT_1))
		{
			m_selectObstructData.no = ObstructSelectNo::MISSILE_PRESS;
		}
		if (Pad::isRelase(PAD_INPUT_1))
		{
			// �ݒu�I�u�W�F�N�g��ID����
			m_selectObstructData.no = ObstructSelectNo::MISSILE_RESULT;
			isSelect1 = false;
			// �I�u�W�F�N�g�ݒu���߂����Ȃ�
			m_isResultObject = false;
			// �I�u�W�F�N�g�R�X�g������
			m_objectCostNum -= kSetCost;
			// �I�u�W�F�N�g�ݒu�ʒu���L�^
			m_posHistory.push_back(m_checkMapChipNo);
		}
	}

	if (isSelectUp)
	{
		if (Pad::isTrigger(PAD_INPUT_2))
		{
			m_selectObstructData.no = ObstructSelectNo::SPEED_PRESS;
			isSelectUp = false;
		}
		if (Pad::isTrigger(PAD_INPUT_4))
		{
			m_selectObstructData.no = ObstructSelectNo::DAMAGE_PRESS;
			isSelectUp = false;
		}
	}

	// �Ȃɂ����邩
	if (m_isResultObject && !isSelect1)
	{
		// �j��
		if (Pad::isPress(PAD_INPUT_1))
		{
		//	m_selectObstructData.no = ObstructSelectNo::ERASE_PRESS;
		}
		if (Pad::isRelase(PAD_INPUT_1))
		{
		//	m_selectObstructData.no = ObstructSelectNo::ERASE_RESULT;
		}

		if (!isBreak)
		{
			// �ݒu
			if (Pad::isPress(PAD_INPUT_2))
			{
				m_selectObstructData.no = ObstructSelectNo::OBSTRUCT_PRESS;
			}
			if (Pad::isRelase(PAD_INPUT_2))
			{
				isSelect1 = true;
				m_selectObstructData.no = ObstructSelectNo::OBSTRUCT_RESULT;
			}
		}

		// ����
		if (Pad::isRelase(PAD_INPUT_4))
		{
			m_selectObstructData.no = ObstructSelectNo::POWER_UP_RESULT;
			m_isSelectPowerUp = true;
			isSelectUp = true;
		}
	}

	// ����
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		m_selectObstructData.no = ObstructSelectNo::EMPTY_RESULT;
		m_isResultObject = false;
		isSelect1 = false;
	}
}

// ����U���p
void Player::UpdateSpecialAttack()
{
	m_isSpecialAttack = false;	
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_specialAttackPos.z += kSpecialAttackPosMoveSpeed;
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_specialAttackPos.z -= kSpecialAttackPosMoveSpeed;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_specialAttackPos.x -= kSpecialAttackPosMoveSpeed;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_specialAttackPos.x += kSpecialAttackPosMoveSpeed;
	}

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_isSpecialAttack = true;
		m_targetPos = m_specialAttackPos;
	}
}

// �͈͊O����
bool Player::CheckOutSide()
{
	// �}�b�v�̒[�܂ňړ��������
	// ���Α��܂ňړ�����
	// ��
	if (m_checkMapChipNo.x < 0)
	{
		m_checkMapChipNo.x = m_mapData.chipMaxX - 1;
		return true;
	}
	// �E
	if (m_checkMapChipNo.x > m_mapData.chipMaxX - 1)
	{
		m_checkMapChipNo.x = 0;
		return true;
	}
	// ��
	if (m_checkMapChipNo.z < 0)
	{
		m_checkMapChipNo.z = m_mapData.chipMaxZ - 1;
		return true;
	}
	// ��
	if (m_checkMapChipNo.z > m_mapData.chipMaxZ - 1)
	{
		m_checkMapChipNo.z = 0;
		return true;
	}

	return false;
}

// �V���b�g�𐶐�
void Player::UpdateShot()
{
	if (m_isShot)
	{

		const int handle = MV1LoadModel(kFilePathShot);

		const int damage = 1000;

		m_countShotNo++;
		m_isTrackingShot = true;
		// �C���X�^���X����
		m_pShot = new NormalShot(VGet(m_pos.x, m_pos.y + 10000.0f, m_pos.z),0, m_countShotNo);
		m_pShot->Init(handle,0,m_targetPos, VGet(10, 10, 10), VGet(0.0f, 90.0f, 0.0f), 16.0f * 7, damage, 30.0f, true);
	}

	if (m_countShotNo == 0)
	{
		m_pShot->Update();
		m_collShotData = m_pShot->GetCollData();

		if (false)
		{
			m_deleteFrameCountShot++;
			if (m_deleteFrameCountShot > 30)
			{
				m_deleteFrameCountShot = 0;
				m_isTrackingShot = false;
				m_countShotNo--;
				m_pShot->End();
				delete m_pShot;
				m_pShot = nullptr;
			}
		}

		// �g���b�L���O�f�[�^�̕ۑ�
		m_trackingData.pos = m_pShot->SetPos();
		m_trackingData.isTracking = m_isTrackingShot;
	}
	
}

// �I�u�W�F�N�g�̃R�X�g�֘A
void Player::ObjectCost()
{
	m_objectCostNum += kCostPuls;
}

void Player::ObjectUp()
{
	if (m_selectObstructData.no == ObstructSelectNo::POWER_UP_RESULT)
	{
		printfDx("������\n");
		if (m_selectObstructData.no == ObstructSelectNo::SPEED_RESULT)
		{
			printfDx("�X�s�[�h����\n");
		}
		if (m_selectObstructData.no == ObstructSelectNo::DAMAGE_RESULT)
		{
			printfDx("�U���͋���\n");
		}
	}
}

ObstructSelect Player::GetObstructData()
{
	return m_selectObstructData;
}

ObjectData Player::GetCollShotDatas()
{
	return m_collShotData;
}
