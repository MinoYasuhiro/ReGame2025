#pragma once
class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start() override;
	void Update() override;

	//�����o�ϐ��B
	Player* m_player;	//�v���C���[
	Vector3 m_toCameraPos;	//�����_
	SoundSource* m_gameClearBGM;
};

