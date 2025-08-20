#pragma once
class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	//�`��
	SpriteRender m_spriteRender;		//�Q�[���N���A��ʂ�\������B
	SoundSource* m_gameClearBGM;
};

