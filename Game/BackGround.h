#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

	void Render(RenderContext& rc);

	ModelRender m_modelRender;
	//“–‚½‚è”»’èB
	PhysicsStaticObject m_physicsStaticObject;

};

