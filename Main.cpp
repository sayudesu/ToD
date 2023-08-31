#include <DxLib.h>
#include <EffekseerForDXLib.h>

#include "Scene/SceneManager.h"
#include "Util/game.h"
#include "Util/SoundFunctions.h"

#include "SaveDataFunctions.h"
#include "Util/LoadGraphfunction.h"

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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

	// 使用する Direct3D のバージョンを 9EX に設定
	   SetUseDirect3DVersion(DX_DIRECT3D_9EX);

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
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
//	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// 3D関連の設定
	// Zバッファを有効にする。
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(true);

	// ポリゴンの裏面を描画しない
	SetUseBackCulling(true);

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

	// ファイルの読み込み
	SaveDataFunctions::Load();
	// サウンド読み込み
	SoundFunctions::Load(SaveDataFunctions::GetSoundData());
	// 画像データの読み込み
	LoadGraphFunction::Load();

	SceneManager* pScene = new SceneManager;
		
	pScene->Init();

	//int m_handle;
	//int m_shader;
	//int m_handleSizeX;
	//int m_handleSizeY;
	//int m_hScreen;
	VERTEX2DSHADER Vert[6];

	//// 画像の読み込み
	//m_handle = LoadGraph("end.png");
	//GetGraphSize(m_handle, &m_handleSizeX, &m_handleSizeY);
	//assert(m_handle != -1);

	//// ピクセルシェーダーバイナリコードの読み込み
	//m_shader = LoadPixelShader("Shader/SamplePS.pso");
	//assert(m_shader != -1);

	// 頂点データの準備
	Vert[0].pos = VGet(0.0f, 0.0f, 0.0f);
	Vert[1].pos = VGet(Game::kScreenWidth - 1, 0.0f, 0.0f);
	Vert[2].pos = VGet(0.0f, Game::kScreenHeight - 1, 0.0f);
	Vert[3].pos = VGet(Game::kScreenWidth - 1, Game::kScreenHeight - 1, 0.0f);
	Vert[0].dif = GetColorU8(255, 255, 255, 255);
	Vert[0].spc = GetColorU8(0, 0, 0, 0);
	Vert[0].u = 0.0f; Vert[0].v = 0.0f;
	Vert[1].u = 1.0f; Vert[1].v = 0.0f;
	Vert[2].u = 0.0f; Vert[2].v = 1.0f;
	Vert[3].u = 1.0f; Vert[3].v = 1.0f;
	Vert[0].su = 0.0f; Vert[0].sv = 0.0f;
	Vert[1].su = 1.0f; Vert[1].sv = 0.0f;
	Vert[2].su = 0.0f; Vert[2].sv = 1.0f;
	Vert[3].su = 1.0f; Vert[3].sv = 1.0f;
	Vert[0].rhw = 1.0f;
	Vert[1].rhw = 1.0f;
	Vert[2].rhw = 1.0f;
	Vert[3].rhw = 1.0f;
	Vert[4] = Vert[2];
	Vert[5] = Vert[1];

	//m_hScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);
	//// 使用するテクスチャをセット
	//SetUseTextureToShader(0, m_hScreen);
	//// 使用するピクセルシェーダーをセット
	//SetUsePixelShader(m_shader);

	int m_handle;
	int m_shader;
	//int m_handleSizeX;
	//int m_handleSizeY;
	int m_hScreen;
	//VERTEX2DSHADER Vert[6]{};

	//// 画像の読み込み
	//m_handle = LoadGraph("end.png");
	//assert(m_handle != -1);
	//GetGraphSize(m_handle, &m_handleSizeX, &m_handleSizeY);

	//// ピクセルシェーダーバイナリコードの読み込み
	m_shader = LoadPixelShader("Shader/SamplePS.pso");
	assert(m_shader != -1);

	//// 頂点データの準備
	//Vert[0].pos = VGet(0.0f, 0.0f, 0.0f);
	//Vert[1].pos = VGet(Game::kScreenWidth - 1, 0.0f, 0.0f);
	//Vert[2].pos = VGet(0.0f, Game::kScreenHeight - 1, 0.0f);
	//Vert[3].pos = VGet(Game::kScreenWidth - 1, Game::kScreenHeight - 1, 0.0f);
	//Vert[0].dif = GetColorU8(255, 255, 255, 255);
	//Vert[0].spc = GetColorU8(0, 0, 0, 0);
	//Vert[0].u = 0.0f; Vert[0].v = 0.0f;
	//Vert[1].u = 1.0f; Vert[1].v = 0.0f;
	//Vert[2].u = 0.0f; Vert[2].v = 1.0f;
	//Vert[3].u = 1.0f; Vert[3].v = 1.0f;
	//Vert[0].su = 0.0f; Vert[0].sv = 0.0f;
	//Vert[1].su = 1.0f; Vert[1].sv = 0.0f;
	//Vert[2].su = 0.0f; Vert[2].sv = 1.0f;
	//Vert[3].su = 1.0f; Vert[3].sv = 1.0f;
	//Vert[0].rhw = 1.0f;
	//Vert[1].rhw = 1.0f;
	//Vert[2].rhw = 1.0f;
	//Vert[3].rhw = 1.0f;
	//Vert[4] = Vert[2];
	//Vert[5] = Vert[1];

	m_hScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);
	//// 使用するテクスチャをセット
	//SetUseTextureToShader(0, m_hScreen);
	//// 使用するピクセルシェーダーをセット
	//SetUsePixelShader(m_shader);

	//std::array< VERTEX2DSHADER, 4 > vertex;
	//std::array< unsigned short, 6 > vertexIndex;

	//auto Settings = [](VERTEX2DSHADER& vtx, float x, float y, float u, float v)
	//{
	//	vtx.pos = VGet(x, y, 0.0f);
	//	vtx.u = u;
	//	vtx.v = v;
	//	vtx.su = u;
	//	vtx.sv = v;
	//	vtx.rhw = 1.0f;
	//	vtx.dif = GetColorU8(255, 255, 255, 255);
	//	vtx.spc = GetColorU8(0, 0, 0, 0);
	//};

	//Settings(vertex[0], 0.0f, 0.0f, 0.0f, 0.0f);
	//Settings(vertex[1], Game::kScreenWidth, 0.0f, 0.0f, 0.0f);
	//Settings(vertex[2], 0.0f, Game::kScreenHeight, 0.0f, 1.0f);
	//Settings(vertex[3], Game::kScreenWidth, Game::kScreenHeight, 0.0f, 1.0f);

	//vertexIndex = { 0, 1, 2, 2, 1, 3 };

	SetUseTextureToShader(0, m_hScreen);

	SetUsePixelShader(m_shader);

	float level = 30.0f;
	SetPSConstSF(GetConstIndexToShader("alpha", m_shader), 1.0f);
	SetPSConstSF(GetConstIndexToShader("mosLv", m_shader), level);
	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		pScene->Update();
		//SetDrawScreen(m_hScreen);
		pScene->Draw();
		if (DxLib::CheckHitKey(KEY_INPUT_1))
		{
			level -= 0.3f;
		}
		if (DxLib::CheckHitKey(KEY_INPUT_2))
		{
			level += 0.3f;
		}
		SetPSConstSF(GetConstIndexToShader("mosLv", m_shader), level);

#if FALSE
		SetDrawScreen(DX_SCREEN_BACK);
		DrawPrimitive2DToShader(Vert, 6, DX_PRIMTYPE_TRIANGLELIST);
		SetDrawScreen(m_hScreen);
#endif

		//ClearDrawScreen();

		//SetDrawScreen(DX_SCREEN_BACK);
		//SetTextureAddressMode(DX_TEXADDRESS_CLAMP);
	//	DrawPolygonIndexed2DToShader(vertex.data(), 4, vertexIndex.data(), 2);
		//// 描画
		//if (true)
		//{
		//	DrawGraph(0, 0, m_hScreen, false);

		//}
		//else
		//{
		//	DrawPrimitive2DToShader(Vert, 6, DX_PRIMTYPE_TRIANGLELIST);
		//}


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

	// 画像データのメモリ解放
	LoadGraphFunction::UnLoad();

	// Effekseerを終了する。
	Effkseer_End();

	// ＤＸライブラリ使用の終了処理
	DxLib_End();				

	// ソフトの終了
	return 0;				 
}