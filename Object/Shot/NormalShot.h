#pragma once
#include "ShotBase.h"

class NormalShot : public ShotBase
{
public:
	NormalShot(VECTOR pos, int originNo,int no);
	~NormalShot();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="handle">   ���f���̃n���h��  </param>
	/// <param name="shotFrameCount"></param>
	/// <param name="taegetPos">�^�[�Q�b�g�ʒu    </param>
	/// <param name="scale">    ���f���̑傫��    </param>
	/// <param name="rotation"> ���f���̊p�x      </param>
	/// <param name="radius">   �����蔻��p�̔��a</param>
	/// <param name="damage">   �U����            </param>
	/// <param name="speed">    ���x              </param>
	/// <param name="isTracking">�Ǐ]�����邩�ǂ���</param>
	void Init(int handle, int shotFrameCount,VECTOR taegetPos, VECTOR scale, VECTOR rotation, float radius, float damage, float speed, bool isTracking)override;
	// ����p�f�[�^
	ObjectData GetCollData()override;
};

