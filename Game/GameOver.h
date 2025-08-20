#pragma once
class GameOver: public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);

	//描画。
	SpriteRender m_spriteRender;	//ゲームオーバー画面を表示する。
	SoundSource* m_gameOverBGM;
};

