#include "UserSaveData.h"
#include <DxLib.h>
#include <cassert>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace
{
    // 外部ファイル読み込み用
    std::vector<int> m_loadData;
    // 
    SaveData m_saveData;
    SaveData m_soundBarData;
}

namespace SaveDataFunctions
{
    void Load()
    {
        // csvファイルを読み込んで数字の配列にしたい
        FILE* fp;

        if (fopen_s(&fp, "Data/Save/SaveData.csv", "rt") != 0)
        {
            // ファイルが存在しなかったら
            // 新しいcsvファイルを作成
            // デフォルトの値を記録
            SaveData data;
            data.Bgm = 255;
            data.SE = 255;
            Save(data);
            // 新しく作ったファイルを開く
            fp;
            if (fopen_s(&fp, "Data/Save/SaveData.csv", "rt"))return;
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
            if (chr == ',' ||
                chr == '\n' ||
                chr == EOF)
            {
                // dataTblにデータを入れる
                m_loadData.push_back(tempNum);
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

        printfDx("閉じた後%d\n", m_loadData[0]);
    }

    void Save(SaveData data)
    {
        printfDx("bgm == %d\n", data.Bgm);
        //FILEポインタの宣言
        FILE* fp1;
        //Step1. CSVファイルを開く
        fopen_s(&fp1, "Data/Save/SaveData.csv", "w");
        //CSVファイルに上書き保存
        fprintf(
            fp1,
            "%ld,%ld\n",
            data.Bgm,
            data.SE);
        //Step3. CSVファイルを閉じる
        fclose(fp1);
    }

    // 0から255
    SaveData GetSoundData()
    {
        m_saveData.Bgm = m_loadData[0];
        m_saveData.SE  = m_loadData[1];

        return m_saveData;
    }

    // 0から1000
    SaveData GetSoundBarData()
    {   
        // 0から255を0から1000の割合に変換
        m_soundBarData.Bgm = (m_loadData[0] - 0) * (1000 - 0) / (255 - 0);
        m_soundBarData.SE = (m_loadData[1] - 0) * (1000 - 0) / (255 - 0);

        return m_soundBarData;
    }
}
