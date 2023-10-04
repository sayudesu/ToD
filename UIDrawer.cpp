#include "UIDrawer.h"
#include "Util/game.h"
#include "Util/LoadGraphFunction.h"
#include "Save/SaveDataFunctions.h"


namespace
{
	// 体力やコストやウェーブ数の背景
	const char* const kFileNameBgUtil           = "Data/Image/UI_Up.png";

	// オブジェクトコスト背景
	const char* const kFileNameBgCost           = "Data/Image/UI_Cost.png";
	// 肉画像
	const char* const kFileNameMeat             = "Data/Image/UI_Meat.png";
	const char* const kFileNameCatFood          = "Data/Image/CatFood.png";
	// 特殊攻撃のボタン説明
	const char* const kFileNameSpecialAttack    = "Data/Image/UI_SpecialAttack.png";
	const char* const kFileNameBarSpecialAttack = "Data/Image/m_hBarTopicSpecialAttack.png";
	const char* const kFileNameBgHp             = "Data/Image/UI_BgHP.png";
	const char* const kFileNameHp               = "Data/Image/UI_HP.png";
	// オブジェクト設置時
	const char* const kFileNameSelectObjectBg     = "Data/Image/UI_SelectObj1.png";
	const char* const kFileNameSelectObject       = "Data/Image/UI_SelectObj2.png";
	const char* const kFileNameSelectCreate       = "Data/Image/UI_SelectObjB.png";
	const char* const kFileNameSelectDelete       = "Data/Image/UI_SelectObjA.png";
	const char* const kFileNameSelectPowerUp      = "Data/Image/UI_SelectObjY.png";

	const char* const kFileNameSelectObstructSpeed    = "Data/Image/UI_SelectObjUpY.png";
	const char* const kFileNameSelectObstructPower    = "Data/Image/UI_SelectObjUpB.png";


	const char* const kFileNameSelectObstructHevy    = "Data/Image/UI_SelectObstrctY.png";
	const char* const kFileNameSelectObstructNormal  = "Data/Image/UI_SelectObstrctB.png";
	const char* const kFileNameSelectObstructMISSILE  = "Data/Image/UI_SelectObstrctA.png";

	const char* const kFileNameSelectObstructDelete  = "Data/Image/UI_SelectObjDeleteB.png";

	// 選択用UIの描画位置
	// プレイヤーからプラスの座標
	
	// 強化
	const VECTOR kPwoerUpPos     = VGet(10.0f, -10.0f, 0.0f);
	const VECTOR kPwoerUpStopPos = VGet(20.0f, -100.0f, 0.0f);
	// 設置
	const VECTOR kSetObjPos     = VGet(10.0f, -5.0f, 0.0f);
	const VECTOR kSetObjStopPos = VGet(40.0f, -35.0f, 0.0f);
	// 破壊
	const VECTOR kDeleteObjPos     = VGet(10.0f, 10.0f, 0.0f);
	const VECTOR kDeleteObjStopPos = VGet(20.0f, 30.0f, 0.0f);

	VECTOR kStopPos[static_cast<int>(SelectData::MAX)];
}

UIDrawer::UIDrawer() :
	m_hBgUtil(-1),
	m_hObjectCost(-1),
	m_hMeat(-1),
	m_hTopicSpecialAttack(-1),
	m_hBarTopicSpecialAttack(-1),
	m_hBgHp(-1),
	m_hHp(-1),
	m_hSelectObject(-1),
	m_costNum(0),
	m_playerPos(VGet(0,0,0))
{
}

UIDrawer::~UIDrawer()
{
}

void UIDrawer::Init()
{
	for (int i = 0; i < static_cast<int>(SelectData::MAX); i++)
	{
		m_selectPos[i] = VGet(0,0,0);

		m_selectPressPos[i].x = 10;
		m_selectPressPos[i].y = 10;
		m_selectPressPos[i].z = 0;
	}

	// 画像をロード
	m_hBgUtil	                = LoadGraph(kFileNameBgUtil);
	m_hObjectCost	            = LoadGraph(kFileNameBgCost);
	m_hMeat                     = LoadGraph(kFileNameMeat);
	m_hCatFood                  = LoadGraph(kFileNameCatFood);
	m_hTopicSpecialAttack       = LoadGraph(kFileNameSpecialAttack);
	m_hBarTopicSpecialAttack    = LoadGraph(kFileNameBarSpecialAttack);
	m_hBgHp		                = LoadGraph(kFileNameBgHp);
	m_hHp	                    = LoadGraph(kFileNameHp);
	m_hSelectObjectBg           = LoadGraph(kFileNameSelectObjectBg);
	m_hSelectObject             = LoadGraph(kFileNameSelectObject);

	m_hSelectObjectState[static_cast<int>(SelectData::OBJ_SET) ] = LoadGraph(kFileNameSelectCreate);
	m_hSelectObjectState[static_cast<int>(SelectData::POWER_UP)] = LoadGraph(kFileNameSelectPowerUp);
	m_hSelectObjectState[static_cast<int>(SelectData::OBJ_END) ] = LoadGraph(kFileNameSelectDelete);

	m_hSelectObjectState[static_cast<int>(SelectData::SHOT_SPEED)]  = LoadGraph(kFileNameSelectObstructSpeed);
	m_hSelectObjectState[static_cast<int>(SelectData::SHOT_DAMAGE)] = LoadGraph(kFileNameSelectObstructPower);

	m_hSelectObjectState[static_cast<int>(SelectData::HRAVY)   ] = LoadGraph(kFileNameSelectObstructHevy);
	m_hSelectObjectState[static_cast<int>(SelectData::NORMAL)]   = LoadGraph(kFileNameSelectObstructNormal);
	m_hSelectObjectState[static_cast<int>(SelectData::MISSILE)]  = LoadGraph(kFileNameSelectObstructMISSILE);

	m_hSelectObjectState[static_cast<int>(SelectData::OBJ_DELETE)]  = LoadGraph(kFileNameSelectObstructDelete);

	for (auto& selectNo : m_isSelectNo)
	{
		selectNo = false;
	}
	m_isSelectNo[static_cast<int>(SelectData::OBJ_DELETE)] = true;

	GetGraphSize(m_hBgHp, &m_hpBarX, &m_hpBarY);
}

void UIDrawer::End()
{
}

void UIDrawer::Update()
{
	int select[5]{};
	select[0] = ObstructSelectNo::OBSTRUCT_PRESS;
	select[1] = ObstructSelectNo::POWER_UP_PRESS;
	select[2] = ObstructSelectNo::ERASE_PRESS;



	select[3] = ObstructSelectNo::HRAVY_PRESS;
	select[4] = ObstructSelectNo::NORMAL_PRESS;

	// オブジェクト選択していない場合
	if (m_obstructData.no == ObstructSelectNo::EMPTY_RESULT)
	{
		m_selectPos[static_cast<int>(SelectData::POWER_UP)] = m_playerPos;
		m_selectPos[static_cast<int>(SelectData::OBJ_SET)]  = m_playerPos;
		m_selectPos[static_cast<int>(SelectData::OBJ_END)]  = m_playerPos;

		m_selectPos[static_cast<int>(SelectData::SHOT_DAMAGE)] = m_playerPos;
		m_selectPos[static_cast<int>(SelectData::SHOT_SPEED)]  = m_playerPos;

		m_selectPos[static_cast<int>(SelectData::HRAVY)]   = m_playerPos;
		m_selectPos[static_cast<int>(SelectData::NORMAL)]  = m_playerPos;
		m_selectPos[static_cast<int>(SelectData::MISSILE)] = m_playerPos;

		m_selectPos[static_cast<int>(SelectData::OBJ_DELETE)] = m_playerPos;
	}

	// 選択
	if (m_obstructData.no == ObstructSelectNo::SELECT_RESULT)
	{
		m_isSelectNo[static_cast<int>(SelectData::POWER_UP)] = true;
		m_isSelectNo[static_cast<int>(SelectData::OBJ_SET)]  = true;
		m_isSelectNo[static_cast<int>(SelectData::OBJ_END)]  = true;
		// パワーアップの場合
		if (static_cast<int>(m_playerPos.x) + static_cast<int>(kPwoerUpStopPos.x) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::POWER_UP)].x))
		{
			m_selectPos[static_cast<int>(SelectData::POWER_UP)].x += kPwoerUpPos.x;
		}
		if (static_cast<int>(m_playerPos.y) + static_cast<int>(kPwoerUpStopPos.y) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::POWER_UP)].y))
		{
			m_selectPos[static_cast<int>(SelectData::POWER_UP)].y += kPwoerUpPos.y;
		}

		// オブジェクト設置の場合
		if (static_cast<int>(m_playerPos.x) + static_cast<int>(kSetObjStopPos.x) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::OBJ_SET)].x))
		{
			m_selectPos[static_cast<int>(SelectData::OBJ_SET)].x += kSetObjPos.x;
		}
		if (static_cast<int>(m_playerPos.y) + static_cast<int>(kSetObjStopPos.y) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::OBJ_SET)].y))
		{
			m_selectPos[static_cast<int>(SelectData::OBJ_SET)].y += kSetObjPos.y;
		}

		// オブジェクト破壊
		if (static_cast<int>(m_playerPos.x) + static_cast<int>(kDeleteObjStopPos.x) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::OBJ_END)].x))
		{
			m_selectPos[static_cast<int>(SelectData::OBJ_END)].x += kDeleteObjPos.x;
		}
		if (static_cast<int>(m_playerPos.y) + static_cast<int>(kDeleteObjStopPos.y) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::OBJ_END)].y))
		{
			m_selectPos[static_cast<int>(SelectData::OBJ_END)].y += kDeleteObjPos.y;
		}
	}
	else
	{
		m_isSelectNo[static_cast<int>(SelectData::POWER_UP)] = false;
		m_isSelectNo[static_cast<int>(SelectData::OBJ_SET)]  = false;
		m_isSelectNo[static_cast<int>(SelectData::OBJ_END)]  = false;
		//m_isSelectNo[static_cast<int>(SelectData::SHOT_DAMAGE)] = false;
		//m_isSelectNo[static_cast<int>(SelectData::SHOT_SPEED)] = false;
		//m_isSelectNo[static_cast<int>(SelectData::HRAVY)] = false;
		//m_isSelectNo[static_cast<int>(SelectData::NORMAL)] = false;
		//m_isSelectNo[static_cast<int>(SelectData::MISSILE)] = false;
	}

	// オブジェクト強化選択
	if (m_obstructData.no == ObstructSelectNo::POWER_UP_RESULT)
	{
		m_isSelectNo[static_cast<int>(SelectData::SHOT_DAMAGE)] = true;
		m_isSelectNo[static_cast<int>(SelectData::SHOT_SPEED)] = true;

		// ダメージ強化
		if (static_cast<int>(m_playerPos.x) + static_cast<int>(kPwoerUpStopPos.x) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::SHOT_DAMAGE)].x))
		{
			m_selectPos[static_cast<int>(SelectData::SHOT_DAMAGE)].x += kPwoerUpPos.x;
		}
		if (static_cast<int>(m_playerPos.y) + static_cast<int>(kPwoerUpStopPos.y) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::SHOT_DAMAGE)].y))
		{
			m_selectPos[static_cast<int>(SelectData::SHOT_DAMAGE)].y += kPwoerUpPos.y;
		}

		// スピード強化
		if (static_cast<int>(m_playerPos.x) + static_cast<int>(kSetObjStopPos.x) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::SHOT_SPEED)].x))
		{
			m_selectPos[static_cast<int>(SelectData::SHOT_SPEED)].x += kSetObjPos.x;
		}
		if (static_cast<int>(m_playerPos.y) + static_cast<int>(kSetObjStopPos.y) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::SHOT_SPEED)].y))
		{
			m_selectPos[static_cast<int>(SelectData::SHOT_SPEED)].y += kSetObjPos.y;
		}

		//// オブジェクト強化
		//if (static_cast<int>(m_playerPos.x) + static_cast<int>(kSetObjStopPos.x) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::SHOT_SPEED)].x))
		//{
		//	m_selectPos[static_cast<int>(SelectData::SHOT_SPEED)].x += kSetObjPos.x;
		//}
		//if (static_cast<int>(m_playerPos.y) + static_cast<int>(kSetObjStopPos.y) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::SHOT_SPEED)].y))
		//{
		//	m_selectPos[static_cast<int>(SelectData::SHOT_SPEED)].y += kSetObjPos.y;
		//}
	}
	else
	{
		//m_isSelectNo[static_cast<int>(SelectData::POWER_UP)] = false;
		//m_isSelectNo[static_cast<int>(SelectData::OBJ_SET)]  = false;
		//m_isSelectNo[static_cast<int>(SelectData::OBJ_END)]  = false;
		m_isSelectNo[static_cast<int>(SelectData::SHOT_DAMAGE)] = false;
		m_isSelectNo[static_cast<int>(SelectData::SHOT_SPEED)]  = false;
		//m_isSelectNo[static_cast<int>(SelectData::HRAVY)]   = false;
		//m_isSelectNo[static_cast<int>(SelectData::NORMAL)]  = false;
		//m_isSelectNo[static_cast<int>(SelectData::MISSILE)] = false;
	}
	// オブジェクト設置
	if (m_obstructData.no == ObstructSelectNo::OBSTRUCT_RESULT)
	{
		m_isSelectNo[static_cast<int>(SelectData::HRAVY)]   = true;
		m_isSelectNo[static_cast<int>(SelectData::NORMAL)]  = true;
		m_isSelectNo[static_cast<int>(SelectData::MISSILE)] = true;
		// クロスボウ
		if (static_cast<int>(m_playerPos.x) + static_cast<int>(kPwoerUpStopPos.x) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::HRAVY)].x))
		{
			m_selectPos[static_cast<int>(SelectData::HRAVY)].x += kPwoerUpPos.x;
		}
		else
		{
			m_selectPos[static_cast<int>(SelectData::HRAVY)].x = static_cast<int>(m_playerPos.x) + static_cast<int>(kPwoerUpStopPos.x);
		}
		if (static_cast<int>(m_playerPos.y) + static_cast<int>(kPwoerUpStopPos.y) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::HRAVY)].y))
		{
			m_selectPos[static_cast<int>(SelectData::HRAVY)].y += kPwoerUpPos.y;
		}
		else
		{
			m_selectPos[static_cast<int>(SelectData::HRAVY)].y = static_cast<int>(m_playerPos.y) + static_cast<int>(kPwoerUpStopPos.y);
		}

		// 大砲
		if (static_cast<int>(m_playerPos.x) + static_cast<int>(kSetObjStopPos.x) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::NORMAL)].x))
		{
			m_selectPos[static_cast<int>(SelectData::NORMAL)].x += kSetObjPos.x;
		}
		else
		{
			m_selectPos[static_cast<int>(SelectData::NORMAL)].x = static_cast<int>(m_playerPos.x) + static_cast<int>(kSetObjStopPos.x);
		}
		if (static_cast<int>(m_playerPos.y) + static_cast<int>(kSetObjStopPos.y) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::NORMAL)].y))
		{
			m_selectPos[static_cast<int>(SelectData::NORMAL)].y += kSetObjPos.y;
		}
		else
		{
			m_selectPos[static_cast<int>(SelectData::NORMAL)].y = static_cast<int>(m_playerPos.y) + static_cast<int>(kSetObjStopPos.y);
		}

		// ミサイル
		if (static_cast<int>(m_playerPos.x) + static_cast<int>(kDeleteObjStopPos.x) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::MISSILE)].x))
		{
			m_selectPos[static_cast<int>(SelectData::MISSILE)].x += kDeleteObjPos.x;
		}
		else
		{
			m_selectPos[static_cast<int>(SelectData::MISSILE)].x = static_cast<int>(m_playerPos.x) + static_cast<int>(kDeleteObjStopPos.x);
		}
		if (static_cast<int>(m_playerPos.y) + static_cast<int>(kDeleteObjStopPos.y) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::MISSILE)].y))
		{
			m_selectPos[static_cast<int>(SelectData::MISSILE)].y += kDeleteObjPos.y;
		}
		else
		{
			m_selectPos[static_cast<int>(SelectData::MISSILE)].y = static_cast<int>(m_playerPos.y) + static_cast<int>(kDeleteObjStopPos.y);
		}
	}
	else
	{
		//m_isSelectNo[static_cast<int>(SelectData::POWER_UP)]    = false;
		//m_isSelectNo[static_cast<int>(SelectData::OBJ_SET)]     = false;
		//m_isSelectNo[static_cast<int>(SelectData::OBJ_END)]     = false;
		//m_isSelectNo[static_cast<int>(SelectData::SHOT_DAMAGE)] = false;
		//m_isSelectNo[static_cast<int>(SelectData::SHOT_SPEED)]  = false;
		m_isSelectNo[static_cast<int>(SelectData::HRAVY)]   = false;
		m_isSelectNo[static_cast<int>(SelectData::NORMAL)]  = false;
		m_isSelectNo[static_cast<int>(SelectData::MISSILE)] = false;
	}

	if (m_obstructData.no == ObstructSelectNo::ERASE_RESULT)
	{
		// オブジェクト削除
		if (static_cast<int>(m_playerPos.x) + static_cast<int>(kSetObjStopPos.x) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::OBJ_DELETE)].x))
		{
			m_selectPos[static_cast<int>(SelectData::OBJ_DELETE)].x += kSetObjPos.x;
		}
		else
		{
			m_selectPos[static_cast<int>(SelectData::OBJ_DELETE)].x = static_cast<int>(m_playerPos.x) + static_cast<int>(kSetObjStopPos.x);
		}
		if (static_cast<int>(m_playerPos.y) + static_cast<int>(kSetObjStopPos.y) != static_cast<int>(m_selectPos[static_cast<int>(SelectData::OBJ_DELETE)].y))
		{
			m_selectPos[static_cast<int>(SelectData::OBJ_DELETE)].y += kSetObjPos.y;
		}
		else
		{
			m_selectPos[static_cast<int>(SelectData::OBJ_DELETE)].y = static_cast<int>(m_playerPos.y) + static_cast<int>(kSetObjStopPos.y);
		}
	}
}

void UIDrawer::Draw()
{
	// 体力やコストやウェーブ数の背景
	DrawGraph(0, 0, m_hBgUtil, true);

	Time();

	// オブジェクトコスト背景
	DrawGraph(Game::kScreenWidth - 570, 20, m_hObjectCost, true);
	DrawRotaGraph(Game::kScreenWidth - 570 + 40, 20+ 38,0.13f,DX_PI_F * 180.0f, m_hCatFood, true);

	meat();

	// 特殊攻撃のボタン説明
	DrawGraph(1150, Game::kScreenHeight - 150 , m_hTopicSpecialAttack, true);
	DrawGraph(1150, Game::kScreenHeight - 150 , m_hTopicSpecialAttack, true);
	// 体力関係
	DrawGraph(120, 20, m_hBgHp, true);

	if (hp < -500)
	{
		m_isDead = true;
	}

	DrawModiGraph(
		120, 20, // 左上
		m_hpBarX + 120 + hp, 20,// 右上
		m_hpBarX + 120 + hp, m_hpBarY + 20,//右下
		120, m_hpBarY + 20,//左下
		m_hHp,true);

	// オブジェクト選択
	for (int i = 0; i < static_cast<int>(SelectData::MAX); i++)
	{
		if (m_isSelectNo[i])
		{
			// 背景
			DrawGraph(
				m_selectPos[i].x,
				m_selectPos[i].y,
				m_hSelectObjectBg, true);
			// 文字の背景
			DrawGraph(
				m_selectPos[i].x - m_selectPressPos[i].x,
				m_selectPos[i].y - m_selectPressPos[i].y, 
				m_hSelectObject, true);
			// 文字
			DrawGraph(
				m_selectPos[i].x - m_selectPressPos[i].x + 10,
				m_selectPos[i].y - m_selectPressPos[i].y + 10,
				m_hSelectObjectState[i], true);
		}
	}

	// あとで修正
	// アイコンロード
	static int m_hIcon[8];
	m_hIcon[0] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon0);
	m_hIcon[1] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon1);
	m_hIcon[2] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon2);
	m_hIcon[3] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon3);
	m_hIcon[4] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon4);
	m_hIcon[5] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon5);
	m_hIcon[6] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon6);
	m_hIcon[7] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon7);

	// アイコン描画
	DrawRotaGraph(
		65,
		55,
		0.6f,
		DX_PI_F * 180.0f,
		m_hIcon[SaveDataFunctions::GetIconData().Icon],
		true);
}

// オブジェクトを設置するためのコストを受け取る
void UIDrawer::SetCostSetObject(int cost)
{
	m_costNum = cost;
}

// プレイヤーの位置を受け取る
void UIDrawer::SetPlayerPos(VECTOR pos)
{
	m_playerPos = ConvWorldPosToScreenPos(pos);

	{

		//// 3D座標から2D座標に変換
		//if (!m_isSelect)
		//{
		//	for (int i = 0; i < 5; i++)
		//	{
		//		m_selectPos[i].x= m_playerPos.x - 80;
		//		m_selectPos[i].y= m_playerPos.y - 50;

		//		m_selectPressPos[i].x = 10;
		//		m_selectPressPos[i].y = 10;
		//		m_selectPressPos[i].z = 0;

		//		m_isSelectNo[i] = false;
		//	}
		//}
		//else
		//{
		//	m_isSelectNo[0] = true;
		//	m_isSelectNo[1] = true;
		//	m_isSelectNo[2] = true;
		//	//m_isSelectNo[3] = false;
		//	//m_isSelectNo[4] = false;

		//}
		//float speed = 4.0f;

		//int select[5]{};
		//select[0] = ObstructSelectNo::OBSTRUCT_PRESS;
		//select[1] = ObstructSelectNo::POWER_UP_PRESS;
		//select[2] = ObstructSelectNo::ERASE_PRESS;
		//select[3] = ObstructSelectNo::HRAVY_PRESS;
		//select[4] = ObstructSelectNo::NORMAL_PRESS;
		//// 選択した場合に分かるようにする
		//for (int i = 0; i < 5; i++)
		//{
		//	// 選択された番号
		//	if (m_obstructData.no == select[i])
		//	{
		//		// すこし画像位置を移動する
		//		if (m_selectPressPos[i].x >= 0 &&
		//			m_selectPressPos[i].y >= 0)
		//		{
		//			m_selectPressPos[i].x -= 5;
		//			m_selectPressPos[i].y -= 5;

		//			// 目的の位置を超えたら戻す
		//			if (m_selectPressPos[i].x < 0 &&
		//				m_selectPressPos[i].y < 0)
		//			{
		//				m_selectPressPos[i].x = 0;
		//				m_selectPressPos[i].y = 0;
		//			}
		//		}
		//	}
		//}

		//if (m_obstructData.no == ObstructSelectNo::OBSTRUCT_RESULT)
		//{
		//	m_isSelectNo[3] = true;
		//	m_isSelectNo[4] = true;
		//	if (m_selectPos[3].x > m_playerPos.x)
		//	{
		//		m_selectPos[3].x -= speed;
		//	}
		//	if (m_selectPos[3].x < m_playerPos.x)
		//	{
		//		m_selectPos[3].x += speed;
		//	}
		//	if (m_selectPos[3].y > m_selectPos[0].y - 60.0f)
		//	{
		//		m_selectPos[3].y -= speed;
		//	}
		//	if (m_selectPos[3].y < m_selectPos[0].y - 60.0f)
		//	{
		//		m_selectPos[3].y += speed;
		//	}

		//	if (m_selectPos[4].x > m_playerPos.x + 20.0f)
		//	{
		//		m_selectPos[4].x -= speed;
		//	}
		//	if (m_selectPos[4].x < m_playerPos.x + 20.0f)
		//	{
		//		m_selectPos[4].x += speed;
		//	}
		//	if (m_selectPos[4].y > m_playerPos.y - 30.0f)
		//	{
		//		m_selectPos[4].y -= speed;
		//	}
		//	if (m_selectPos[4].y < m_playerPos.y - 30.0f)
		//	{
		//		m_selectPos[4].y += speed;
		//	}
		//}


		//if (m_selectPos[0].x > m_playerPos.x + 20.0f)
		//{
		//	m_selectPos[0].x -= speed;
		//}
		//if (m_selectPos[0].x < m_playerPos.x + 20.0f)
		//{
		//	m_selectPos[0].x += speed;
		//}
		//if (m_selectPos[0].y > m_playerPos.y - 30.0f)
		//{
		//	m_selectPos[0].y -= speed;
		//}
		//if (m_selectPos[0].y < m_playerPos.y - 30.0f)
		//{
		//	m_selectPos[0].y += speed;
		//}

		//if (m_selectPos[1].x > m_playerPos.x)
		//{
		//	m_selectPos[1].x -= speed;
		//}
		//if (m_selectPos[1].x < m_playerPos.x)
		//{
		//	m_selectPos[1].x += speed;
		//}
		//if (m_selectPos[1].y > m_selectPos[0].y - 60.0f)
		//{
		//	m_selectPos[1].y -= speed;
		//}
		//if (m_selectPos[1].y < m_selectPos[0].y - 60.0f)
		//{
		//	m_selectPos[1].y += speed;
		//}

		//if (m_selectPos[2].x > m_playerPos.x)
		//{
		//	m_selectPos[2].x -= speed;
		//}
		//if (m_selectPos[2].x < m_playerPos.x)
		//{
		//	m_selectPos[2].x += speed;
		//}
		//if (m_selectPos[2].y > m_selectPos[0].y + 60.0f)
		//{
		//	m_selectPos[2].y -= speed;
		//} 
		//if (m_selectPos[2].y < m_selectPos[0].y + 60.0f)
		//{
		//	m_selectPos[2].y += speed;
		//}
	}
}

void UIDrawer::SetObstructSelect(bool select)
{
	m_isSelect = select;
}

void UIDrawer::SetObstructData(ObstructSelect data)
{
	m_obstructData = data;
}

void UIDrawer::Time()
{
	SetFontSize(128);
	if (notloop) DrawFormatString(Game::kScreenWidth / 2 - 170, 12, 0x000000,   "0%d:%d", time, time2);
	if (notloopS2) DrawFormatString(Game::kScreenWidth / 2 - 170, 12, 0x000000, "0%d:0%d", time, timeSecond);
	if (!notloop && !notloopS2)DrawFormatString(Game::kScreenWidth / 2 - 70 + timerPosChange, 20, 0x000000, "%d", time3);
	SetFontSize(16);

	if (notloop)
	{
		timeCount1++;
		if (timeCount1 > 60)
		{
			time2--;
			timeCount1 = 0;
			if (time2 == 9)
			{
				notloop = false;
				notloopS2 = true;
			}
		}
	}

	if (notloopS2)
	{
		timeCountS2++;
		if (timeCountS2 > 60)
		{
			timeSecond--;
			timeCountS2 = 0;
			if (timeSecond == -1)
			{
				notloop2 = true;
				notloopS2 = false;
			}
		}
	}

	if (notloop2)
	{
		timeCount2++;
		if (timeCount2 > 60)
		{
			time3--;
			timeCount2 = 0;
			if (time3 == -1)
			{
				notloop2 = false;
			}

			if (time3 == 9)
			{
				timerPosChange = 15 + 10;
			}
		}
	}

	if (time3 == 0)
	{
		m_isClear = true;
	}
}

void UIDrawer::meat()
{
	m_costNum += 0;
	SetFontSize(48);
	// コスト数
	DrawFormatString(Game::kScreenWidth - 330 + costPos, 35, 0x000000, "%d", m_costNum);
	SetFontSize(16);

	if(m_costNum > 10 && is1)
	{
		costPos -= 5;
		is1 = false;
	}
	if (m_costNum > 100 && is2)
	{
		costPos -= 5;
		is2 = false;
	}
	if (m_costNum > 100 && is3)
	{
		costPos -= 5;
		is3 = false;
	}
	if (m_costNum > 1000 && is4)
	{
		costPos -= 5;
		is4 = false;
	}
	if (m_costNum > 1000 && is5)
	{
		costPos -= 5;
		is5 = false;
	}
	if (m_costNum > 1000 && is6)
	{
		costPos -= 5;
		is6 = false;
	}


	if (m_costNum < 10 && is1_ && !is1)
	{
		costPos += 5;
		is1_ = false;
		is1 = true;
	}
	if (m_costNum < 100 && is2_ && !is2)
	{
		costPos += 5;
		is2_ = false;
		is2 = true;
	}
	if (m_costNum < 100 && is3_ && !is3)
	{
		costPos += 5;
		is3_ = false;
		is3 = true;
	}
	if (m_costNum < 1000 && is4_ && !is4)
	{
		costPos += 5;
		is4_ = false;
		is4 = true;
	}
	if (m_costNum < 1000 && is5_ && !is5)
	{
		costPos += 5;
		is5_ = false;
		is5 = true;
	}
	if (m_costNum < 1000 && is6_ && !is6)
	{
		costPos += 5;
		is6_ = false;
		is6 = true;
	}
}
