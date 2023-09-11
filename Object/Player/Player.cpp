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
//	constexpr int kSetCost = 200;
	constexpr int kSetCost = 1;
	constexpr float kSetPosMoveSpeed = 50.0f;
	constexpr float kSpecialAttackPosMoveSpeed = 20.0f;
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
	m_isTrackingShot(false)
{
	m_posHistory.push_back(VGet(-1.0f, -1.0f, -1.0f));
}

Player::~Player()
{
}

void Player::Init()
{
	// �C���X�^���X����
	m_pObjMenu = new ObjectMenuDrawer;

	m_pObjMenu->Init();
}

void Player::End()
{
	m_pObjMenu->End();
	// ���������
	delete m_pObjMenu;
	m_pObjMenu = nullptr;
}

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

void Player::DrawUI()
{
	// ����U���̃��j���[
	m_pObjMenu->Draw();
}

bool Player::isGetGameStop()
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

void Player::SpecialAttackReset()
{
	m_isSpecialAttack = false;
}

void Player::IsSetShot(bool isShot)
{
	m_isShot = isShot;
}

Tracking Player::GetTracingData()
{
	return m_trackingData;
}

int Player::GetObjectCostNum()
{
	return m_objectCostNum;
}

void Player::UpdateControl()
{
	// �ݒu����w��
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_pos.z += kSetPosMoveSpeed;
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_pos.z -= kSetPosMoveSpeed;
	}
	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		m_pos.x -= kSetPosMoveSpeed;
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		m_pos.x += kSetPosMoveSpeed;
	}

	m_isResultObject = false;

	// �ݒu���܂�
	if (Pad::isTrigger(PAD_INPUT_1) && m_objectCostNum > kSetCost)
	{		
		// ���łɂ��̏ꏊ�ɃI�u�W�F�N�g�����݂��Ȃ����m�F
		for (int i = 0; i < m_posHistory.size(); i++)
		{
			if(m_pos.x != m_posHistory[i].x ||
		       m_pos.z != m_posHistory[i].z)
			{
				m_isSetObject = true;
			}
			else
			{
				m_isSetObject = false;
			}
		}

		if (m_isSetObject)
		{
			m_isResultObject = true;
			// �I�u�W�F�N�g��u�����ꏊ��ۑ�
			m_posHistory.push_back(m_pos);
			// �ݒu�������̃R�X�g
			m_objectCostNum -= kSetCost;
		}
	}
}

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

void Player::UpdateShot()
{
	if (m_isShot)
	{
		m_countShotNo++;
		m_isTrackingShot = true;
		// �C���X�^���X����
		m_pShot = new NormalShot(VGet(m_pos.x, m_pos.y + 2000.0f, m_pos.z),0, m_countShotNo);
		m_pShot->Init(m_targetPos,VGet(10,10,10), VGet(0.0f, 90.0f, 0.0f), 30.0f,false);
	}

	if (m_countShotNo == 0)
	{
		m_pShot->Update();

		if (m_pShot->IsGetEnd())
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
		m_trackingData.tracking = m_isTrackingShot;
	}
	
}

void Player::ObjectCost()
{
	m_objectCostNum++;
}
