#include <DxLib.h>
#include <EffekseerForDXLib.h>

#include "Scene/SceneManager.h"
#include "Util/game.h"
#include "Util/SoundFunctions.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// ウィンドのサイズを変更できるかどうか
	SetWindowSizeChangeEnableFlag(Game::kWindowSizeChange);
	// Log.txtでログを残すかどうか
	SetOutApplicationLogValidFlag(Game::kLogText);

	// ＤＸライブラリ初期化処理
	// エラーが起きたら直ちに終了
	if (DxLib_Init() == -1)		
	{
		return -1;			
	}

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// DirectX9を使用するようにする。(DirectX11も可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
//	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	// フォントのロード
	LPCSTR fontPath = "Data/Fonts/Senobi-Gothic-Bold.ttf"; // 読み込むフォントファイルのパス
	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) 
	{
		ChangeFont("せのびゴシック Bold", DX_CHARSET_DEFAULT);
	}
	else 
	{
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	// サウンド読み込み
	SoundFunctions::Load();

	SceneManager* pScene = new SceneManager;

	pScene->Init();


	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		pScene->Update();

		pScene->Draw();
#if _DEBUG
		DrawFormatString(0, 0, 0xffffff,  "FPS       = %2f",DxLib::GetFPS());
		DrawFormatString(0, 10, 0xffffff, "DrawColl  = %d"  ,DxLib::GetDrawCallCount());
#endif
		// 裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	// フォントのアンロード
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) 
	{
	}
	else
	{
		MessageBox(NULL, "remove failure", "", MB_OK);
	}

	pScene->End();

	// サウンドメモリ解放
	SoundFunctions::UnLoad();

	// Effekseerを終了する。
	Effkseer_End();

	// ＤＸライブラリ使用の終了処理
	DxLib_End();				

	// ソフトの終了
	return 0;				 
}