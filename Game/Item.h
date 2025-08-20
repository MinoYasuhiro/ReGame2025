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
	
	//座標、回転。
	Vector3 m_position;				//現在の座標。
	Quaternion m_rotation;			//回転情報。
	
	//別クラス。
	Player* m_player;				//プレイヤー

	//描画。
	ModelRender m_modelRender;		//アイテムの表示

	SoundSource* m_itemSE;
};

