#pragma once

namespace LoadGraphFunction
{
	typedef enum GraphId
	{
		// �摜�̖��O
		VolCat,
		VolCatS,
		Wood,
		Bar,
		OutSideBar,
		OutSideBarBg,
		SelectFrame,
		SelectCatHand,

		// �ő吔
		GraphIdMaxNum
	}GraphId;

	// �摜�����[�h���܂�
	void Load();
	// ��������������܂�
	void UnLoad();
	// �摜�f�[�^��n��
	int GraphData(GraphId name);
}

