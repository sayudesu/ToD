#include "ShotBase.h"
#include <cmath>
#include "../../Util/SoundFunctions.h"

namespace
{
	constexpr float kSpeed = 10.0f;
}

ShotBase::ShotBase(VECTOR pos):
	m_pos(pos),
	m_targetPos(VGet(0,0,0)),
	m_isScreenOut(false)
{
	SoundFunctions::Play(SoundFunctions::SoundIdShot);
}

ShotBase::~ShotBase()
{
}

void ShotBase::Update()
{
	if (!m_isScreenOut)
	{
		VecCalculation();
	}
}

void ShotBase::Draw()
{
	if (!m_isScreenOut)
	{
		DrawSphere3D(m_pos, 8, 8, 0x00ff00, 0x00ff00, true);
	}
}

// ˆÚ“®‚ÌŒvŽZ‚ð‚µ‚Ä‚¢‚Ü‚·
void ShotBase::VecCalculation()
{
	//**** ’Ç]‚ÌAI ****//
	// Œü‚«‚ðŽZo
	m_dir = VSub(m_targetPos, m_pos);
	// ƒvƒŒƒCƒ„[‚©‚çƒGƒlƒ~[‚Ü‚Å‚ÌŠp“x‚ð‹‚ß‚é
	const float angle = atan2(m_dir.y, m_dir.x);
	// Œ»Ý“G‚ªŒü‚¢‚Ä‚¢‚é•ûŒü‚ÌƒxƒNƒgƒ‹‚ð¶¬‚·‚é
	const MATRIX enemyRotMtx = MGetRotY(angle);
	const VECTOR dir = VTransform(VGet(0, 0, 0), enemyRotMtx);
	// ŽÎ‚ß‚É‚È‚Á‚½‚Æ‚«((1, 1, 0)‚È‚Ç)‚É‚¢‚Á‚½‚ñ’·‚³‚P‚É–ß‚·(³‹K‰»)
	if (VSquareSize(m_dir) > 0)
	{
		m_dir = VNorm(m_dir);
	}
	// ‘¬“x‚ð‹‚ß‚é
	const VECTOR velecity = VScale(m_dir, kSpeed);
	// ˆÊ’u‚ð•Ï‚¦‚é
	m_pos = VAdd(m_pos, velecity);
	//	m_pModel->SetPos(m_pos);
	//	m_pModel->SetRot(VGet(0, m_pPlayer->GetDir().y, 0));
}
