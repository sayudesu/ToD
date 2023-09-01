#pragma once
class ObjectMenuDrawer
{
public:
	ObjectMenuDrawer();
	~ObjectMenuDrawer();
	
	void Init();
	void End();
	void Update();
	void Draw();

	// ���j���[���J���Ă��邩�ǂ���
	bool IsSetMenu();
	// �I�������肵���ԍ���Ԃ�
	int SelectNo();
	// �I�������ԍ������Z�b�g����
	void ResetSelectNo();
private:
	// �I�u�W�F�N�g���j���[�摜�n���h��
	int m_hObjMenuFrame;
	// �I�u�W�F�N�g�摜
	int m_hObject[3];
	// �I�u�W�F�N�g�T�C�Y
	float m_hObjectSize[3];
	// ���j���[���J���Ă��邩�ǂ���
	bool m_isMenu;
	// ���j���[�I��p
	int m_select;
	int m_checkSelect;
	// �X���C�h�̒l
	int m_slierY;
};

