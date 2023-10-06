#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/Vec2.h"
#include "../../Util/Tracking.h"
#include "../../Util/ObstructSelectNo.h"
#include "../../MapDatas.h"
#include "../../Util/ObjectData.h"

// プレイヤークラス
class Player
{
public:
	Player();
	virtual ~Player();

	// 初期化処理
	void Init(MapDatas mapChip);
	// メモリ開放処理
	void End();
	// 更新処理
	void Update();
	// 描画
	void Draw();
	// プレイヤーの位置を渡す
	VECTOR SetPos() { return m_pos; }
	// マウスが押されているかどうか
	bool GetObjCreate() { return m_isResultObject; }
	// カメラクラスに渡す
	Tracking GetTracingData();
	// 現在のオブジェクトコストを渡す
	int GetObjectCostNum();

	// 選択中の状態を渡す
	ObstructSelect GetObstructData();

	ObjectData GetCollShotDatas();

	// マップチップ上の座標を渡す
	int GetMapChipX();
	int GetMapChipZ();

private:
	// 操作を制御
	void UpdateControl();
	void UpdateObjSelect();
	// 範囲外処理
	bool CheckOutSide();
	// オブジェクトのコスト関連
	void ObjectCost();
private:
	// プレイヤーの位置
	VECTOR m_pos;
	// ターゲット位置
	VECTOR m_targetPos;
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
	// 移動位置を確認
	VECTOR m_checkMapChipNo;

	ObstructSelect m_selectObstructData;

	MapDatas m_mapData;

	ObjectData m_collShotData;

	bool m_isSelectPowerUp;
};

