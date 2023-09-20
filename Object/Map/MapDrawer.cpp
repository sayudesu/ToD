#include "MapDrawer.h"
#include <DxLib.h>
#include <cassert>
#include "WorldSprite.h"

namespace
{
#if false
    const char* kDataPath = "Data/Save/T_MapData.csv";
#else
    const char* kDataPath = "Data/Save/MapData.csv";
#endif
    // �}�b�v�`�b�v�T�C�Y
    constexpr int kMapChipMaxZ = 50;// �s
    constexpr int kMapChipMaxX = 25;// ��
    // �}�b�v�`�b�v�i���o�[(�G�̓�)
    constexpr int kEnemyRoad = 2;
    // �u���b�N1�̑傫��
    constexpr float kBlockSize = 50.0f;
    // �}�b�v�`�b�v�摜�T�C�Y
    constexpr float kMapCihpSize = 32.0f;
}

MapDrawer::MapDrawer():
    m_hBlock(-1),
    m_hEnemyRoad(-1),
    m_hEnemySpawner(-1),
    m_hEnemyStop(-1),
    m_dataNum(-1)
{
 
}

MapDrawer::~MapDrawer()
{

}

void MapDrawer::Init()
{
    // csv�t�@�C����ǂݍ���Ő����̔z��ɂ�����
    FILE* fp;
    // �t�@�C�������邩�ǂ���
    bool isFileCheck = true;

    if (fopen_s(&fp, kDataPath, "rt") != 0)
    {
        if (fopen_s(&fp, kDataPath, "rt"))return;
    }

    int chr;
    // ���m��
    int wNum = -1;
    // ���̗v�f��������p
    int tempW = 0;

    int tempNum = 0;

    while (true)
    {
        chr = fgetc(fp);    // 1�����ǂݍ���

        // ��؂蕶������������
        if (chr == ',' || chr == '\n' || chr == EOF)
        {

            // m_loadData�Ƀf�[�^������
            m_loadData.push_back(tempNum);

            m_dataNum++;
            tempNum = 0;

            // �t�@�C���̏I�[�ɗ�����I��
            if (chr == EOF)
            {
                break;
            }
            else if (chr == ',')
            {
                tempW++;    // �v�f��������
            }
            else   // chr == '\n'
            {
                tempW++;    // �v�f��������
                if (wNum < 0)
                {
                    wNum = tempW;    // �v�f���m��
                }
                /*else
                {
                    assert(wNum == tempW);
                }*/
                tempW = 0;
            }
            // �܂��I����ĂȂ��̂ő����ēǂݍ���
            continue;
        }

        // �f�[�^�͐����݂̂̂͂�
        assert(chr >= '0' && chr <= '9');

        // �����Ȃ̂͊m��
        // ������𐔒l�ɕϊ�������
        // 268��ǂݍ���
        // 1�����ڂ�'2'    ����𐔒l�ɕϊ����Ă����
        // 2�����ڂ�'6'    tempNum��2 20 + 6  tempNum = 26
        // 3�����ڂ�'8' tempNum��26 260+ 8 tempNum = 268
        tempNum = (tempNum * 10) + chr - '0';

        // �f�[�^�̋�؂肪�����������_�ł����܂ł��f�[�^�̂ЂƂ܂Ƃ܂�

    }
    // �t�@�C�������
    fclose(fp);

    //// ���f�����[�h
    //m_hBlock        = MV1LoadModel("Data/Model/NormalBlock2.mv1");
    //m_hEnemyRoad    = MV1LoadModel("Data/Model/EnemyRoad.mv1");
    //m_hEnemySpawner = MV1LoadModel("Data/Model/EnemySpawner.mv1");
    //m_hEnemyStop    = MV1LoadModel("Data/Model/EnemyStop.mv1");


    int gprah = LoadGraph("mapData.png");
    m_dataNum = -1;
    // WorldSprite���̐ݒ�ƈʒu������
    // �}�b�v�̕`��J�n�ʒu�i����j
    // �s
    VECTOR chipLeftTopPos = VGet(0, 0, kMapChipMaxZ * 50.0f);

    for (int z = 0; z < kMapChipMaxZ; ++z)
    {
        // ��
        for (int x = 0; x < kMapChipMaxX; ++x)
        {
            m_dataNum++;
            // �C���X�^���X����
            m_pSprite.push_back(new WorldSprite());
            m_pSprite[m_dataNum]->Init(gprah, kMapCihpSize, m_loadData[m_dataNum]);
            // �}�b�v�`�b�v�̔����T�C�Y�����ɂ��炷�I�t�Z�b�g
           // VECTOR chipHalfOffset = VGet(-kBlockSize * 0.5f, 0, -kBlockSize * 0.5f);
            // �^�񒆃s�{�b�g�Ȃ̂Ń}�b�v�`�b�v�����T�C�Y���炷+�n�ʂȂ̂ň����
            VECTOR chipPos = VAdd(VGet(x * kBlockSize, 0, (-z - 1) * kBlockSize), VGet(0,0,0));
            chipPos = VAdd(chipPos, chipLeftTopPos);
            // �ʒu��ݒ�
            m_pSprite[m_dataNum]->SetTransform(chipPos, kBlockSize);
        }
    }
    m_data.chipMaxX = kMapChipMaxX;
    m_data.chipMaxZ = kMapChipMaxZ;
    m_data.chipSizeX = kMapCihpSize;
    m_data.chipSizeZ = kMapCihpSize;
    m_data.road         = 1;
    m_data.enemyRoad    = 2;
    m_data.enemySpawner = 3;
    m_data.enemyStop    = 4;
    m_data.blockSizeY = kBlockSize;
    m_data.blockSizeZ = kBlockSize;
    m_data.data = m_loadData;
}

void MapDrawer::End()
{
    for (int i = 0; i < m_pSprite.size(); i++)
    {
        delete m_pSprite[i];
        m_pSprite[i] = nullptr;
    }
    m_pSprite.clear();
}

void MapDrawer::Draw()
{
    for(auto& sprite : m_pSprite)
    {
       sprite->Draw();
    }
}

// �f�[�^�ۊ�
MapDatas MapDrawer::GetChip()
{
    return m_data;
}