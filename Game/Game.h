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
	void PauseScreen();								//�|�[�Y���

	Pause* m_pause = nullptr;					//�|�[�Y���
	bool m_isPause = false;						//�|�[�Y���

private:
	//�Q�[�����I�u�W�F�N�g�B
	Player* m_player = nullptr;					//�v���C���[
	BackGround* m_backGround = nullptr;			//�w�i�B
	GameCamera* m_gameCamera = nullptr;			//�Q�[���J�����B
	Map* m_map = nullptr;						//�}�b�v
	SkyCube* m_skyCube = nullptr;				//��B
	SoundSource* m_gameBGM = nullptr;			//�Q�[���a�f�l�B

	//�A�C�e���֘A
	Item* m_item = nullptr;						//�A�C�e��
	Item* m_items[5];							//�A�C�e���̔z��

	//�Q�[����ԊǗ��B
	float GameOverTime;							//�Q�[���I�[�o�[��ʂ�\������܂ł̎��ԁB
	
	//�`��֘A�B
	FontRender m_fontRender;					//���W��\������
	
};


