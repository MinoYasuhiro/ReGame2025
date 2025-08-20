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
	//�v���C���[�̍폜�B
	DeleteGO(m_player);
	//�X�e�[�W�̍폜�B
	DeleteGO(m_backGround);
	//�Q�[���J�����̍폜�B
	DeleteGO(m_gameCamera);
	//�X�J�C�L���[�u�̍폜�B
	DeleteGO(m_skyCube);
	//�A�C�e���̍폜�B
	for (auto item : m_items) {
		DeleteGO(item);
	}
	//BGM�̍폜�B
	DeleteGO(m_gameBGM);
}
bool Game::Start()
{
	//�v���C���[�̃I�u�W�F�N�g�����B
	m_player = NewGO<Player>(0, "BattleCharacter");
	
	//�w�i�̃I�u�W�F�N�g�����B
	m_backGround = NewGO<BackGround>(0, "backGround");

	//�J�����̃I�u�W�F�N�g�����B
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	//��̃I�u�W�F�N�g���쐬����B�B
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f); //1.0�̂Ƃ��낪�I�u�W�F�N�g�ɗ^������̋����B
	g_renderingEngine->SetCascadeNearAreaRates(0.01f, 0.1f, 0.5f);
	
	//�Q�[����BGM���Đ��B
	SoundManager* sound = FindGO<SoundManager>("soundManager");
	m_gameBGM = sound->PlayingSound(Sound::enSound_InGameBGM);

	//�A�C�e���̐����B
	std::vector<Vector3> itemPositions = {	//std::vector��Vector3�^�̗v�f���i�[�ł���z��ł���B
		{ 0.0f,  25.0f, 1100.0f },//0		//itemposition�͕ϐ����B
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

		//�A�C�e���J�E���g���T�ɂȂ�����Q�[���N���A��ʂ�\������B
	if (m_player->m_itemCount == 5)
	{
		GameOverTime += 1.0f;

		if (GameOverTime == 60)
		{
			NewGO<GameClear>(0, "gameclear");

			DeleteGO(this);
		}
	}

	//�v���C���[��y���W��-1100�ɂȂ�����B�Q�[���I�[�o�[��ʂ�\������B
	if (m_player->m_position.y <= -1200)
	{
		NewGO<GameOver>(0, "gameover");

		DeleteGO(this);
	}


	////B�{�^�������͂��ꂽ��Q�[���N���A��ʂ𐶐�����B
	//if (g_pad[0]->IsTrigger(enButtonB))
	//{
	//	NewGO<GameClear>(0, "gameclear");

	//	DeleteGO(this);
	//}
	
}

void Game::PauseScreen()
{
	//Y�{�^�������͂��ꂽ��|�[�Y��ʂ𐶐�����B
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
	////�v���C���[�̍��W��\������B
	////�\��������W��ݒ肷��B
	//m_fontRender.SetPosition({ -600.0f,100.0f,0.0f });
	////�\������F��ݒ肷��B
	//m_fontRender.SetColor(g_vec4White);
	////�v���C���[�̍��W���擾
	//Vector3 pos = m_player->GetPosition();
	////���W�𕶎���ɕϊ�
	//wchar_t buf[128];
	//swprintf(buf, 128, L"Player Pos: X=%.1f Y=%.1f Z=%.1f", pos.x, pos.y, pos.z);
	////�e�L�X�g���Z�b�g
	//m_fontRender.SetText(buf);
	////�t�H���g��`��
	//m_fontRender.Draw(rc);
}
