#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

	void Render(RenderContext& rc);

	ModelRender m_modelRender;
	//�����蔻��B
	PhysicsStaticObject m_physicsStaticObject;

};

