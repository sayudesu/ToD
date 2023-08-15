#include "Player.h"
#include <DxLib.h>
#include "../../Util/Pad.h"
#include "../../SaveDataFunctions.h"
#include "../../Util/SoundFunctions.h"
#include "../../Util/LoadGraphFunction.h"


Player::Player() :
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_screenToWorldPos(VGet(0.0f, 0.0f, 0.0f)),
	m_isResultObject(false),
	m_isSetObject(false),
	m_objectCostNum(0)
{
	m_posHistory.push_back(VGet(-1.0f, -1.0f, -1.0f));
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::End()
{
}

void Player::Update()
{
	
	// 操作の制御
	UpdateControl();
}

void Player::Draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + 10, m_pos.y + 10, 0x00ffff, true);

	VECTOR pos = VGet(m_pos.x, m_pos.y + 30.0f, m_pos.z);
	DrawSphere3D(pos, 8, 16, 0xffffff, 0xffffff, true);

	// オブジェクトコスト描画
	DrawFormatString(300, 300, 0xffffff, "オブジェクトコスト[%d]", m_objectCostNum);
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
	// オブジェクトの設置コスト
	ObjectCost();

	// 設置場を指定
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_pos.z += 50.0f;
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_pos.z -= 50.0f;
	}
	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		m_pos.x -= 50.0f;
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		m_pos.x += 50.0f;
	}

	m_isResultObject = false;
	// 設置します
	if (Pad::isTrigger(PAD_INPUT_1) && m_objectCostNum > 100)
	{		
		m_objectCostNum -= 100;
		// すでにその場所にオブジェクトが存在しないか確認
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
				break;
			}
		}

		// オブジェクトを置いた場所を保存
		if (m_isSetObject)
		{
			m_posHistory.push_back(m_pos);
			m_isResultObject = true;
		}
	}
}

void Player::ObjectCost()
{
	m_objectCostNum++;
}
