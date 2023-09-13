#include "MapDrawer.h"
#include <DxLib.h>
#include <cassert>
#include "WorldSprite.h"

namespace
{

    const char* kDataPath = "Data/Save/MapData.csv";

    // �}�b�v�`�b�v�T�C�Y
    constexpr int kMapChipMaxZ = 13;// �s
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
    static int count = -1;

    // WorldSprite���̐ݒ�ƈʒu������
    // �}�b�v�̕`��J�n�ʒu�i����j
    // �s
    VECTOR chipLeftTopPos = VGet(0, 0, kMapChipMaxZ * 50.0f);

    for (int z = 0; z < kMapChipMaxZ; ++z)
    {
        // ��
        for (int x = 0; x < kMapChipMaxX; ++x)
        {
            count++;
            // �C���X�^���X����
            m_pSprite.push_back(new WorldSprite());
            m_pSprite[count]->Init(gprah, kMapCihpSize, m_loadData[count]);
            // �}�b�v�`�b�v�̔����T�C�Y�����ɂ��炷�I�t�Z�b�g
           // VECTOR chipHalfOffset = VGet(-kBlockSize * 0.5f, 0, -kBlockSize * 0.5f);
            // �^�񒆃s�{�b�g�Ȃ̂Ń}�b�v�`�b�v�����T�C�Y���炷+�n�ʂȂ̂ň����
            VECTOR chipPos = VAdd(VGet(x * kBlockSize, 0, (-z - 1) * kBlockSize), VGet(0,0,0));
            chipPos = VAdd(chipPos, chipLeftTopPos);
            // �ʒu��ݒ�
            m_pSprite[count]->SetTransform(chipPos, kBlockSize);
        }
    }
    count = 0;
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

void MapDrawer::Update()
{
  
}

void MapDrawer::Draw()
{
    VECTOR m_pos{};
    m_pos.y = -kBlockSize + 20.0f;
#if false   
    // �s
    for (int z = 0; z < kMapChipMaxZ; ++z)
    {
        // ��
        for (int x = 0; x < kMapChipMaxX; ++x)
        {
            // [���݂̗� + ���݂̗� * �`�b�v�ő��]
            if (m_loadData[x + z * kMapChipMaxX] == 1)
            {
                m_pos.x = (x * kBlockSize);
                m_pos.z = (z * kBlockSize);
                MV1SetPosition(m_hBlock, m_pos);
                MV1DrawModel(m_hBlock);
            }
            // [���݂̗� + ���݂̗� * �`�b�v�ő��]
            if (m_loadData[x + z * kMapChipMaxX] == 2)
            {
                //// �G�̈ʒu�ɑ��
                m_pos.x = (x * kBlockSize);
                m_pos.z = (z * kBlockSize);
                MV1SetPosition(m_hEnemyRoad, m_pos);
                MV1DrawModel(m_hEnemyRoad);
            }
            // [���݂̗� + ���݂̗� * �`�b�v�ő��]
            if (m_loadData[x + z * kMapChipMaxX] == 3)
            {
                m_pos.x = (x * kBlockSize);
                m_pos.z = (z * kBlockSize);
                MV1SetPosition(m_hEnemySpawner, m_pos);
                MV1DrawModel(m_hEnemySpawner);
            }
            // [���݂̗� + ���݂̗� * �`�b�v�ő��]
            if (m_loadData[x + z * kMapChipMaxX] == 4)
            {
                m_pos.x = (x * kBlockSize);
                m_pos.z = (z * kBlockSize);
                MV1SetPosition(m_hEnemyStop, m_pos);
                MV1DrawModel(m_hEnemyStop);
            }

        }
    }
#endif

    for(auto& sprite : m_pSprite)
    {
       sprite->Draw();
    }
}

// �f�[�^�ۊ�
std::vector<int> MapDrawer::GetMapChip()
{
    return m_loadData;
}