#pragma once
class Player :public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	//更新処理。
	void Update() override;
	//描画処理
	void Render(RenderContext& rc) override;
	//移動処理。
	void Move();
	//回転処理。
	void Rotation();
	//ステート管理。
	void ManageState();
	//アニメーションの再生。
	void PlayAnimation();
	////座標を取得する。
	Vector3 GetPosition() const
	{
		return m_position;
	}


	//ココからメンバ変数

	//描画。
	ModelRender m_modelRender;					//モデルの表示


	//位置、物理。
	Vector3 m_position;							//プレイヤーの座標
	CharacterController m_characterController;	//キャラクターコントローラー
	Vector3 m_moveSpeed;						//移動速度
	float speed = 0;							//移動速度の倍数
	Quaternion m_rotation;						//回転情報
	int jumpState = 0;							//ジャンプ状態


	//アニメーションの再生。
	enum EnAnimationClip {						//アニメーション。
		enAnimationClip_Idle,	//0				//立ち
		enAnimationClip_Jump,					//ジャンプ
		enAnimationClip_Walk,					//歩く
		enAnimationClip_Run,					//走る
		enAnimationClip_Num,	//4				//総数。
	};
	AnimationClip m_animationClips[enAnimationClip_Num];	//アニメーションクリップの総数の配列

	
	//状態管理
	int m_playerState = 0;						//ステート管理用の変数
	int m_itemCount = 0;						//アイテムのカウント
};

