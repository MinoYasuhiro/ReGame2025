#pragma once
class Map:public IGameObject
{
public:
	Map();
	~Map();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	//�`��B
	SpriteRender m_spriteRender;	//�}�b�v�̕\���B

	//�ʒu
	Vector3 m_position;				//���݂̍��W�B
};	

