#include "ObstacleHeavyShot.h"
#include "../../Object/Shot/ShotBase.h"
#include "../../Object/Shot/NormalShot.h"
#include "../../Effeck/EffekseerDrawer.h"
#include "../../Util/SoundFunctions.h"
#include <math.h>

namespace
{
	// ショット打ち出しまでのフレーム
	constexpr int kShotFrameCount = 10;
	// モデルの大きさ
	const VECTOR kScale = VGet(1, 1, 1);
	// 角度
	const VECTOR kRotation = VGet(0, 0, 0);
	// 半径
	constexpr float kRadius = 8.0f;
	// 攻撃力
	constexpr float kDamage = 20.0f;
	// 速度
	constexpr float kSpeed = 50.0f;
	// 追跡
	constexpr bool kIsTracking = false;
	// ファイルパス
	const char* kFilePath = "Data/Model/Crossbow.mv1";
}

ObstacleHeavyShot::ObstacleHeavyShot(VECTOR pos, int no):
	ObstacleBase::ObstacleBase(pos,no)
{
	m_pos = pos;
	m_myNo = no;
}

void ObstacleHeavyShot::Init()
{
	// ショットデータ
	m_shotData.shotFrameCount = kShotFrameCount;
	m_shotData.targetPos = VGet(1000, 0, 300);
	m_shotData.rotation = kRotation;
	m_shotData.scale = kScale;
	m_shotData.radius = kRadius;
	m_shotData.damage = kDamage;
	m_shotData.speed = kSpeed;
	m_shotData.isTracking = kIsTracking;
	// 設置音
	SoundFunctions::Play(SoundFunctions::SoundIdSet);
	// 大砲モデルのロード
	m_handle = MV1LoadModel(kFilePath);
	// 大砲モデルの位置
	MV1SetPosition(m_handle, m_pos);
	// 大砲モデルのサイズ変更
	MV1SetScale(m_handle, VGet(1,1,1));
	// 設置用関数に移動
	m_updateFunc = &ObstacleBase::UpdateSetting;
}
