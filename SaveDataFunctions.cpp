#include "SaveDataFunctions.h"
#include <DxLib.h>
#include <cassert>

#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace
{
    // �O���t�@�C���ǂݍ��ݗp
    std::vector<int> m_loadData;
    // 
    GameData::Sound m_saveData;
    GameData::Sound m_soundBarData;
    // �f�[�^���J�E���g
    int dataNum = -1;
}

namespace SaveDataFunctions
{
    void Load()
    {
        // csv�t�@�C����ǂݍ���Ő����̔z��ɂ�����
        FILE* fp;

        if (fopen_s(&fp, "Data/Save/SaveData.csv", "rt") != 0)
        {
            // �t�@�C�������݂��Ȃ�������
            // �V����csv�t�@�C�����쐬
            // �f�t�H���g�̒l���L�^
            GameData::Input data{};
            data.Bgm_ = 255;
            data.SE_ = 255;
            Save(data);
            // �V����������t�@�C�����J��
            // �J���Ȃ��ꍇ�̓��^�[��
            fp;
            if (fopen_s(&fp, "Data/Save/SaveData.csv", "rt"))return;
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
            if (chr == ',' ||
                chr == '\n' ||
                chr == EOF)
            {
                // dataTbl�Ƀf�[�^������
                m_loadData.push_back(tempNum);
                dataNum++;
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
    }

    void Save(GameData::Input data)
    {
        //FILE�|�C���^�̐錾
        FILE* fp1;
        // CSV�t�@�C�����J��
        fopen_s(&fp1, "Data/Save/SaveData.csv", "w");
        // CSV�t�@�C���ɏ㏑���ۑ�
        fprintf(
            fp1,
            "%ld,%ld\n",
            data.Bgm_,
            data.SE_);
        // CSV�t�@�C�������
        fclose(fp1);

        // �f�[�^��ۊ�
        m_loadData[0] = data.Bgm_;
        m_loadData[1] = data.SE_;
    }

    // 0����255
    GameData::Sound GetSoundData()
    {
        m_saveData.Bgm = m_loadData[0];
        m_saveData.SE  = m_loadData[1];

        return m_saveData;
    }

    // 0����1000
    GameData::Sound GetSoundBarData()
    {   
        // 0����255��0����1000�̊����ɕϊ�
        m_soundBarData.Bgm = (m_loadData[0] - 0) * (1000 - 0) / (255 - 0);
        m_soundBarData.SE = (m_loadData[1] - 0) * (1000 - 0) / (255 - 0);

        return m_soundBarData;
    }
}
