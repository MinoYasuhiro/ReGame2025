#pragma once
class Player;
class Item : public IGameObject
{
public:
	Item();
	~Item();
	bool Start();
	void Update();
	void Rotation();
	void Render(RenderContext& rc);
	
	//���W�A��]�B
	Vector3 m_position;				//���݂̍��W�B
	Quaternion m_rotation;			//��]���B
	
	//�ʃN���X�B
	Player* m_player;				//�v���C���[

	//�`��B
	ModelRender m_modelRender;		//�A�C�e���̕\��

	SoundSource* m_itemSE;
};

