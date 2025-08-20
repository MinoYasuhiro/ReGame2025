#pragma once
class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	//描画
	SpriteRender m_spriteRender;		//ゲームクリア画面を表示する。
	SoundSource* m_gameClearBGM;
};

