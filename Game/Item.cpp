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

	//�A�C�e���擾���̉���ǂݍ��ށB
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

		//�A�C�e���J�E���g�𑝂₷�B
		m_player->m_itemCount += 1;


		//�A�C�e�����폜����B
		DeleteGO(this);
	}


	Rotation();
	
	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();
}
//��]�����B
void Item::Rotation()
{
	////��]�����Z����B
	m_rotation.AddRotationDegY(4.0f);

	//m_rotation.AddRotationDegX(-4.0f);
	
	


	//�G�`������ɉ�]��������B
	m_modelRender.SetRotation(m_rotation);
}

void Item::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}