#include "stdafx.h"
#include "Map.h"

Map::Map()
{

}

Map::~Map()
{

}

bool Map::Start()
{
	m_spriteRender.Init("Assets/modelData/ReGame map.DDS", 700.0f, 300.0f);
	//m_spriteRender.Init("Assets/modelData/ReGame map1.DDS", 700.0f, 300.0f);
	
	
	m_position.x = 620.0f;
	m_position.y = 390.0f;

	m_spriteRender.SetPosition(m_position);
	return true;
}

void Map::Update()
{
	m_spriteRender.Update();
}

void Map::Render(RenderContext & rc)
{
	m_spriteRender.Draw(rc);
}

