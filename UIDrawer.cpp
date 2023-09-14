#include "UIDrawer.h"
#include "Util/game.h"
#include "Util/LoadGraphFunction.h"
#include "Save/SaveDataFunctions.h"


namespace
{
	// �̗͂�R�X�g��E�F�[�u���̔w�i
	const char* kFileNameBgUtil           = "Data/Image/UI_Up.png";

	// �I�u�W�F�N�g�R�X�g�w�i
	const char* kFileNameBgCost           = "Data/Image/UI_Cost.png";
	// ���摜
	const char* kFileNameMeat             = "Data/Image/UI_Meat.png";
	const char* kFileNameCatFood            = "Data/Image/CatFood.png";
	// ����U���̃{�^������
	const char* kFileNameSpecialAttack    = "Data/Image/UI_SpecialAttack.png";
	const char* kFileNameBarSpecialAttack = "Data/Image/m_hBarTopicSpecialAttack.png";
	const char* kFileNameBgHp             = "Data/Image/UI_BgHP.png";
	const char* kFileNameHp               = "Data/Image/UI_HP.png";
	// �I�u�W�F�N�g�ݒu��
	const char* kFileNameSelectObject     = "Data/Image/UI_SelectObj.png";
	const char* kFileNameSelectCreate     = "Data/Image/UI_SelectObjB.png";
	const char* kFileNameSelectDelete     = "Data/Image/UI_SelectObjA.png";
	const char* kFileNameSelectPowerUp    = "Data/Image/UI_SelectObjY.png";

	const char* kFileNameSelectObstructHevy    = "Data/Image/UI_SelectObstrctY.png";
	const char* kFileNameSelectObstructNormal  = "Data/Image/UI_SelectObstrctB.png";
}

UIDrawer::UIDrawer() :
	m_hBgUtil(-1),
	m_hObjectCost(-1),
	m_hMeat(-1),
	m_hTopicSpecialAttack(-1),
	m_hBarTopicSpecialAttack(-1),
	m_hBgHp(-1),
	m_hHp(-1),
	m_hSelectObject(-1),
	m_costNum(0),
	m_playerPos(VGet(0,0,0))
{
}

UIDrawer::~UIDrawer()
{
}

void UIDrawer::Init()
{
	// �摜�����[�h
	m_hBgUtil	                = LoadGraph(kFileNameBgUtil);
	m_hObjectCost	            = LoadGraph(kFileNameBgCost);
	m_hMeat                     = LoadGraph(kFileNameMeat);
	m_hCatFood                  = LoadGraph(kFileNameCatFood);
	m_hTopicSpecialAttack       = LoadGraph(kFileNameSpecialAttack);
	m_hBarTopicSpecialAttack    = LoadGraph(kFileNameBarSpecialAttack);
	m_hBgHp		                = LoadGraph(kFileNameBgHp);
	m_hHp	                    = LoadGraph(kFileNameHp);
	m_hSelectObject             = LoadGraph(kFileNameSelectObject);
	m_hSelectObjectState[0]     = LoadGraph(kFileNameSelectCreate);
	m_hSelectObjectState[1]     = LoadGraph(kFileNameSelectPowerUp);
	m_hSelectObjectState[2]     = LoadGraph(kFileNameSelectDelete);

	m_hSelectObjectState[3]     = LoadGraph(kFileNameSelectObstructHevy);
	m_hSelectObjectState[4]     = LoadGraph(kFileNameSelectObstructNormal);

	GetGraphSize(m_hBgHp, &m_hpBarX, &m_hpBarY);
}

void UIDrawer::End()
{
}

void UIDrawer::Update()
{
}

void UIDrawer::Draw()
{
	// �̗͂�R�X�g��E�F�[�u���̔w�i
	DrawGraph(0, 0, m_hBgUtil, true);

	Time();

	// �I�u�W�F�N�g�R�X�g�w�i
	DrawGraph(Game::kScreenWidth - 570, 20, m_hObjectCost, true);
	DrawRotaGraph(Game::kScreenWidth - 570 + 40, 20+ 38,0.13f,DX_PI_F * 180.0f, m_hCatFood, true);

	meat();

	// ����U���̃{�^������
	DrawGraph(1150, Game::kScreenHeight - 150 , m_hTopicSpecialAttack, true);
	DrawGraph(1150, Game::kScreenHeight - 150 , m_hTopicSpecialAttack, true);
	// �̗͊֌W
	DrawGraph(120, 20, m_hBgHp, true);

	if (hp < -500)
	{
		m_isDead = true;
	}

	DrawModiGraph(
		120, 20, // ����
		m_hpBarX + 120 + hp, 20,// �E��
		m_hpBarX + 120 + hp, m_hpBarY + 20,//�E��
		120, m_hpBarY + 20,//����
		m_hHp,true);

	// �I�u�W�F�N�g�I��
	for (int i = 0; i < 5; i++)
	{
		if (m_isSelectNo[i])
		{
			DrawGraph(m_selectPos[i].x, m_selectPos[i].y, m_hSelectObject, true);
			DrawGraph(m_selectPos[i].x + 10.0f, m_selectPos[i].y + 10.0f, m_hSelectObjectState[i], true);
		}
	}

	// ���ƂŏC��
	// �A�C�R�����[�h
	static int m_hIcon[8];
	m_hIcon[0] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon0);
	m_hIcon[1] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon1);
	m_hIcon[2] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon2);
	m_hIcon[3] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon3);
	m_hIcon[4] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon4);
	m_hIcon[5] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon5);
	m_hIcon[6] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon6);
	m_hIcon[7] = LoadGraphFunction::GraphData(LoadGraphFunction::Icon7);

	// �A�C�R���`��
	DrawRotaGraph(
		65,
		55,
		0.6f,
		DX_PI_F * 180.0f,
		m_hIcon[SaveDataFunctions::GetIconData().Icon],
		true);


#if false	
	static int UI = LoadGraph("Data/Image/UI_ToDUI.png");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawGraph(0, 0, UI, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
#endif
}

// �I�u�W�F�N�g��ݒu���邽�߂̃R�X�g���󂯎��
void UIDrawer::SetCostSetObject(int cost)
{
	m_costNum = cost;
}

// �v���C���[�̈ʒu���󂯎��
void UIDrawer::SetPlayerPos(VECTOR pos)
{
	// 3D���W����2D���W�ɕϊ�
	if (!m_isSelect)
	{
		m_playerPos = ConvWorldPosToScreenPos(pos);
		for (int i = 0; i < 5; i++)
		{
			m_selectPos[i].x= m_playerPos.x - 80;
			m_selectPos[i].y= m_playerPos.y - 50;

			m_isSelectNo[i] = false;
		}
	}
	else
	{
		m_isSelectNo[0] = true;
		m_isSelectNo[1] = true;
		m_isSelectNo[2] = true;
		m_isSelectNo[3] = false;
		m_isSelectNo[4] = false;

	}
	float speed = 4.0f;

	if (m_obstructData.no == ObstructSelectNo::OBSTRUCT)
	{
		m_isSelectNo[3] = true;
		m_isSelectNo[4] = true;
		if (m_selectPos[3].x > m_playerPos.x)
		{
			m_selectPos[3].x -= speed;
		}
		if (m_selectPos[3].x < m_playerPos.x)
		{
			m_selectPos[3].x += speed;
		}
		if (m_selectPos[3].y > m_selectPos[0].y - 60.0f)
		{
			m_selectPos[3].y -= speed;
		}
		if (m_selectPos[3].y < m_selectPos[0].y - 60.0f)
		{
			m_selectPos[3].y += speed;
		}

		if (m_selectPos[4].x > m_playerPos.x + 20.0f)
		{
			m_selectPos[4].x -= speed;
		}
		if (m_selectPos[4].x < m_playerPos.x + 20.0f)
		{
			m_selectPos[4].x += speed;
		}
		if (m_selectPos[4].y > m_playerPos.y - 30.0f)
		{
			m_selectPos[4].y -= speed;
		}
		if (m_selectPos[4].y < m_playerPos.y - 30.0f)
		{
			m_selectPos[4].y += speed;
		}
	}


	if (m_selectPos[0].x > m_playerPos.x + 20.0f)
	{
		m_selectPos[0].x -= speed;
	}
	if (m_selectPos[0].x < m_playerPos.x + 20.0f)
	{
		m_selectPos[0].x += speed;
	}
	if (m_selectPos[0].y > m_playerPos.y - 30.0f)
	{
		m_selectPos[0].y -= speed;
	}
	if (m_selectPos[0].y < m_playerPos.y - 30.0f)
	{
		m_selectPos[0].y++;
	}
	//m_selectPos[0].x = m_playerPos.x + 20.0f;
	//m_selectPos[0].y = m_playerPos.y - 30.0f;
	if (m_selectPos[1].x > m_playerPos.x)
	{
		m_selectPos[1].x -= speed;
	}
	if (m_selectPos[1].x < m_playerPos.x)
	{
		m_selectPos[1].x += speed;
	}
	if (m_selectPos[1].y > m_selectPos[0].y - 60.0f)
	{
		m_selectPos[1].y -= speed;
	}
	if (m_selectPos[1].y < m_selectPos[0].y - 60.0f)
	{
		m_selectPos[1].y += speed;
	}
	//m_selectPos[1].x = m_playerPos.x;
	//m_selectPos[1].y = m_selectPos[0].y - 60.0f;
	if (m_selectPos[2].x > m_playerPos.x)
	{
		m_selectPos[2].x -= speed;
	}
	if (m_selectPos[2].x < m_playerPos.x)
	{
		m_selectPos[2].x += speed;
	}
	if (m_selectPos[2].y > m_selectPos[0].y + 60.0f)
	{
		m_selectPos[2].y -= speed;
	} 
	if (m_selectPos[2].y < m_selectPos[0].y + 60.0f)
	{
		m_selectPos[2].y += speed;
	}
	//m_selectPos[2].x = m_playerPos.x;
	//m_selectPos[2].y = m_selectPos[0].y + 60.0f;
}

void UIDrawer::SetObstructSelect(bool select)
{
	m_isSelect = select;
}

void UIDrawer::SetObstructData(ObstructSelect data)
{
	m_obstructData = data;
}

void UIDrawer::Time()
{
	//static int time  = 01;
	//static int time2 = 30;
	//static int time3  = 59;
	//static int timeSecond = 9;

	//static int timeCount1 = 0;
	//static int timeCount2 = 0;
	//static int timeCountS2 = 0;

	//static bool notloop   = true;
	//static bool notloop2  = false;
	//static bool notloopS2 = false;

	//static int timerPosChange = 0;

	SetFontSize(128);
	if (notloop) DrawFormatString(Game::kScreenWidth / 2 - 170, 12, 0x000000,   "0%d:%d", time, time2);
	if (notloopS2) DrawFormatString(Game::kScreenWidth / 2 - 170, 12, 0x000000, "0%d:0%d", time, timeSecond);
	if (!notloop && !notloopS2)DrawFormatString(Game::kScreenWidth / 2 - 70 + timerPosChange, 20, 0x000000, "%d", time3);
	SetFontSize(16);

	if (notloop)
	{
		timeCount1++;
		if (timeCount1 > 60)
		{
			time2--;
			timeCount1 = 0;
			if (time2 == 9)
			{
				notloop = false;
				notloopS2 = true;
			}
		}
	}

	if (notloopS2)
	{
		timeCountS2++;
		if (timeCountS2 > 60)
		{
			timeSecond--;
			timeCountS2 = 0;
			if (timeSecond == -1)
			{
				notloop2 = true;
				notloopS2 = false;
			}
		}
	}

	if (notloop2)
	{
		timeCount2++;
		if (timeCount2 > 60)
		{
			time3--;
			timeCount2 = 0;
			if (time3 == -1)
			{
				notloop2 = false;
			}

			if (time3 == 9)
			{
				timerPosChange = 15 + 10;
			}
		}
	}

	if (time3 == 0)
	{
		m_isClear = true;
	}
}

void UIDrawer::meat()
{
	//static int costPos = 0;
	//static bool is1 = true;
	//static bool is2 = true;
	//static bool is3 = true;
	//static bool is4 = true;
	//static bool is5 = true;
	//static bool is6 = true;

	//static bool is1_ = true;
	//static bool is2_ = true;
	//static bool is3_ = true;
	//static bool is4_ = true;
	//static bool is5_ = true;
	//static bool is6_ = true;

	m_costNum += 0;
	SetFontSize(48);
	// �R�X�g��
	DrawFormatString(Game::kScreenWidth - 330 + costPos, 35, 0x000000, "%d", m_costNum);
	SetFontSize(16);

	if(m_costNum > 10 && is1)
	{
		costPos -= 5;
		is1 = false;
	}
	if (m_costNum > 100 && is2)
	{
		costPos -= 5;
		is2 = false;
	}
	if (m_costNum > 100 && is3)
	{
		costPos -= 5;
		is3 = false;
	}
	if (m_costNum > 1000 && is4)
	{
		costPos -= 5;
		is4 = false;
	}
	if (m_costNum > 1000 && is5)
	{
		costPos -= 5;
		is5 = false;
	}
	if (m_costNum > 1000 && is6)
	{
		costPos -= 5;
		is6 = false;
	}


	if (m_costNum < 10 && is1_ && !is1)
	{
		costPos += 5;
		is1_ = false;
		is1 = true;
	}
	if (m_costNum < 100 && is2_ && !is2)
	{
		costPos += 5;
		is2_ = false;
		is2 = true;
	}
	if (m_costNum < 100 && is3_ && !is3)
	{
		costPos += 5;
		is3_ = false;
		is3 = true;
	}
	if (m_costNum < 1000 && is4_ && !is4)
	{
		costPos += 5;
		is4_ = false;
		is4 = true;
	}
	if (m_costNum < 1000 && is5_ && !is5)
	{
		costPos += 5;
		is5_ = false;
		is5 = true;
	}
	if (m_costNum < 1000 && is6_ && !is6)
	{
		costPos += 5;
		is6_ = false;
		is6 = true;
	}
}
