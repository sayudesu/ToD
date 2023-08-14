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
    // データ保存用パス
    const char* kDataPath = "Data/Save/SaveData.csv";
    // 外部ファイル読み込み用
    std::vector<int> m_loadData;
    // 
    GameData::Sound m_saveData;
    GameData::Sound m_soundBarData;
    GameData::Icon m_iconData;
    // データ数カウント
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
        // csvファイルを読み込んで数字の配列にしたい
        FILE* fp;
        // ファイルがあるかどうか
        bool isFileCheck = true;

        if (fopen_s(&fp,kDataPath, "rt") != 0)
        {
            isFileCheck = false;
            // ファイルが存在しなかったら
            // 新しいcsvファイルを作成
            // デフォルトの値を記録
            GameData::Input data{};
            data.Icon_ = 0;
            data.Bgm_ = 255;
            data.SE_ = 255;
            Save(data,false);

            // 新しく作ったファイルを開く
            // 開けない場合はリターン
            fp;
            if (fopen_s(&fp,kDataPath, "rt"))return;
        }

        int chr;
        // 未確定
        int wNum = -1;
        // 横の要素数数える用
        int tempW = 0;

        int tempNum = 0;

        while (true)
        {
            chr = fgetc(fp);    // 1文字読み込み

            // 区切り文字が見つかった
            if (chr == ',' || chr == '\n' || chr == EOF)
            {

                // m_loadDataにデータを入れる
                m_loadData.push_back(tempNum);

                dataNum++;
                tempNum = 0;

                // ファイルの終端に来たら終了
                if (chr == EOF)
                {
                    break;
                }
                else if (chr == ',')
                {
                    tempW++;    // 要素数数える
                }
                else   // chr == '\n'
                {
                    tempW++;    // 要素数数える
                    if (wNum < 0)
                    {
                        wNum = tempW;    // 要素数確定
                    }
                    /*else
                    {
                        assert(wNum == tempW);
                    }*/
                    tempW = 0;
                }
                // まだ終わってないので続けて読み込み
                continue;
            }

            // データは数字のみのはず
           assert(chr >= '0' && chr <= '9');
        
            // 数字なのは確定
            // 文字列を数値に変換したい
            // 268を読み込む
            // 1文字目は'2'    これを数値に変換していれる
            // 2文字目は'6'    tempNumは2 20 + 6  tempNum = 26
            // 3文字目は'8' tempNumは26 260+ 8 tempNum = 268
            tempNum = (tempNum * 10) + chr - '0';

            // データの区切りが見つかった時点でそこまでがデータのひとまとまり

        }
        // ファイルを閉じる
        fclose(fp);

        if (!isFileCheck)
        {
            // ファイルが存在しなかったら
            // 新しいcsvファイルを作成
            // デフォルトの値を記録
            GameData::Input data{};
            data.Icon_ = 255;
            data.Bgm_ = 255;
            data.SE_ = 255;
            Save(data, true);
        }
    }

    void Save(GameData::Input data,bool now)
    {
        //FILEポインタの宣言
        FILE* fp1;
        // CSVファイルを開く
        fopen_s(&fp1, kDataPath, "w");
        // CSVファイルに上書き保存
        fprintf(
            fp1,
            "%ld,%ld,%ld\n",
            data.Icon_,
            data.Bgm_,
            data.SE_);
        // CSVファイルを閉じる
        fclose(fp1);

        if (now)
        {
            // データを保管
            m_loadData[kDataIcon] = data.Icon_;
            m_loadData[kDataBGM] = data.Bgm_;
            m_loadData[kDataSE] = data.SE_;
        }
    }

    // 0から255
    GameData::Sound GetSoundData()
    {
        m_saveData.Bgm = m_loadData[kDataBGM];
        m_saveData.SE  = m_loadData[kDataSE];

        return m_saveData;
    }

    // 0から1000
    GameData::Sound GetSoundBarData()
    {   
        // 0から255を0から1000の割合に変換
        m_soundBarData.Bgm = (m_loadData[kDataBGM] - 0) * (1000 - 0) / (255 - 0);
        m_soundBarData.SE = (m_loadData[kDataSE] - 0) * (1000 - 0) / (255 - 0);

        return m_soundBarData;
    }
    // アイコンのデータを渡す
    GameData::Icon GetIconData()
    {
        m_iconData.Icon = m_loadData[kDataIcon];

        return m_iconData;
    }
}
