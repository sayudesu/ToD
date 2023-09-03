#include "Player.h"
#include <DxLib.h>
#include "../../Util/Pad.h"
#include "../../Util/game.h"
#include "../../Save/SaveDataFunctions.h"
#include "../../Util/SoundFunctions.h"
#include "../../Util/LoadGraphFunction.h"
#include "ObjectMenuDrawer.h"
#include "../Shot/NormalShot.h"
namespace
{
//	constexpr int kSetCost = 200;
	constexpr int kSetCost = 1;
	constexpr float kSetPosMoveSpeed = 50.0f;
	constexpr float kSpecialAttackPosMoveSpeed = 20.0f;

	const char* kCostString = "オブジェクトコスト[%d]";
	const char* kObjSelectString = "RBを押してオブジェクトを選ぶ！";
}

Player::Player() :
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_specialAttackPos(VGet(0.0f, 0.0f, 0.0f)),
	m_isSpecialAttack(false),
	m_screenToWorldPos(VGet(0.0f, 0.0f, 0.0f)),
	m_isResultObject(false),
	m_isSetObject(false),
	m_hCostBg(0),
	m_objectCostNum(0),
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
	// 画像のロード
	m_hCostBg = LoadGraph("Data/Image/Cost.png");

	// インスタンス生成
	m_pObjMenu = new ObjectMenuDrawer;

	m_pObjMenu->Init();
}

void Player::End()
{
	m_pObjMenu->End();
	// メモリ解放
	delete m_pObjMenu;
	m_pObjMenu = nullptr;
}

void Player::Update()
{	
	// オブジェクトメニューを開いている場合
	if (!m_pObjMenu->IsSetMenu() && (m_pObjMenu->SelectNo() == -1))
	{
		// 操作の制御
		UpdateControl();
		// プレイヤーの位置を渡す
		m_specialAttackPos = m_pos;
	}
	if (m_pObjMenu->SelectNo() != -1)
	{
		UpdateSpecialAttack();
		// 技を出した後
		if (m_isSpecialAttack)
		{
			// 選択した番号をリセット
			m_pObjMenu->ResetSelectNo();
		}
	}
	// ショット
	UpdateShot();

	// オブジェクトの設置コスト
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
	VECTOR a = VGet(m_pos.x + 50.0f, m_pos.y, m_pos.z);
	DrawLine3D(m_pos, a, 0xffffff);

	DrawRotaGraph(500, 100, 0.5f, DX_PI_F * 180.0f, m_hCostBg, true);

	// オブジェクトコスト描画
	DrawFormatString(400, 80, 0xffffff, kCostString, m_objectCostNum);

	// オブジェクト選択
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

// 特殊攻撃をおこなったかどうか
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

void Player::UpdateControl()
{
	// 設置場を指定
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

	// 設置します
	if (Pad::isTrigger(PAD_INPUT_1) && m_objectCostNum > kSetCost)
	{		
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
			}
		}

		if (m_isSetObject)
		{
			m_isResultObject = true;
			// オブジェクトを置いた場所を保存
			m_posHistory.push_back(m_pos);
			// 設置した分のコスト
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
		// インスタンス生成
		m_pShot = new NormalShot(m_countShotNo, VGet(m_pos.x, m_pos.y + 2000.0f, m_pos.z));
		m_pShot->Init(m_targetPos,VGet(10,10,10), VGet(0.0f, 90.0f, 0.0f), 30.0f);
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

		// トラッキングデータの保存
		m_trackingData.pos = m_pShot->SetPos();
		m_trackingData.tracking = m_isTrackingShot;
	}
	
}

void Player::ObjectCost()
{
	m_objectCostNum++;
}
