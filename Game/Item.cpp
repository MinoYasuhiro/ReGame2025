#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SoundManager.h"

Item::Item()
{

}

Item::~Item()
{

}

bool Item::Start()
{
	//m_modelRender.Init("Assets/modelData/Item.tkm");
	m_modelRender.Init("Assets/modelData/Item1.tkm");

	m_player = FindGO<Player>("BattleCharacter");

	//アイテム取得時の音を読み込む。
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/star.wav");

	return true;
}

void Item::Update()
{
	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 100.0f)
	{
		SoundManager* se = FindGO<SoundManager>("soundManager");
		m_itemSE = se->PlayingSound(enSound_ItemSE,false);

		//アイテムカウントを増やす。
		m_player->m_itemCount += 1;


		//アイテムを削除する。
		DeleteGO(this);
	}


	Rotation();
	
	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();
}
//回転処理。
void Item::Rotation()
{
	////回転を加算する。
	m_rotation.AddRotationDegY(4.0f);

	//m_rotation.AddRotationDegX(-4.0f);
	
	


	//絵描きさんに回転を教える。
	m_modelRender.SetRotation(m_rotation);
}

void Item::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}