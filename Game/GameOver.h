#pragma once
class GameOver: public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);

	//�`��B
	SpriteRender m_spriteRender;	//�Q�[���I�[�o�[��ʂ�\������B
	SoundSource* m_gameOverBGM;
};

