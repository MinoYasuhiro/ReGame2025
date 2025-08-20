#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class Item;
class Map;
class GameClear;
class GameOver;
class Pause;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);
	void PauseScreen();								//ポーズ画面

	Pause* m_pause = nullptr;					//ポーズ画面
	bool m_isPause = false;						//ポーズ状態

private:
	//ゲーム内オブジェクト。
	Player* m_player = nullptr;					//プレイヤー
	BackGround* m_backGround = nullptr;			//背景。
	GameCamera* m_gameCamera = nullptr;			//ゲームカメラ。
	Map* m_map = nullptr;						//マップ
	SkyCube* m_skyCube = nullptr;				//空。
	SoundSource* m_gameBGM = nullptr;			//ゲームＢＧＭ。

	//アイテム関連
	Item* m_item = nullptr;						//アイテム
	Item* m_items[5];							//アイテムの配列

	//ゲーム状態管理。
	float GameOverTime;							//ゲームオーバー画面を表示するまでの時間。
	
	//描画関連。
	FontRender m_fontRender;					//座標を表示する
	
};


