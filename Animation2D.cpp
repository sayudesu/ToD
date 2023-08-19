#include "Animation2D.h"
#include <DxLib.h>

namespace
{
	// �A�j���[�V�����X�s�[�h�𒲐����܂�
	int m_count = 0;
	// �摜�̕`��ʒu
	int m_imageLeftPosX = 0;
	int m_imageLeftPosY = 0;
	int m_imageRightBottomX = 0;
	int m_imageRightBottomY = 0;

	int m_animCount = 0;
	int m_imageMaxX = 0;
}

namespace Animation2D
{
	void Anim(int leftTopX, int leftTopY, int rightBottomX, int rightBottomY,int animCount,
		      int imageMaxX)
	{
		m_imageLeftPosX = leftTopX;
		m_imageLeftPosY = leftTopY;
		m_imageRightBottomX = rightBottomX;
		m_imageRightBottomY = rightBottomY;

		m_animCount = animCount;
		m_imageMaxX = imageMaxX;
	}

	void Update()
	{
		// �J�E���g
		m_count++;
		// �w�萔�܂ŃJ�E���g�����
		if (m_count > m_animCount)
		{
			// �J�E���g������
			m_count = 0;

			if (m_imageMaxX <= m_imageLeftPosX)
			{
				m_imageLeftPosX = 0;
			}
			else
			{
				m_imageLeftPosX += m_imageRightBottomX;
			}

		}

		printfDx("%d\n", m_imageLeftPosX);
	}

	void Draw(int posX,int posY,int size,float rota,int handle,int trans,bool reverse)
	{
		DrawRectRotaGraph(
			posX,
			posY,//�v���C���[�̈ʒu
			m_imageLeftPosX, m_imageLeftPosY,// �摜�̍���
			m_imageRightBottomX, m_imageRightBottomY,    // �摜�̉E��
			size,	   // �T�C�Y
			rota,			   // ��]�p�x
			handle,		   // �n���h��
			trans,		       // �摜����
			reverse      // �摜���]
		);

	}
}
