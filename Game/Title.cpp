#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "SoundManager.h"


Title::Title()
{

}

Title::~Title()
{
	DeleteGO(m_titleBGM);
	
}

bool Title::Start()
{
	m_spriteRender.Init("Assets/modelData/Title.DDS", 1920.0f, 1080.0f);

	//PlayingSound()を使用するため、SoundManagerのインスタンスを取得。
	SoundManager* sound = FindGO<SoundManager>("soundManager");
	//BGMの再生。
	m_titleBGM = sound->PlayingSound(Sound::enSound_TitleBGM);


	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");

		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
