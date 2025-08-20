#include "stdafx.h"
#include "Pause.h"
#include "Player.h"
#include "Title.h"
#include "Game.h"

Pause::Pause()
{

}

Pause::~Pause()
{

}

bool Pause::Start()
{
	m_spriteRender.Init("Assets/modelData/PAUSE.DDS", 1200.0f, 800.0f);
	m_arrow.Init("Assets/modelData/arrow.DDS", 400.0f, 400.0f);
	m_retry.Init("Assets/modelData/retry.DDS", 350.0f, 200.0f);
	m_pauseTitle.Init("Assets/modelData/pausetitle.DDS", 350.0f, 200.0f);

	m_arrowPosition.x -= 350.0f;
	m_retryPosition.y -= 10.0f;
	m_titlePosition.y -= 250.0f;

	m_arrow.SetPosition(m_arrowPosition);
	m_retry.SetPosition(m_retryPosition);
	m_pauseTitle.SetPosition(m_titlePosition);

	m_player = FindGO<Player>("BattleCharacter");
	m_game = FindGO<Game>("game");

	return true;
}

void Pause::Update()
{
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		m_arrowPosition.y = 0.0f;
		arrowState = 0;
		m_arrow.SetPosition(m_arrowPosition);
	}

	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		m_arrowPosition.y = -250.0f;
		arrowState = 1;
		m_arrow.SetPosition(m_arrowPosition);
	}

	//色の変化。
	switch (arrowState)
	{
	case 0:
		m_retry.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });	//赤くする。
		m_pauseTitle.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });	//白くする。
		break;
	case 1:
		m_pauseTitle.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });	//赤くする。
		m_retry.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });		//白くする。
		break;
	}

	if (arrowState == 0 and g_pad[0]->IsTrigger(enButtonY))
	{
	    Vector3 retrypos = { 0.0f,24.0f,0.0f };
		m_player->m_characterController.SetPosition(retrypos);
		m_game->m_pause = nullptr;
		DeleteGO(this);
	}
	
	if (arrowState == 1 and g_pad[0]->IsTrigger(enButtonY))
	{
		m_title = NewGO<Title>(0, "title");
		m_game->m_pause = nullptr;
		DeleteGO(this);
		DeleteGO(m_game);
	}

	if (g_pad[0]->IsTrigger(enButtonX))
	{
		m_game->m_pause = nullptr;
		DeleteGO(this);
	}

	m_arrow.Update();
	m_retry.Update();
	m_pauseTitle.Update();
}

void Pause::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_arrow.Draw(rc);
	m_retry.Draw(rc);
	m_pauseTitle.Draw(rc);
}
