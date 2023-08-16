#include "Player.h"
#include <DxLib.h>
#include "../../Util/Pad.h"
#include "../../SaveDataFunctions.h"
#include "../../Util/SoundFunctions.h"
#include "../../Util/LoadGraphFunction.h"

namespace
{
	constexpr int kSetCost = 200;
	constexpr int kSetPosMoveSpeed = 50.0f;
}

Player::Player() :
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
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
	m_hCostBg = LoadGraph("Data/Image/Cost.png");
}

void Player::End()
{
}

void Player::Update()
{	
	// ����̐���
	UpdateControl();
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
}

void Player::DrawUI()
{
	VECTOR a = VGet(m_pos.x + 50.0f, m_pos.y, m_pos.z);
	DrawLine3D(m_pos, a, 0xffffff);

	DrawBox(m_pos.x, m_pos.y, m_pos.x + 10, m_pos.y + 10, 0x00ffff, true);

	DrawRotaGraph(500, 100, 0.5f, DX_PI_F * 180.0f, m_hCostBg, true);

	// �I�u�W�F�N�g�R�X�g�`��
	DrawFormatString(400, 80, 0xffffff, "�I�u�W�F�N�g�R�X�g[%d]", m_objectCostNum);

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
}

void Player::UpdateControl()
{
	// �I�u�W�F�N�g�̐ݒu�R�X�g
	ObjectCost();

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

void Player::ObjectCost()
{
	m_objectCostNum++;
}
