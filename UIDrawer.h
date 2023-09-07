#pragma once
#include <DxLib.h>

class UIDrawer
{
public:
	UIDrawer();
	~UIDrawer();

	void Init();
	void End();
	void Update();
	void Draw();

	// オブジェクトを設置するためのコストを受け取る
	void SetCostSetObject(int cost);
	// プレイヤーの位置を受け取り3D座標から2D座標に変換
	void SetPlayerPos(VECTOR pos);

private:
	// 画像ハンドル
	// 自身の体力や設置コスト数の背景
	int m_hBgUtil;
	// オブジェクト設置コストの背景
	int m_hObjectCost;
	// 肉の画像
	int m_hMeat;
	// 必殺技ボタンの説明
	int m_hTopicSpecialAttack;
	int m_hBarTopicSpecialAttack;
	// HPバーの背景
	int m_hBgHp;
	// HPバー
	int m_hHp;
	// オブジェクト設置用
	int m_hSelectObject;
	int m_hSelectObjectState[3];


	// 現在のコスト数
	int m_costNum;

	// プレイヤーの位置を受け取る
	VECTOR m_playerPos;

	// 選択画像用位置
	VECTOR m_selectPos[3];
};

