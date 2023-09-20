#pragma once
#include <DxLib.h>
#include "../../Util/Vec2.h"
#include "../../Util/Tracking.h"
#include <vector>
#include "../../Util/ObstructSelectNo.h"
#include "../../MapDatas.h"

class ObjectMenuDrawer;
class NormalShot;


// プレイヤークラス
class Player
{
public:
	Player();
	virtual ~Player();

	// 初期化処理
	void Init();
	// メモリ開放処理
	void End();
	// 更新処理
	void Update();
	// 描画
	void Draw();
	// UI専用描画
	void DrawUI();
	// プレイヤーの位置を渡す
	VECTOR SetPos() { return m_pos; }
	// マウスが押されているかどうか
	bool GetObjCreate() { return m_isResultObject; }
	// ゲームの進行を止めるかどうか
	bool IsGetGameStop();
	// 特殊攻撃をおこなったかどうか
	bool isSpecialAttack();
	// 特殊攻撃の状態をリセットする
	void SpecialAttackReset();
	// ショットを撃つかどうか
	void IsSetShot(bool isShot);
	// カメラクラスに渡す
	Tracking GetTracingData();
	// 現在のオブジェクトコストを渡す
	int GetObjectCostNum();
	// マップチップデータを受けとる
	void SetMapChip(MapDatas mapChip);

	ObstructSelect GetObstructData();
private:
	// 操作を制御
	void UpdateControl();
	// 特殊攻撃用
	void UpdateSpecialAttack();
	// 範囲外処理
	void CheckOutSide();
	// ショットを生成
	void UpdateShot();
	// オブジェクトのコスト関連
	void ObjectCost();
private:
	// プレイヤーの位置
	VECTOR m_pos;
	// 特殊攻撃指定場所
	VECTOR m_specialAttackPos;
	// ターゲット位置
	VECTOR m_targetPos;
	// 特殊攻撃をおこなったかどうか
	bool m_isSpecialAttack;
	// 画面から3D空間に変換用
	VECTOR m_start3DPos;
	VECTOR m_end3DPos;
	// 位置を記録します
	std::vector<VECTOR>m_posHistory;
	// false : 押していない true : 押している
	bool m_isResultObject;
	// 設置出来るかの最終確認
	bool m_isSetObject;
	// コスト数
	int m_objectCostNum;
	// ショットの数
	int m_countShotNo;
	bool m_isTrackingShot;
	int m_deleteFrameCountShot;
	// ショットを撃つかどうか
	bool m_isShot;
	// カメラに渡す用のデータ
	Tracking m_trackingData;
	// メニュー表記
	ObjectMenuDrawer* m_pObjMenu;
	// 必殺技(ショット)
	NormalShot* m_pShot;
	// 移動位置を確認
	VECTOR m_checkMapChipNo;

	std::vector<VECTOR> recordChipNo{ VGet(-1, -1, -1) };

	ObstructSelect m_selectObstructData;

	MapDatas m_mapData;
};

