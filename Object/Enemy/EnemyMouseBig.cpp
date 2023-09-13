#include "EnemyMouseBig.h"
#include <cmath>
#include <cassert>
#include <iostream>

namespace
{
	// ファイルデータ
	const char* kFileNameMouse = "Data/Model/MouseR.mv1";
	// 速度
	constexpr float kSpeed = 1.0f;
	// 大きさ
	constexpr float kSize = 3.0f;

}

EnemyMouseBig::EnemyMouseBig()
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

	m_collData.datage = 0.0f;
	m_collData.pos = m_pos;
	m_collData.radius = 16.0f * 2.0f;
	m_collData.speed = kSpeed;
	m_collData.size = kSize;
	m_collData.hp = 1000;
	m_collData.isHit = true;
	m_collData.isAttack = false;
}
EnemyMouseBig::~EnemyMouseBig()
{
}

void EnemyMouseBig::Attack()
{
	m_collData.isAttack = false;
	m_attackCount++;
	if (m_attackCount == 10)
	{
		m_pos.x += 10.0f;
		m_collData.isAttack = true;
	}
	if (m_attackCount == 20)
	{
		m_pos.x -= 10.0f;
		m_attackCount = 0;

	}

	MV1SetPosition(m_hModel, m_pos);
}

// 当たり判定用データ
ObjectData EnemyMouseBig::GetCollDatas()
{
	m_collData.datage   = 30.0f;
	m_collData.pos      = m_pos;
	m_collData.radius   = 16.0f * 5.0f;
	m_collData.speed	= kSpeed;
	m_collData.size     = 3;
	m_collData.isHit    = true;

	return m_collData;
}