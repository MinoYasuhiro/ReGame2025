#pragma once
class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start() override;
	void Update() override;

	//メンバ変数。
	Player* m_player;	//プレイヤー
	Vector3 m_toCameraPos;	//注視点
	SoundSource* m_gameClearBGM;
};

