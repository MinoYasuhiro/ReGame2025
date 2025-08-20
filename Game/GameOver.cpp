#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "SoundManager.h"

GameOver::GameOver()
{

}

GameOver::~GameOver()
{
	DeleteGO(m_gameOverBGM);
}

bool GameOver::Start()
{
	m_spriteRender.Init("Assets/modelData/GameOver.DDS", 1920.0f, 1080.0f);

	SoundManager* sound = FindGO<SoundManager>("soundManager");
	m_gameOverBGM = sound->PlayingSound(Sound::enSound_GameOverBGM);

	return true;
}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0, "title");

		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext & rc)
{
	m_spriteRender.Draw(rc);
}
