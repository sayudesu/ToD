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
	// オブジェクト設置する際のコスト
	constexpr int kSetCost = 200;
	// 特殊攻撃する時のカーソル移動速度
	constexpr float kSpecialAttackPosMoveSpeed = 20.0f;
	// マップチップサイズ
	constexpr  int kMapChipMaxZ = 13;// 行
	constexpr  int kMapChipMaxX = 25;// 列
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

	// プレイヤーの初期位置
	m_checkMapChipNo.x = kMapChipMaxX / 2;
	m_checkMapChipNo.z = kMapChipMaxZ / 2;
}

Player::~Player()
{
}

// 初期化処理
void Player::Init()
{
	// インスタンス生成
	m_pObjMenu = new ObjectMenuDrawer;

	m_pObjMenu->Init();
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

	isPress = false;
	if (!m_isResultObject)
	{
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
	CheckOutSide();

	// 位置に代入
	m_pos.x = (m_checkMapChipNo.x * 50.0f);
	m_pos.z = (m_checkMapChipNo.z * 50.0f);

	// 設置用変数初期化
	m_isSetObject    = false;

	//// 設置します
	//if (Pad::isTrigger(PAD_INPUT_1) && m_objectCostNum > kSetCost && !m_isResultObject)
	//{		
	//	// 記録した場所の数
	//	for (int i = 0; i < recordChipNo.size(); i++)
	//	{
	//		// マップチップデータでおける場所を確認
	//		if (m_mapChip[m_checkMapChipNo.x + m_checkMapChipNo.z * kMapChipMaxX] == 1)
	//		{
	//			// 一度置いたことあるかどうか確認
	//			if (recordChipNo[i].x != m_checkMapChipNo.x &&
	//				recordChipNo[i].z != m_checkMapChipNo.z)
	//			{
	//				// 設置できる事を確認
	//				m_isSetObject = true;
	//			}
	//		}
	//	}
	//	// 置く場所を決める
	//	if (m_isSetObject)
	//	{
	//		// 設置した事を確認
	//		m_isResultObject = true;
	//		//// 置いた場所を記録
	//		//recordChipNo.push_back(m_checkMapChipNo);
	//		//// オブジェクトコストを引く
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
			// オブジェクトコストを引く
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
			// オブジェクトコストを引く
			m_objectCostNum -= kSetCost;
		}

	}
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// 設置できる事を確認
		m_isResultObject = true;
	}

	if (m_isResultObject && !isSelect1)
	{	
		//// 破壊
		//if (DxLib::CheckHitKey(PAD_INPUT_1) && !isSelect1 && !isSelect2)
		//{
		////	m_selectObstructData.no = ObstructSelectNo::ERASE;
		//}

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


		//// 強化
		//if (DxLib::CheckHitKey(PAD_INPUT_4) && !isSelect1)
		//{
		////	isSelect2 = true;
		////	m_selectObstructData.no = ObstructSelectNo::POWER_UP;
		//}
	}

	// 閉じる
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		m_selectObstructData.obstructNo = ObstructNo::NONE_RESULT;
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
void Player::CheckOutSide()
{
	// マップの端まで移動させると
	// 反対側まで移動する
	// 左
	if (m_checkMapChipNo.x < 0)
	{
		m_checkMapChipNo.x = kMapChipMaxX - 1;
	}
	// 右
	if (m_checkMapChipNo.x > kMapChipMaxX - 1)
	{
		m_checkMapChipNo.x = 0;
	}
	// 下
	if (m_checkMapChipNo.z < 0)
	{
		m_checkMapChipNo.z = kMapChipMaxZ - 1;
	}
	// 上
	if (m_checkMapChipNo.z > kMapChipMaxZ - 1)
	{
		m_checkMapChipNo.z =0;
	}
}

// ショットを生成
void Player::UpdateShot()
{
	if (m_isShot)
	{
		m_countShotNo++;
		m_isTrackingShot = true;
		// インスタンス生成
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

		// トラッキングデータの保存
		m_trackingData.pos = m_pShot->SetPos();
		m_trackingData.isTracking = m_isTrackingShot;
	}
	
}

// オブジェクトのコスト関連
void Player::ObjectCost()
{
	m_objectCostNum += 2;
}

// マップチップの情報を受け取ります
void Player::SetMapChip(std::vector<int> mapChip)
{
	m_mapChip = mapChip;
}

ObstructSelect Player::GetObstructData()
{
	return m_selectObstructData;
}
