#pragma once
namespace Animation2D
{
	// �A�j���[�V���������܂�
	void Anim(int leftTopX,int leftTopY,int rightBottomX, int rightBottomY, int animCount,
		      int imageMaxX);
	void Update();
	// �`�悳���܂�
	void Draw(int posX, int posY, int size, float rota, int handle, int trans, bool reverse);
}
