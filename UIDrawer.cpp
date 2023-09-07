#include "UIDrawer.h"
#include "Util/game.h"
#include "Util/LoadGraphFunction.h"
#include "Save/SaveDataFunctions.h"


namespace
{
	// 体力やコストやウェーブ数の背景
	const char* kFileNameBgUtil           = "Data/Image/UI_Up.png";

	// オブジェクトコスト背景
	const char* kFileNameBgCost           = "Data/Image/UI_Cost.png";
	// 肉画像
	const char* kFileNameMeat             = "Data/Image/UI_Meat.png";
	// 特殊攻撃のボタン説明
	const char* kFileNameSpecialAttack    = "Data/Image/UI_SpecialAttack.png";
	const char* kFileNameBarSpecialAttack = "Data/Image/m_hBarTopicSpecialAttack.png";
	const char* kFileNameBgHp             = "Data/Image/UI_BgHP.png";
	const char* kFileNameHp               = "Data/Image/UI_HP.png";
	// オブジェクト設置時
	const char* kFileNameSelectObject     = "Data/Image/UI_SelectObj.png";
	const char* kFileNameSelectCreate     = "Data/Image/UI_SelectObjB.png";
	const char* kFileNameSelectDelete     = "Data/Image/UI_SelectObjA.png";
	const char* kFileNameSelectPowerUp    = "Data/Image/UI_SelectObjY.png";
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
	// 画像をロード
	m_hBgUtil	                = LoadGraph(kFileNameBgUtil);
	m_hObjectCost	            = LoadGraph(kFileNameBgCost);
	m_hMeat                     = LoadGraph(kFileNameMeat);
	m_hTopicSpecialAttack       = LoadGraph(kFileNameSpecialAttack);
	m_hBarTopicSpecialAttack    = LoadGraph(kFileNameBarSpecialAttack);
	m_hBgHp		                = LoadGraph(kFileNameBgHp);
	m_hHp	                    = LoadGraph(kFileNameHp);
	m_hSelectObject             = LoadGraph(kFileNameSelectObject);
	m_hSelectObjectState[0]     = LoadGraph(kFileNameSelectCreate);
	m_hSelectObjectState[1]     = LoadGraph(kFileNameSelectPowerUp);
	m_hSelectObjectState[2]     = LoadGraph(kFileNameSelectDelete);
}

void UIDrawer::End()
{
}

void UIDrawer::Update()
{
}

void UIDrawer::Draw()
{
	// 体力やコストやウェーブ数の背景
	DrawGraph(0, 0, m_hBgUtil, true);

	// オブジェクトコスト背景
	DrawGraph(Game::kScreenWidth - 570, 20, m_hObjectCost, true);
	DrawGraph(Game::kScreenWidth - 570, 20, m_hMeat, true);

	// コスト数
	DrawFormatString(Game::kScreenWidth - 570, 20, 0x000000, "%d", m_costNum);

	// 特殊攻撃のボタン説明
	DrawGraph(1150, Game::kScreenHeight - 150 , m_hTopicSpecialAttack, true);
	DrawGraph(1150, Game::kScreenHeight - 150 , m_hTopicSpecialAttack, true);

	// 体力関係
	DrawGraph(120, 20, m_hBgHp, true);
	DrawGraph(120, 20, m_hHp, true);

	// オブジェクト選択
	for (int i = 0; i < 3; i++)
	{
		DrawGraph(m_selectPos[i].x, m_selectPos[i].y, m_hSelectObject, true);
		DrawGraph(m_selectPos[i].x + 10.0f, m_selectPos[i].y + 10.0f, m_hSelectObjectState[i], true);
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


#if false	
	static int UI = LoadGraph("Data/Image/UI_ToDUI.png");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawGraph(0, 0, UI, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#endif
}

// オブジェクトを設置するためのコストを受け取る
void UIDrawer::SetCostSetObject(int cost)
{
	m_costNum = cost;
}

// プレイヤーの位置を受け取る
void UIDrawer::SetPlayerPos(VECTOR pos)
{
	// 3D座標から2D座標に変換
	m_playerPos = ConvWorldPosToScreenPos(pos);

	m_selectPos[0].x = m_playerPos.x + 20.0f;
	m_selectPos[0].y = m_playerPos.y - 30.0f;

	m_selectPos[1].x = m_playerPos.x;
	m_selectPos[1].y = m_selectPos[0].y - 60.0f;

	m_selectPos[2].x = m_playerPos.x;
	m_selectPos[2].y = m_selectPos[0].y + 60.0f;
}
