#include "ObstacleHomingMissile.h"
#include "../../Object/Shot/ShotBase.h"
#include "../../Util/SoundFunctions.h"

namespace
{
	// ショット打ち出しまでのフレーム
	constexpr int kShotFrameCount = 5;
	// ショットモデルの大きさ
	const VECTOR kShotScale = VGet(1, 1, 1);
	// 角度
	const VECTOR kRotation = VGet(0, 0, 0);
	// 半径
	constexpr float kRadius = 16.0f;
	// 攻撃力
	constexpr float kDamage = 10.0f;
	// 速度
	constexpr float kSpeed = 50.0f;
	// 追跡
	constexpr bool kIsTracking = true;
	// ファイルパス
	const char* kFilePath     = "Data/Model/Homing.mv1";
	const char* kFilePathShot = "Data/Model/HomingShot.mv1";

	// モデルの大きさ
	const VECTOR kScale = VGet(1, 1, 1);
}

ObstacleHomingMissile::ObstacleHomingMissile(VECTOR pos,int no, int mapCihpX, int mapCihpY):
	ObstacleBase::ObstacleBase(pos,no,mapCihpX,mapCihpY)
{
	m_pos = pos;
	m_myNo = no;
}

void ObstacleHomingMissile::Init()
{
	// ショットデータ
	m_shotData.handle         = MV1LoadModel(kFilePathShot);
	m_shotData.shotFrameCount = kShotFrameCount;
	m_shotData.targetPos      = VGet(1000, 0, 300);
	m_shotData.rotation       = kRotation;
	m_shotData.scale          = kShotScale;
	m_shotData.radius         = kRadius;
	m_shotData.damage         = kDamage;
	m_shotData.speed          = kSpeed;
	m_shotData.isTracking     = kIsTracking;
	m_shotData.id = 1;

	// 大砲モデルのロード
	m_handle = MV1LoadModel(kFilePath);
	// 大砲モデルの位置
	MV1SetPosition(m_handle, m_pos);
	// 大砲モデルのサイズ変更
	MV1SetScale(m_handle, kScale);
	// 設置用関数に移動
	m_updateFunc = &ObstacleBase::UpdateSetting;

	// 設置音
	SoundFunctions::Play(SoundFunctions::SoundIdSet);
}
