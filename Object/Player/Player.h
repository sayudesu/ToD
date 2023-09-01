#pragma once
#include <DxLib.h>
#include "../../Util/Vec2.h"
#include <vector>


class ObjectMenuDrawer;

// プレイヤークラス
class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void End();
	void Update();
	void Draw();
	void DrawUI();

	// マウスの位置を返す
	VECTOR SetMouseWorldPos() { return m_screenToWorldPos; }
	VECTOR SetPos() { return m_pos; }
	// マウスが押されているかどうか
	bool SetMouseLeft() { return m_isResultObject; }

	// ゲームの進行を止めるかどうか
	bool isGetGameStop();
private:
	// 操作を制御
	void UpdateControl();
	void UpdateSpecialAttack();
	// オブジェクトのコスト関連
	void ObjectCost();
private:
	// マウスの位置
	VECTOR m_pos;

	VECTOR m_specialAttackPos;
	bool m_isSpecialAttack;
	// 画面から3D空間に変換用
	VECTOR m_screenToWorldPos;
	VECTOR m_screenPos;
	VECTOR m_start3DPos;
	VECTOR m_end3DPos;

	// 位置を記録します
	std::vector<VECTOR>m_posHistory;

	// マウスの左クリックが押されているかどうか
	// false : 押していない true : 押している
	bool m_isResultObject;
	// 設置出来るかの最終確認
	bool m_isSetObject;

	// オブジェクトコスト関連
	// 背景ハンドル
	int m_hCostBg;
	// コスト数
	int m_objectCostNum;

	ObjectMenuDrawer* m_pObjMenu;
};

