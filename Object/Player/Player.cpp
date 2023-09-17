#include "Player.h"
#include <DxLib.h>
#include "../../Util/Pad.h"
#include "../../Util/game.h"
#include "../../Save/SaveDataFunctions.h"
#include "../../Util/SoundFunctions.h"
#include "ObjectMenuDrawer.h"
#include "../Shot/NormalShot.h"

namespace
{
	// �I�u�W�F�N�g�ݒu����ۂ̃R�X�g
	constexpr int kSetCost = 200;
	// ����U�����鎞�̃J�[�\���ړ����x
	constexpr float kSpecialAttackPosMoveSpeed = 20.0f;
	// �}�b�v�`�b�v�T�C�Y
	constexpr  int kMapChipMaxZ = 13;// �s
	constexpr  int kMapChipMaxX = 25;// ��
}

Player::Player() :
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_specialAttackPos(VGet(0.0f, 0.0f, 0.0f)),
	m_isSpecialAttack(false),
	m_isResultObject(false),
	m_isSetObject(false),
	m_isShot(false),
	m_countShotNo(-1),
	m_deleteFrameCountShot(0),
	m_isTrackingShot(false),
	m_checkMapChipNo(VGet(0,0,0))
{
	m_posHistory.push_back(VGet(-1.0f, -1.0f, -1.0f));

	// �v���C���[�̏����ʒu
	m_checkMapChipNo.x = kMapChipMaxX / 2;
	m_checkMapChipNo.z = kMapChipMaxZ / 2;
}

Player::~Player()
{
}

// ����������
void Player::Init()
{
	// �C���X�^���X����
	m_pObjMenu = new ObjectMenuDrawer;

	m_pObjMenu->Init();
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
		// ����̐���
		UpdateControl();
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

	// �I�u�W�F�N�g�̐ݒu�R�X�g
	ObjectCost();

	m_pObjMenu->Update();
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

	isPress = false;
	if (!m_isResultObject)
	{
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
	CheckOutSide();

	// �ʒu�ɑ��
	m_pos.x = (m_checkMapChipNo.x * 50.0f);
	m_pos.z = (m_checkMapChipNo.z * 50.0f);

	// �ݒu�p�ϐ�������
	m_isSetObject    = false;

	//// �ݒu���܂�
	//if (Pad::isTrigger(PAD_INPUT_1) && m_objectCostNum > kSetCost && !m_isResultObject)
	//{		
	//	// �L�^�����ꏊ�̐�
	//	for (int i = 0; i < recordChipNo.size(); i++)
	//	{
	//		// �}�b�v�`�b�v�f�[�^�ł�����ꏊ���m�F
	//		if (m_mapChip[m_checkMapChipNo.x + m_checkMapChipNo.z * kMapChipMaxX] == 1)
	//		{
	//			// ��x�u�������Ƃ��邩�ǂ����m�F
	//			if (recordChipNo[i].x != m_checkMapChipNo.x &&
	//				recordChipNo[i].z != m_checkMapChipNo.z)
	//			{
	//				// �ݒu�ł��鎖���m�F
	//				m_isSetObject = true;
	//			}
	//		}
	//	}
	//	// �u���ꏊ�����߂�
	//	if (m_isSetObject)
	//	{
	//		// �ݒu���������m�F
	//		m_isResultObject = true;
	//		//// �u�����ꏊ���L�^
	//		//recordChipNo.push_back(m_checkMapChipNo);
	//		//// �I�u�W�F�N�g�R�X�g������
	//		//m_objectCostNum -= kSetCost;
	//	}
	//}
	static bool isSelect1 = false;
	if (!m_isResultObject)
	{
		m_selectObstructData.obstructNo = ObstructNo::NONE_RESULT;
		m_selectObstructData.no = ObstructSelectNo::EMPTY_RESULT;
	}

	if (isSelect1 && m_objectCostNum > kSetCost)
	{	
		if (Pad::isTrigger(PAD_INPUT_4))
		{
			m_selectObstructData.obstructNo = ObstructNo::HRAVY_PRESS;
		}
		if (Pad::isRelase(PAD_INPUT_4))
		{
			m_selectObstructData.obstructNo = ObstructNo::HRAVY_RESULT;
			isSelect1 = false;
			m_isResultObject = false;
			// �I�u�W�F�N�g�R�X�g������
			m_objectCostNum -= kSetCost;
		}
		if (Pad::isTrigger(PAD_INPUT_2))
		{
			m_selectObstructData.obstructNo = ObstructNo::NORMAL_PRESS;
		}
		if (Pad::isRelase(PAD_INPUT_2))
		{
			m_selectObstructData.obstructNo = ObstructNo::NORMAL_RESULT;
			isSelect1 = false;
			m_isResultObject = false;
			// �I�u�W�F�N�g�R�X�g������
			m_objectCostNum -= kSetCost;
		}

	}
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// �ݒu�ł��鎖���m�F
		m_isResultObject = true;
	}

	if (m_isResultObject && !isSelect1)
	{	
		//// �j��
		//if (DxLib::CheckHitKey(PAD_INPUT_1) && !isSelect1 && !isSelect2)
		//{
		////	m_selectObstructData.no = ObstructSelectNo::ERASE;
		//}

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


		//// ����
		//if (DxLib::CheckHitKey(PAD_INPUT_4) && !isSelect1)
		//{
		////	isSelect2 = true;
		////	m_selectObstructData.no = ObstructSelectNo::POWER_UP;
		//}
	}

	// ����
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		m_selectObstructData.obstructNo = ObstructNo::NONE_RESULT;
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
void Player::CheckOutSide()
{
	// �}�b�v�̒[�܂ňړ��������
	// ���Α��܂ňړ�����
	// ��
	if (m_checkMapChipNo.x < 0)
	{
		m_checkMapChipNo.x = kMapChipMaxX - 1;
	}
	// �E
	if (m_checkMapChipNo.x > kMapChipMaxX - 1)
	{
		m_checkMapChipNo.x = 0;
	}
	// ��
	if (m_checkMapChipNo.z < 0)
	{
		m_checkMapChipNo.z = kMapChipMaxZ - 1;
	}
	// ��
	if (m_checkMapChipNo.z > kMapChipMaxZ - 1)
	{
		m_checkMapChipNo.z =0;
	}
}

// �V���b�g�𐶐�
void Player::UpdateShot()
{
	if (m_isShot)
	{
		m_countShotNo++;
		m_isTrackingShot = true;
		// �C���X�^���X����
		m_pShot = new NormalShot(VGet(m_pos.x, m_pos.y + 2000.0f, m_pos.z),0, m_countShotNo);
		m_pShot->Init(m_targetPos,VGet(10,10,10), VGet(0.0f, 90.0f, 0.0f),16.0f*5,10000, 30.0f,true);
	}

	if (m_countShotNo == 0)
	{
		m_pShot->Update();

		if (false)
		{
			m_deleteFrameCountShot++;
			if (m_deleteFrameCountShot > 30)
			{
				m_deleteFrameCountShot = 0;
				m_isTrackingShot = false;
				m_countShotNo--;
				m_pShot->End();
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
	m_objectCostNum += 2;
}

// �}�b�v�`�b�v�̏����󂯎��܂�
void Player::SetMapChip(std::vector<int> mapChip)
{
	m_mapChip = mapChip;
}

ObstructSelect Player::GetObstructData()
{
	return m_selectObstructData;
}
