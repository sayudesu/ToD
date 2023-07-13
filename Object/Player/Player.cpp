#include "Player.h"
#include <DxLib.h>
#include "Util/Pad.h"


Player::Player() :
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_screenToWorldPos(VGet(0.0f, 0.0f, 0.0f)),
	m_isResultObject(false),
	m_isSetObject(false)
{
	m_posHistory.push_back(VGet(-1.0f, -1.0f, -1.0f));
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::End()
{
}

void Player::Update()
{
#if false
	// �}�E�X�̈ʒu���擾
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	float speed = 1.0f;
	m_pos.x = static_cast<float>(mouseX) * -speed;
	m_pos.y = static_cast<float>(mouseY) * speed;

	// �}�E�X�����Ă��邩�ǂ���
	// �}�E�X���������ꍇ��ʍ��W����3D��Ԃɕϊ�����
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !m_isMouseLeft)
	{
		const VECTOR pos = VGet(m_pos.x, m_pos.y, 0.0f);
		m_screenToWorldPos = ConvScreenPosToWorldPos(pos);
		m_isMouseLeft = true;
	}
	else
	{
		m_isMouseLeft = false;
	}
#endif
	// ����̐���
	UpdateControl();
}

void Player::Draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + 10, m_pos.y + 10, 0x00ffff, true);

	VECTOR pos = VGet(m_pos.x, m_pos.y + 30.0f, m_pos.z);
	DrawSphere3D(pos, 8, 16, 0xffffff, 0xffffff, true);
}

void Player::UpdateControl()
{
	// �ݒu����w��
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_pos.z += 50.0f;
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_pos.z -= 50.0f;
	}
	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		m_pos.x -= 50.0f;
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		m_pos.x += 50.0f;
	}

	m_isResultObject = false;
	// �ݒu���܂�
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		
		// ���łɂ��̏ꏊ�ɃI�u�W�F�N�g�����݂��Ȃ����m�F
		for (int i = 0; i < m_posHistory.size(); i++)
		{
			if(m_pos.x != m_posHistory[i].x ||
		       m_pos.z != m_posHistory[i].z)
			{
				m_isSetObject = true;
			}
			else
			{
				m_isSetObject = false;
				break;
			}
		}

		// �I�u�W�F�N�g��u�����ꏊ��ۑ�
		if (m_isSetObject)
		{
			m_posHistory.push_back(m_pos);
			m_isResultObject = true;
		}
	}
}
