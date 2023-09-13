// 2023 Takeru Yui All Rights Reserved.
#pragma once
#include <DxLib.h>

/// <summary>
/// 3D���W��ԂɃX�v���C�g��\������d�g�݁i�s�{�b�g�͒��S�Œ�A�摜��graph�͊O�ŊǗ��j
/// </summary>
class WorldSprite
{
public:
	void Init(int textureGraph, int chipPixelSize, int spriteNo);
	void SetTransform(const VECTOR& pos, float spriteSize);
	void Draw();
	
private:
	int			m_hGraph;	 // �X�v���C�g���쐬���錳�e�N�X�`���̃O���t�B�b�N�n���h��
	VECTOR		m_pos;		 // �`��|�W�V����
	VERTEX3D	m_vertex[4]; // ���_�o�b�t�@S
	WORD		m_index [6]; // �C���f�b�N�X�o�b�t�@
};

