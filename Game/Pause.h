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

	SpriteRender m_spriteRender;			//�|�[�Y��ʂ̕\��
	SpriteRender m_arrow;					//�|�[�Y��ʂ̖��\���B
	SpriteRender m_retry;					//�|�[�Y��ʂ̃��g���C�B
	SpriteRender m_pauseTitle;				//�|�[�Y��ʂ̃^�C�g���B

	Vector3 m_arrowPosition;				//���̍��W�B
	Vector3 m_retryPosition;				//���g���C�̍��W�B
	Vector3 m_titlePosition;				//�^�C�g���̍��W�B

	int arrowState = 0; 					//�X�e�[�g�Ǘ��B

	Player* m_player = nullptr;				//�v���C���[�B
	Title* m_title = nullptr;				//�^�C�g���B
	Game* m_game = nullptr;
};

