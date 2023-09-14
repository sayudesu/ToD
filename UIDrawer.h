#pragma once
#include <DxLib.h>
#include "Util/ObstructSelectNo.h"

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

	// デバッグ用
	bool GetDead() { return m_isDead; }
	bool GetClear() { return m_isClear; }
	void SetDamage(int damage) { hp -= damage; }

	void SetObstructSelect(bool select);
	void SetObstructData(ObstructSelect data);

private:
	// デバッグ用
	void Time();
	void meat();

private:
	// 画像ハンドル
	// 自身の体力や設置コスト数の背景
	int m_hBgUtil;
	// オブジェクト設置コストの背景
	int m_hObjectCost;
	// 肉の画像
	int m_hCatFood;
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
	int m_hSelectObjectState[5];


	// 現在のコスト数
	int m_costNum;

	// プレイヤーの位置を受け取る
	VECTOR m_playerPos;

	// 選択画像用位置
	VECTOR m_selectPos[5];


	ObstructSelect m_obstructData;
	bool m_isSelect;
	bool m_isSelectNo[5];

	// デバッグ用
	int m_hpBarX;
	int m_hpBarY;

	int hp = 0;

	bool m_isDead = false;
	bool m_isClear = false;


	int time = 01;
	int time2 = 30;
	int time3 = 59;
	int timeSecond = 9;

	int timeCount1 = 0;
	int timeCount2 = 0;
	int timeCountS2 = 0;

	bool notloop = true;
	bool notloop2 = false;
	bool notloopS2 = false;

	int timerPosChange = 0;


	int costPos = 0;
	bool is1 = true;
	bool is2 = true;
	bool is3 = true;
	bool is4 = true;
	bool is5 = true;
	bool is6 = true;

	bool is1_ = true;
	bool is2_ = true;
	bool is3_ = true;
	bool is4_ = true;
	bool is5_ = true;
	bool is6_ = true;
};

