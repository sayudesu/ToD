#include "ObjectMenuDrawer.h"
#include "../../Util/Pad.h"
#include <DxLib.h>
#include "../../Util/game.h"

ObjectMenuDrawer::ObjectMenuDrawer():
	m_hObjMenuFrame(-1),
	m_isMenu(false),
	m_select(0),
	m_checkSelect(-1),
	m_slierY(Game::kScreenHeight)
{
	for (int i = 0; i < 3; i++)
	{
		m_hObject[i] = -1;
		m_hObjectSize[i] = 1.0f;
	}
}

ObjectMenuDrawer::~ObjectMenuDrawer()
{
}

void ObjectMenuDrawer::Init()
{
	m_hObjMenuFrame = LoadGraph("Data/Image/FrameCat.png");
	//m_hObject[0] = LoadGraph("Data/Image/ObjCat.png");
	//m_hObject[1] = LoadGraph("Data/Image/Icon0.png");
	//m_hObject[2] = LoadGraph("Data/Image/Icon1.png");
}

void ObjectMenuDrawer::End()
{
	DeleteGraph(m_hObjMenuFrame);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(m_hObject[i]);
	}
}

void ObjectMenuDrawer::Update()
{
	// ���j���[���J���Ă���ꍇ
	if (Pad::isPress(PAD_INPUT_6))
	{
		// �Ȃɂ��I�����Ă���ꍇ
		if(m_checkSelect == -1)m_isMenu = true;

		// �I��
		if (Pad::isTrigger(PAD_INPUT_LEFT))
		{
			if(m_select > 0)m_select--;
		}
		if (Pad::isTrigger(PAD_INPUT_RIGHT))
		{
			if (m_select < 3-1)m_select++;
		}
		// ����
		if (Pad::isPress(PAD_INPUT_1))
		{
			// �I�������ԍ�����
			m_checkSelect = m_select;
			// ���j���[���\���ɂ���
			m_isMenu = false;
		}
	}
	else
	{
		m_isMenu = false;
	}

	// �X���C�h����
	if (m_isMenu)
	{
		if (m_slierY > 0)m_slierY -= 50;
	}
	else
	{
		if (m_slierY < Game::kScreenHeight)m_slierY += 50;
	}

	// �T�C�Y�ύX
	// �S�Ă������̃T�C�Y�ɖ߂�
	for (int i = 0; i < 3; i++)
	{
		m_hObjectSize[i] = 1.0f;
	}
	// �I�𒆂̕������T�C�Y��ς���
	m_hObjectSize[m_select] = 1.5f;
}

void ObjectMenuDrawer::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
	// �w�i��`�悷��
	DrawBox(
		300,
		(Game::kScreenHeight / 2 + 160) + m_slierY,
		Game::kScreenWidth - 300,
		Game::kScreenHeight + m_slierY,
		0xffffff,
		true);

	const int frameSpace = 180;
	const int frameNum = 3;

	for (int i = 0; i < frameNum; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
		// �t���[����`�悳����
		DrawRotaGraph(
			(Game::kScreenWidth / 2) +(frameSpace * i) - frameSpace,
			(Game::kScreenHeight / 2 + 350) + m_slierY,
			1 * m_hObjectSize[i],
			DX_PI_F * 180.0f,
			m_hObjMenuFrame,
			true
		);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		// �摜��`�悳����
		DrawRotaGraph(
			Game::kScreenWidth / 2 + (frameSpace * i) - frameSpace,
			(Game::kScreenHeight / 2 + 350) + m_slierY,
			0.1 * m_hObjectSize[i],
			DX_PI_F * 180.0f,
			m_hObject[i],
			true
		);
	}
	
}

// ���j���[���J���Ă��邩�ǂ���
bool ObjectMenuDrawer::IsSetMenu()
{
	return m_isMenu;
}
// �I�������肵���ԍ���Ԃ�
int ObjectMenuDrawer::SelectNo()
{
	return m_checkSelect;
}

// �I�������ԍ������Z�b�g����
void ObjectMenuDrawer::ResetSelectNo()
{
	m_checkSelect = -1;
}
