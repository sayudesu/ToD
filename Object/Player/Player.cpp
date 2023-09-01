#include "Player.h"
#include <DxLib.h>
#include "../../Util/Pad.h"
#include "../../Util/game.h"
#include "../../Save/SaveDataFunctions.h"
#include "../../Util/SoundFunctions.h"
#include "../../Util/LoadGraphFunction.h"
#include "ObjectMenuDrawer.h"
namespace
{
//	constexpr int kSetCost = 200;
	constexpr int kSetCost = 1;
	constexpr float kSetPosMoveSpeed = 50.0f;
	constexpr float kSpecialAttackPosMoveSpeed = 20.0f;

	const char* kCostString = "�I�u�W�F�N�g�R�X�g[%d]";
	const char* kObjSelectString = "RB�������ăI�u�W�F�N�g��I�ԁI";
}

Player::Player() :
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_specialAttackPos(VGet(0.0f, 0.0f, 0.0f)),
	m_isSpecialAttack(false),
	m_screenToWorldPos(VGet(0.0f, 0.0f, 0.0f)),
	m_isResultObject(false),
	m_isSetObject(false),
	m_hCostBg(0),
	m_objectCostNum(0)
{
	m_posHistory.push_back(VGet(-1.0f, -1.0f, -1.0f));
}

Player::~Player()
{
}

void Player::Init()
{
	// �摜�̃��[�h
	m_hCostBg = LoadGraph("Data/Image/Cost.png");

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
}

void Player::DrawUI()
{
	VECTOR a = VGet(m_pos.x + 50.0f, m_pos.y, m_pos.z);
	DrawLine3D(m_pos, a, 0xffffff);

	DrawRotaGraph(500, 100, 0.5f, DX_PI_F * 180.0f, m_hCostBg, true);

	// �I�u�W�F�N�g�R�X�g�`��
	DrawFormatString(400, 80, 0xffffff, kCostString, m_objectCostNum);

	// �I�u�W�F�N�g�I��
	DrawFormatString(400, Game::kScreenHeight - 100, 0xffffff, kObjSelectString, m_objectCostNum);

	int m_hIcon[8];
	m_hIcon[0] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon0);
	m_hIcon[1] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon1);
	m_hIcon[2] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon2);
	m_hIcon[3] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon3);
	m_hIcon[4] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon4);
	m_hIcon[5] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon5);
	m_hIcon[6] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon6);
	m_hIcon[7] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon7);

	DrawRotaGraph(
		100,
		100,
		1,
		DX_PI_F * 180.0f,
		m_hIcon[SaveDataFunctions::GetIconData().Icon],
		true);

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

	if (Pad::isPress(PAD_INPUT_1))
	{
		m_isSpecialAttack = true;
	}
}

void Player::ObjectCost()
{
	m_objectCostNum++;
}
