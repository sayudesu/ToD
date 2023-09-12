#include "EnemyMouse.h"
#include <cmath>
#include <cassert>
#include <iostream>

namespace
{
	// ファイルデータ
	const char* kFileNameMouse = "Data/Model/Mouse.mv1";

}

EnemyMouse::EnemyMouse()
{	
	// モデルのハンドル
	m_hModel = -1;
	// 移動方向
	m_dir = VGet(0, 0, 0);
	// 体力
	m_hp = 20.0f;
	// 受けるダメージ
	m_damage = 0;
	// 動く場所があるかどうか
	m_isEndPos = false;
	// どこに移動するか
	m_targetPos = VGet(0, 0, 0);
	// 2D座標で体力描画用
	m_screenPos = VGet(0, 0, 0);
	// マップチップのどこにいるか
	m_chipPosX = 0;
	m_chipPosZ = 0;
	// 敵がどこに動くかの処理をするかどうか
	m_isRandMove = false;
	// ファイルパス
	m_filePathModel = kFileNameMouse;
}
EnemyMouse::~EnemyMouse()
{
}

// 当たり判定用データ
CollData EnemyMouse::GetCollDatas()
{
	m_collData.datage   = 0.0f;
	m_collData.pos      = m_pos;
	m_collData.radius   = 16.0f * 2.0f;
	m_collData.isHit    = true;

	return m_collData;
}
