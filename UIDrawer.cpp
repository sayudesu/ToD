#include "UIDrawer.h"
#include <DxLib.h>
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
}

UIDrawer::UIDrawer() :
	m_hBgUtil(-1),
	m_hObjectCost(-1),
	m_hMeat(-1),
	m_hTopicSpecialAttack(-1),
	m_hBarTopicSpecialAttack(-1),
	m_hBgHp(-1),
	m_hHp(-1),
	m_costNum(0)
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

	//// コスト描画背景
	//DrawRotaGraph(500, 100, 0.5f, DX_PI_F * 180.0f, m_hObjectCost, true);

	// オブジェクトコスト背景
	DrawGraph(Game::kScreenWidth - 570, 20, m_hObjectCost, true);
	DrawGraph(Game::kScreenWidth - 570, 20, m_hMeat, true);

	// コスト数
	DrawFormatString(0, 0, 0x000000, "%d", m_costNum);

	// 特殊攻撃のボタン説明
	DrawGraph(1150, Game::kScreenHeight - 150 , m_hTopicSpecialAttack, true);
	DrawGraph(1150, Game::kScreenHeight - 150 , m_hTopicSpecialAttack, true);

	// 体力関係
	DrawGraph(120, 20, m_hBgHp, true);
	DrawGraph(120, 20, m_hHp, true);

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

void UIDrawer::SetCostSetObject(int cost)
{
	m_costNum = cost;
}
