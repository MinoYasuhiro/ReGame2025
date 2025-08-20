#pragma once
class Player;
class Title;
class Game;
class Pause : public IGameObject
{
public:
	Pause();
	~Pause();
	bool Start() override;
	void Update() override;
	void Render(RenderContext & rc);

	SpriteRender m_spriteRender;			//ポーズ画面の表示
	SpriteRender m_arrow;					//ポーズ画面の矢印表示。
	SpriteRender m_retry;					//ポーズ画面のリトライ。
	SpriteRender m_pauseTitle;				//ポーズ画面のタイトル。

	Vector3 m_arrowPosition;				//矢印の座標。
	Vector3 m_retryPosition;				//リトライの座標。
	Vector3 m_titlePosition;				//タイトルの座標。

	int arrowState = 0; 					//ステート管理。

	Player* m_player = nullptr;				//プレイヤー。
	Title* m_title = nullptr;				//タイトル。
	Game* m_game = nullptr;
};

