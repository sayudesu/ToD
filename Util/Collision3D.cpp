#include "Collision3D.h"

Collision3D::Collision3D():
	m_pos1Num(-1),
	m_pos2Num(-1),
	m_tempMax1Num(0),
	m_tempMax2Num(0)
{
}

Collision3D::~Collision3D()
{
	
}

bool Collision3D::UpdateCheck(std::vector<VECTOR>pos1, std::vector<VECTOR>pos2)
{
	// ���݂̃|�W�V�����ۑ����̐���ۑ��ꎞ�I�ɕۑ�����
	int tempPos1 = m_pos1Num;
	int tempPos2 = m_pos2Num;

	// �z�񂪑��݂��Ȃ��ꍇ�͈ȉ��̏������s��Ȃ�
	if (pos1.size() == 0)return false;
	if (pos2.size() == 0)return false;

	// �z��̐����ς���Ă��Ȃ��ꍇ�̓J�E���g���Ȃ�
	if (pos1.size() != m_tempMax1Num)m_pos1Num++;
	if (pos2.size() != m_tempMax2Num)m_pos2Num++;

	// pos2���pos1�̕����傫���ꍇ
	if (pos1.size() > pos2.size())
	{
		// �ő�l���Œ�
		if (m_pos1Num == pos1.size())
		{
			m_pos1Num = pos1.size();
		}
	}
	else if (pos1.size() < pos2.size())
	{
		// �ő�l���Œ�
		if (m_pos2Num == pos2.size())
		{
			m_pos2Num = pos2.size();
		}
	}

	// �z��ő吔���ꎞ�I�ɋL�^
	m_tempMax1Num = pos1.size();
	m_tempMax2Num = pos2.size();


	// ���菈��
	const VECTOR vec = VSub(pos1[m_pos1Num], pos2[m_pos2Num]);
	const float del = VSize(vec);
	if (del < 128 * 2 + 68)
	{
		return true;
	}

	return false;
}
