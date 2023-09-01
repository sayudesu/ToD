#include "ManualDrawer.h"
#include <DxLib.h>
#include "../Util/game.h"
#include "../Util/Pad.h"
#include "../Util/SelectDrawer.h"
#include "../Util/SoundFunctions.h"
#include "../SaveDataFunctions.h"
#include "../Util/LoadGraphFunction.h"

namespace
{
	// �L�̉摜�̑���
	constexpr int kVolCatSpeed = 20;
	// �X���C�h�̑���
	constexpr int kSlideSpeed = 50;

	// 3
	constexpr int kFrame3PosX = Game::kScreenWidth / 2;
	constexpr int kFrame3PosY = Game::kScreenHeight / 2 + 350;
	constexpr int kString3PosX = -200;
	constexpr int kString3PosY = -25;
	const char* kStringSettingEnd = "����";
	constexpr int kString3Color = 0xffffff;
	constexpr int kString3Size = 52;
}

ManualDrawer::ManualDrawer():
	m_isSetingEnd(false),
	m_slideY(-Game::kScreenHeight)
{
	// �I��p�N���X�̃C���X�^���X
	m_pSelect = new SelectDrawer;

	// �ݒu�p�֐��Ɉړ�
	m_updateFunc = &PauseBase::UpdateStart;
}

ManualDrawer::~ManualDrawer()
{
	delete m_pSelect;
}

void ManualDrawer::Init()
{

	m_pSelect->Add(
		kFrame3PosX,
		kFrame3PosY,
		kString3PosX,
		kString3PosY,
		kStringSettingEnd,
		kString3Color,
		kString3Size
	);
}

void ManualDrawer::End()
{
}

void ManualDrawer::Update()
{
	(this->*m_updateFunc)();
}

void ManualDrawer::Draw()
{
	// �w�i�摜
	DrawExtendGraph(
		0,
		0 + m_slideY,
		Game::kScreenWidth - 0,
		Game::kScreenHeight + 100 + m_slideY,
		LoadGraphFunction::GraphData(LoadGraphFunction::Wood),
		true);

	DrawRotaGraph(
		Game::kScreenWidth / 2,
		Game::kScreenHeight / 2 + m_slideY,
		1,
		DX_PI_F * 180.0f,
		LoadGraphFunction::GraphData(LoadGraphFunction::GamePad),
		true);

	m_pSelect->Draw();
}

/// <returns>�ݒ��ʂ��I������ǂ���</returns>
bool ManualDrawer::GetSettingEnd()
{
	return m_isSetingEnd;
}


void ManualDrawer::UpdateStart()
{
	// �X���C�h���܂�
	m_slideY += kSlideSpeed;

	m_pSelect->UpdatePos(0,m_slideY);

	// �X���C�h���I���Ɗ֐����ړ�
	if (m_slideY > 0)
	{
		// �X���C�h�̒l��0�ɒ���
		m_slideY = 0;
		// Main�p�֐��Ɉړ�
		m_updateFunc = &PauseBase::UpdateMain;
	}
	m_isSetingEnd = false;	
}

void ManualDrawer::UpdateMain()
{
	m_pSelect->Update();

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		// �T�E���h�Đ�
		SoundFunctions::Play(SoundFunctions::SoundIdSelct);
		// End�p�֐��Ɉړ�
		m_updateFunc = &PauseBase::UpdateEnd;
	}

	// �����I������Ɛݒ��ʂ��I�������Ɉڍs���܂�
	if (m_pSelect->GetSelectNo() == 0)
	{
		// End�p�֐��Ɉړ�
		m_updateFunc = &PauseBase::UpdateEnd;
	}
	else
	{
		m_isSetingEnd = false;
	}
}

void ManualDrawer::UpdateEnd()
{
	m_slideY -= kSlideSpeed;

	m_pSelect->UpdatePos(0, m_slideY);

	if (m_slideY < -Game::kScreenHeight)
	{
		// �ϐ��̏�����
		Reset();
		// �G���h�������I����Ă��邩�ǂ���
		m_isSetingEnd = true;
		// �I�������Z�b�g���܂�
		m_pSelect->ResetSelectNo();
	}
}


void ManualDrawer::Reset()
{
	// Main�p�֐��Ɉړ�
	m_updateFunc = &PauseBase::UpdateStart;
	// �X���C�h�̒l��������
	m_slideY = -Game::kScreenHeight;
}


