#include "LoadGraphfunction.h"
#include <vector>
#include <DxLib.h>
#include <cassert>

namespace
{
    // �摜�n���h��
    std::vector<int> graphHandle{};

    // �摜�t�@�C����
    const char* const kFileName[LoadGraphFunction::GraphIdMaxNum] =
    {
        "Data/Image/SelectVol_B.png",// �L�̉摜�p�X
        "Data/Image/SelectVol_S.png",// ����������
        "Data/Image/Wood.png",// �w�i�摜�p�X
        "Data/Image/GBar.png",// ���[�^�[�摜�p�X   
        "Data/Image/OutSideBar.png",// �O���̃��[�^�[�摜�p�X   
        "Data/Image/OutSideBarBg.png",// �O���̃��[�^�[�摜�p�X   
        "Data/Image/SelectFrame.png",// �I��p�g
        "Data/Image/nikukyu_S.png",// �I��p����
    };
}

namespace LoadGraphFunction
{
    // �摜�����[�h���܂�
    void LoadGraphFunction::Load()
    {
        // �T�E���h�f�[�^�̓ǂݍ���
        for (auto& fileName : kFileName)
        {
            int handle = LoadGraph(fileName);
            assert(handle != -1);
            graphHandle.push_back(handle);
        }
    }

    // ���������
    void LoadGraphFunction::UnLoad()
    {
        // �T�E���h�f�[�^�̓ǂݍ���
        for (auto& graphData : graphHandle)
        {
            DeleteGraph(graphData);
        }
    }

    // �摜�f�[�^��n��
    int LoadGraphFunction::GraphData(GraphId name)
    {
        return graphHandle[name];
    }
}