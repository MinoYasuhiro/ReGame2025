#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "SoundManager.h"

GameClear::GameClear()
{

}

GameClear::~GameClear()
{
	DeleteGO(m_gameClearBGM);
}

bool GameClear::Start()
{
	m_spriteRender.Init("Assets/modelData/GameClear.DDS",1920.0f,1080.0f);

	SoundManager* sound = FindGO<SoundManager>("soundManager");
	m_gameClearBGM = sound->PlayingSound(Sound::enSound_GameClearBGM);

	return true;
}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0, "title");

		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}