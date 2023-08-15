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
		Icon0,
		Icon1,
		Icon2,
		Icon3,
		Icon4,
		Icon5,
		Icon6,
		Icon7,
		GamePad,

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

