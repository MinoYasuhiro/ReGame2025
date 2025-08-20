#pragma once
class Title:public IGameObject
{
public:
	Title();
	~Title();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
	SoundSource* m_titleBGM = nullptr;
};

