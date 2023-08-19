#include "Animation2D.h"
#include <DxLib.h>

namespace
{
	// アニメーションスピードを調整します
	int m_count = 0;
	// 画像の描画位置
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
		// カウント
		m_count++;
		// 指定数までカウントすると
		if (m_count > m_animCount)
		{
			// カウント初期化
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
			posY,//プレイヤーの位置
			m_imageLeftPosX, m_imageLeftPosY,// 画像の左上
			m_imageRightBottomX, m_imageRightBottomY,    // 画像の右下
			size,	   // サイズ
			rota,			   // 回転角度
			handle,		   // ハンドル
			trans,		       // 画像透過
			reverse      // 画像反転
		);

	}
}
