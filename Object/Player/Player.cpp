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
	// オブジェクト設置する際のコスト
	constexpr int kSetCost = 200;
	// 特殊攻撃する時のカーソル移動速度
	constexpr float kSpecialAttackPosMoveSpeed = 20.0f;

	// 必殺技
	const char* kFilePathShot = "Data/Model/ShotCat.mv1";

#if _DEBUG
	constexpr  int kCostPuls = 200;// 列
#else
	constexpr  int kCostPuls = 1;// 列
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

// 初期化処理
void Player::Init(MapDatas mapChip)
{
	// インスタンス生成
	m_pObjMenu = new ObjectMenuDrawer();

	m_pObjMenu->Init();

	m_posHistory.push_back(VGet(0.0f, 0.0f, 0.0f));

	m_mapData = mapChip;
	// プレイヤーの初期位置
	m_checkMapChipNo.x = (m_mapData.chipMaxX / 2) + ((m_mapData.chipMaxX / 2)/2) + 1;
	m_checkMapChipNo.z = m_mapData.chipMaxZ / 2;

	// 位置に代入
	m_pos.x = (m_checkMapChipNo.x * 50.0f);
	m_pos.z = (m_checkMapChipNo.z * 50.0f);
}

// メモリ開放処理
void Player::End()
{
	m_pObjMenu->End();
	// メモリ解放
	delete m_pObjMenu;
	m_pObjMenu = nullptr;
}

// 更新処理
void Player::Update()
{	
	// オブジェクトメニューを開いている場合
	if (!m_pObjMenu->IsSetMenu() && (m_pObjMenu->SelectNo() == -1))
	{
		if (!m_isResultObject)
		{
			// 操作の制御
			UpdateControl();
		}
		UpdateObjSelect();
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


	static int count = 0;
	count++;
	if (count > 3)
	{
		// オブジェクトの設置コスト
		ObjectCost();
		count = 0;
	}

	m_pObjMenu->Update();

	// 強化
	ObjectUp();
}

// 描画
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

// UI専用描画
void Player::DrawUI()
{
	// 特殊攻撃のメニュー
	m_pObjMenu->Draw();
}

// ゲームの進行を止めるかどうか
bool Player::IsGetGameStop()
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

// 特殊攻撃の状態をリセットする
void Player::SpecialAttackReset()
{
	m_isSpecialAttack = false;
}

// ショットを撃つかどうか
void Player::IsSetShot(bool isShot)
{
	m_isShot = isShot;
}

// カメラクラスに渡す
Tracking Player::GetTracingData()
{
	return m_trackingData;
}

// 現在のオブジェクトコストを渡す
int Player::GetObjectCostNum()
{
	return m_objectCostNum;
}

// 操作を制御
void Player::UpdateControl()
{
	// デバッグ用
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

	// 設置場を指定
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

	// 右上
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
	// 左上
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
	// 右下
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
	// 左下
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

	// 範囲外処理
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
		// 位置に代入
		m_pos.x = (m_checkMapChipNo.x * 50.0f);
		m_pos.z = (m_checkMapChipNo.z * 50.0f);
	}
}

void Player::UpdateObjSelect()
{
	// 設置用変数初期化
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
		// オブジェクトが設置可能なのか
		if (m_mapData.data[m_checkMapChipNo.x + m_checkMapChipNo.z * m_mapData.chipMaxX] == m_mapData.road)
		{
			// オブジェクト設置命令
			m_isResultObject = true;
			// すでに設置しているかの確認
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
	
	// 設置オブジェクトの選択
	if (isSelect1 && m_objectCostNum > kSetCost)
	{
		if (Pad::isPress(PAD_INPUT_4))
		{
			m_selectObstructData.no = ObstructSelectNo::HRAVY_PRESS;
		}
		if (Pad::isRelase(PAD_INPUT_4))
		{
			// 設置オブジェクトのIDを代入
			m_selectObstructData.no = ObstructSelectNo::HRAVY_RESULT;
			isSelect1 = false;
			// オブジェクト設置命令をしない
			m_isResultObject = false;
			// オブジェクトコストを引く
			m_objectCostNum -= kSetCost;
			// オブジェクト設置位置を記録
			m_posHistory.push_back(m_checkMapChipNo);
		}

		if (Pad::isPress(PAD_INPUT_2))
		{
			m_selectObstructData.no = ObstructSelectNo::NORMAL_PRESS;
		}
		if (Pad::isRelase(PAD_INPUT_2))
		{
			// 設置オブジェクトのIDを代入
			m_selectObstructData.no = ObstructSelectNo::NORMAL_RESULT;
			isSelect1 = false;
			// オブジェクト設置命令をしない
			m_isResultObject = false;
			// オブジェクトコストを引く
			m_objectCostNum -= kSetCost;
			// オブジェクト設置位置を記録
			m_posHistory.push_back(m_checkMapChipNo);
		}

		if (Pad::isPress(PAD_INPUT_1))
		{
			m_selectObstructData.no = ObstructSelectNo::MISSILE_PRESS;
		}
		if (Pad::isRelase(PAD_INPUT_1))
		{
			// 設置オブジェクトのIDを代入
			m_selectObstructData.no = ObstructSelectNo::MISSILE_RESULT;
			isSelect1 = false;
			// オブジェクト設置命令をしない
			m_isResultObject = false;
			// オブジェクトコストを引く
			m_objectCostNum -= kSetCost;
			// オブジェクト設置位置を記録
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

	// なにをするか
	if (m_isResultObject && !isSelect1)
	{
		// 破壊
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
			// 設置
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

		// 強化
		if (Pad::isRelase(PAD_INPUT_4))
		{
			m_selectObstructData.no = ObstructSelectNo::POWER_UP_RESULT;
			m_isSelectPowerUp = true;
			isSelectUp = true;
		}
	}

	// 閉じる
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		m_selectObstructData.no = ObstructSelectNo::EMPTY_RESULT;
		m_isResultObject = false;
		isSelect1 = false;
	}
}

// 特殊攻撃用
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

// 範囲外処理
bool Player::CheckOutSide()
{
	// マップの端まで移動させると
	// 反対側まで移動する
	// 左
	if (m_checkMapChipNo.x < 0)
	{
		m_checkMapChipNo.x = m_mapData.chipMaxX - 1;
		return true;
	}
	// 右
	if (m_checkMapChipNo.x > m_mapData.chipMaxX - 1)
	{
		m_checkMapChipNo.x = 0;
		return true;
	}
	// 下
	if (m_checkMapChipNo.z < 0)
	{
		m_checkMapChipNo.z = m_mapData.chipMaxZ - 1;
		return true;
	}
	// 上
	if (m_checkMapChipNo.z > m_mapData.chipMaxZ - 1)
	{
		m_checkMapChipNo.z = 0;
		return true;
	}

	return false;
}

// ショットを生成
void Player::UpdateShot()
{
	if (m_isShot)
	{

		const int handle = MV1LoadModel(kFilePathShot);

		const int damage = 1000;

		m_countShotNo++;
		m_isTrackingShot = true;
		// インスタンス生成
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

		// トラッキングデータの保存
		m_trackingData.pos = m_pShot->SetPos();
		m_trackingData.isTracking = m_isTrackingShot;
	}
	
}

// オブジェクトのコスト関連
void Player::ObjectCost()
{
	m_objectCostNum += kCostPuls;
}

void Player::ObjectUp()
{
	if (m_selectObstructData.no == ObstructSelectNo::POWER_UP_RESULT)
	{
		printfDx("強化中\n");
		if (m_selectObstructData.no == ObstructSelectNo::SPEED_RESULT)
		{
			printfDx("スピード強化\n");
		}
		if (m_selectObstructData.no == ObstructSelectNo::DAMAGE_RESULT)
		{
			printfDx("攻撃力強化\n");
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
