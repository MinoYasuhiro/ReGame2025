#pragma once
class Map:public IGameObject
{
public:
	Map();
	~Map();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	//描画。
	SpriteRender m_spriteRender;	//マップの表示。

	//位置
	Vector3 m_position;				//現在の座標。
};	

