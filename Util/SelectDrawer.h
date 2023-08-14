#pragma once
#include "Vec2.h"
#include <vector>
#include <memory>


namespace
{
	// �L�̎�
	constexpr int kCatHandNum = 2;
}


class StringDrawer;

/// ������`�悳����N���X
class SelectDrawer
{
public:
	SelectDrawer();
	virtual ~SelectDrawer();

	/// <summary>
	/// �e�L�X�g�̐�����Text�N���X���C���X�^���X���쐬����
	/// </summary>
	/// <param name="frameX">    �g�̈ʒuX  </param>
	/// <param name="frameY">    �g�̈ʒuY  </param>
	/// <param name="stringX">   �g�̈ʒuX����̕����ʒu  </param>
	/// <param name="stringY">   �g�̈ʒuY����̕����ʒu  </param>
	/// <param name="text">		 ����  </param>
	/// <param name="color">	 �F	   </param>
	/// <param name="size">		 �T�C�Y</param>
	void Add(int frameX, int frameY, int stringX, int stringY, const char* text, int color, int size);

	// ���������
	void End();

	/// �p�b�h���͂̍X�V����
	void Update();

	// ���W��ύX���܂�
	void UpdatePos(int x, int y);

	// �L�̎�̈ʒu��ύX���܂�
	void UpdateCatHandPos();

	/// �e�L�X�g��`�悷��
	void Draw();

	// �Z���N�g�i���o�[�����Z�b�g����
	void ResetSelectNo();

	/// <summary>
	/// �I�������ԍ�
	/// </summary>
	/// <returns>���Ԗڂ�I����������Ԃ�</returns>
	int GetSelectNo();

	/// <summary>
	/// ���ݑI�𒆂̔ԍ�
	/// </summary>
	/// <returns>���ݑI�𒆂̔ԍ���Ԃ�</returns>
	int GetSelectNowNo();

private:
	// �e�L�X�g�`��p�N���X
	std::vector<std::shared_ptr<StringDrawer>> m_pText;
	// �I���������ǂ���
	bool m_isSelect;
	// �I�����̐�
	int selectNum;
	int selectNow;
	int m_selectNo;
	// �~�̔��a
	int selectRad;

	// �L�̎�̈ʒu
	int m_catHandPosX[kCatHandNum];
	int m_catHandPosY;
};

class StringDrawer
{
public:
	/// <summary>
	/// �e�L�X�g�쐬
	/// </summary>
	/// <param name="frameX">    �g�̈ʒuX  </param>
	/// <param name="frameY">    �g�̈ʒuY  </param>
	/// <param name="stringX">   �g�̈ʒuX����̕����ʒu  </param>
	/// <param name="stringY">   �g�̈ʒuY����̕����ʒu  </param>
	/// <param name="text">		 ����  </param>
	/// <param name="color">	 �F	   </param>
	/// <param name="size">		 �T�C�Y</param>
	/// <param name="frameHnadle">		 �����g�̉摜�n���h��</param>
	StringDrawer(int frameX, int frameY, int stringX, int stringY, const char* text, int color, int size,int frameHnadle,int selectHandle);
	virtual ~StringDrawer();
	void UpdatePos(int x, int y);
	void Draw();

	void SetSelectRadius(int rad);
	void SetBlendMode(int blendLevel);

	int GetFramePosX();
	int GetFramePosY();
private:
	// �ʒu
	int m_frameX;
	int m_frameY;
	// �ʒu
	int m_stringX;
	int m_stringY;
	// ���̈ʒu���炸�炷�p
	int m_changePosX;
	int m_changePosY;
	// �X���C�h�p�ϐ�
	int m_slideY;
	// ����
	const char* m_text;
	// �F
	int m_color;
	// �g��\�����邩�ǂ���
	bool m_isFrame;
	// �����f�[�^
	int m_fontHandle;
	// �I�����Ă邩�ǂ���
	bool m_isSelect;
	// �I����̃G�t�F�N�g�~�̑傫��
	int m_rad;
	// �u�����h��
	int m_blend;
	// �I���摜�p�n���h��
	int m_hSelectFrame;
};

