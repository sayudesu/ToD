#include "MapDrawer.h"
#include <DxLib.h>
#include <cassert>

namespace
{

    const char* kDataPath = "Data/Save/MapData.csv";
}

MapDrawer::MapDrawer():
    m_hBlock(-1),
    m_hEnemyRoad(-1),
    m_hEnemySpawner(-1),
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


    int puls = -1;
    int z = 250;
    int x = 0;

    for (int i = 0; i < m_loadData.size(); i++)
    {
        // �J�E���g
        puls++;
        // �E�ɉ����l�߂�
        //int x = -600;
        x = 0;
        x += (puls * 50) - 600;

        // Z���ύX
        if (m_loadData[i] == 0)
        {
            puls = -1;
            z -= 50;
        }

        // �ۑ�
        m_objPosX.push_back(x);
        m_objPosZ.push_back(z);
    }

    // ���f�����[�h
    m_hBlock        = MV1LoadModel("Data/Model/NormalBlock2.mv1");
    m_hEnemyRoad    = MV1LoadModel("Data/Model/EnemyRoad.mv1");
    m_hEnemySpawner = MV1LoadModel("Data/Model/EnemySpawner.mv1");
}

void MapDrawer::End()
{
}

void MapDrawer::Update()
{
}

void MapDrawer::Draw()
{
    for (int i = 0; i < m_loadData.size(); i++)
    {
        // �n�ʃu���b�N
        if (m_loadData[i] == 1)
        {
            VECTOR pos = VGet(m_objPosX[i], -25.0f, m_objPosZ[i]);
            MV1SetPosition(m_hBlock, pos);
            // �I�u�W�F�N�g�`��
            MV1DrawModel(m_hBlock);
            continue;
        }
        // �G�̓�
        if (m_loadData[i] == 2)
        {
            VECTOR pos = VGet(m_objPosX[i], -25.0f, m_objPosZ[i]);
            MV1SetPosition(m_hEnemyRoad, pos);
            // �I�u�W�F�N�g�`��
            MV1DrawModel(m_hEnemyRoad);
            continue;
        }
        // �G�̃X�|�[���ʒu
        if (m_loadData[i] == 3)
        {
            VECTOR pos = VGet(m_objPosX[i], -25.0f, m_objPosZ[i]);
            MV1SetPosition(m_hEnemySpawner, pos);
            // �I�u�W�F�N�g�`��
            MV1DrawModel(m_hEnemySpawner);
            continue;
        }
    }
}

std::vector<int> MapDrawer::GetMapChip()
{
    return m_loadData;
}

std::vector<int> MapDrawer::GetMapChipX()
{
    return m_objPosX;
}

std::vector<int> MapDrawer::GetMapChipZ()
{
    return m_objPosZ;
}
