#include "SaveDataFunctions.h"
#include <DxLib.h>
#include <cassert>

#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <cctype>

namespace
{
    // �f�[�^�ۑ��p�p�X
    const char* kDataPath = "Data/Save/SaveData.csv";
    // �O���t�@�C���ǂݍ��ݗp
    std::vector<int> m_loadData;
    // 
    GameData::Sound m_saveData;
    GameData::Sound m_soundBarData;
    GameData::Icon m_iconData;
    // �f�[�^���J�E���g
    int dataNum = -1;

    constexpr int kDataMaxNum = 2;
    constexpr int kDataIcon = 0;
    constexpr int kDataBGM  = 1;
    constexpr int kDataSE   = 2;
}

namespace SaveDataFunctions
{
    void Load()
    {
        // csv�t�@�C����ǂݍ���Ő����̔z��ɂ�����
        FILE* fp;
        // �t�@�C�������邩�ǂ���
        bool isFileCheck = true;

        if (fopen_s(&fp,kDataPath, "rt") != 0)
        {
            isFileCheck = false;
            // �t�@�C�������݂��Ȃ�������
            // �V����csv�t�@�C�����쐬
            // �f�t�H���g�̒l���L�^
            GameData::Input data{};
            data.Icon_ = 0;
            data.Bgm_ = 255;
            data.SE_ = 255;
            Save(data,false);

            // �V����������t�@�C�����J��
            // �J���Ȃ��ꍇ�̓��^�[��
            fp;
            if (fopen_s(&fp,kDataPath, "rt"))return;
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

        if (!isFileCheck)
        {
            // �t�@�C�������݂��Ȃ�������
            // �V����csv�t�@�C�����쐬
            // �f�t�H���g�̒l���L�^
            GameData::Input data{};
            data.Icon_ = 255;
            data.Bgm_ = 255;
            data.SE_ = 255;
            Save(data, true);
        }
    }

    void Save(GameData::Input data,bool now)
    {
        //FILE�|�C���^�̐錾
        FILE* fp1;
        // CSV�t�@�C�����J��
        fopen_s(&fp1, kDataPath, "w");
        // CSV�t�@�C���ɏ㏑���ۑ�
        fprintf(
            fp1,
            "%ld,%ld,%ld\n",
            data.Icon_,
            data.Bgm_,
            data.SE_);
        // CSV�t�@�C�������
        fclose(fp1);

        if (now)
        {
            // �f�[�^��ۊ�
            m_loadData[kDataIcon] = data.Icon_;
            m_loadData[kDataBGM] = data.Bgm_;
            m_loadData[kDataSE] = data.SE_;
        }
    }

    // 0����255
    GameData::Sound GetSoundData()
    {
        m_saveData.Bgm = m_loadData[kDataBGM];
        m_saveData.SE  = m_loadData[kDataSE];

        return m_saveData;
    }

    // 0����1000
    GameData::Sound GetSoundBarData()
    {   
        // 0����255��0����1000�̊����ɕϊ�
        m_soundBarData.Bgm = (m_loadData[kDataBGM] - 0) * (1000 - 0) / (255 - 0);
        m_soundBarData.SE = (m_loadData[kDataSE] - 0) * (1000 - 0) / (255 - 0);

        return m_soundBarData;
    }
    // �A�C�R���̃f�[�^��n��
    GameData::Icon GetIconData()
    {
        m_iconData.Icon = m_loadData[kDataIcon];

        return m_iconData;
    }
}
