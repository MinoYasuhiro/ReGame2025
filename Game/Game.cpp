#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Item.h"
#include "Map.h"
#include "GameClear.h"
#include "GameOver.h"
#include "SoundManager.h"
#include "Pause.h"

Game::Game()
{

}

Game::~Game()
{
	//プレイヤーの削除。
	DeleteGO(m_player);
	//ステージの削除。
	DeleteGO(m_backGround);
	//ゲームカメラの削除。
	DeleteGO(m_gameCamera);
	//スカイキューブの削除。
	DeleteGO(m_skyCube);
	//アイテムの削除。
	for (auto item : m_items) {
		DeleteGO(item);
	}
	//BGMの削除。
	DeleteGO(m_gameBGM);
}
bool Game::Start()
{
	//プレイヤーのオブジェクトを作る。
	m_player = NewGO<Player>(0, "BattleCharacter");
	
	//背景のオブジェクトを作る。
	m_backGround = NewGO<BackGround>(0, "backGround");

	//カメラのオブジェクトを作る。
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	//空のオブジェクトを作成する。。
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f); //1.0のところがオブジェクトに与える光の強さ。
	g_renderingEngine->SetCascadeNearAreaRates(0.01f, 0.1f, 0.5f);
	
	//ゲームのBGMを再生。
	SoundManager* sound = FindGO<SoundManager>("soundManager");
	m_gameBGM = sound->PlayingSound(Sound::enSound_InGameBGM);

	//アイテムの生成。
	std::vector<Vector3> itemPositions = {	//std::vectorはVector3型の要素を格納できる配列である。
		{ 0.0f,  25.0f, 1100.0f },//0		//itempositionは変数名。
		{ 0.0f, 420.0f, 2460.0f },//1
		{ 0.0f, 740.0f, 3950.0f },//2
		{ 0.0f,-870.0f, 4100.0f },//3
		{ 0.0f,-380.0f, 6550.0f } //4
	};
	for (int i = 0; i < 5; i++)
	{
		m_items[i] = NewGO<Item>(0, "item");
		m_items[i]->m_position = itemPositions[i];
	}

	return true;
}

void Game::Update()
{	
	PauseScreen();

		//アイテムカウントが５になったらゲームクリア画面を表示する。
	if (m_player->m_itemCount == 5)
	{
		GameOverTime += 1.0f;

		if (GameOverTime == 60)
		{
			NewGO<GameClear>(0, "gameclear");

			DeleteGO(this);
		}
	}

	//プレイヤーのy座標が-1100になったら。ゲームオーバー画面を表示する。
	if (m_player->m_position.y <= -1200)
	{
		NewGO<GameOver>(0, "gameover");

		DeleteGO(this);
	}


	////Bボタンが入力されたらゲームクリア画面を生成する。
	//if (g_pad[0]->IsTrigger(enButtonB))
	//{
	//	NewGO<GameClear>(0, "gameclear");

	//	DeleteGO(this);
	//}
	
}

void Game::PauseScreen()
{
	//Yボタンが入力されたらポーズ画面を生成する。
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		if (m_pause == nullptr)
		{
			m_pause = NewGO<Pause>(0, "pause");
		}
	}
}


void Game::Render(RenderContext& rc)
{
	////プレイヤーの座標を表示する。
	////表示する座標を設定する。
	//m_fontRender.SetPosition({ -600.0f,100.0f,0.0f });
	////表示する色を設定する。
	//m_fontRender.SetColor(g_vec4White);
	////プレイヤーの座標を取得
	//Vector3 pos = m_player->GetPosition();
	////座標を文字列に変換
	//wchar_t buf[128];
	//swprintf(buf, 128, L"Player Pos: X=%.1f Y=%.1f Z=%.1f", pos.x, pos.y, pos.z);
	////テキストをセット
	//m_fontRender.SetText(buf);
	////フォントを描画
	//m_fontRender.Draw(rc);
}
