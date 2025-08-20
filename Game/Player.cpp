#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	
}

Player::~Player()
{

}

bool Player::Start()
{
	//アニメーションクリップをロードする。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);


	//モデルを初期化する。
	m_modelRender.Init("Assets/modelData/unityChan.tkm",m_animationClips,enAnimationClip_Num,enModelUpAxisY);

	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, m_position);

	return true;
}

void Player::Update()
{
	


	//移動処理。
	Move();

	//回転処理。
	Rotation();

	//ステート管理。
	ManageState();

	//アニメーションの再生。
	PlayAnimation();
	
	//モデルを更新する。
	m_modelRender.Update();
}

void Player::Move()
{
	//xzの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	
	//y軸方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;
	
	float speed = 1.0f;

	//走り
	//padのセレクトまたはキーボードのスペースキーが押されたら。
	if (g_pad[0]->IsPress(enButtonSelect))
	{
		//移動速度が3倍になる。
		speed = 3.0f;
	}


	//左スティックの入力量に500.0fを乗算。
	right *= stickL.x * 500.0f* speed;
	forward *= stickL.y * 500.0f* speed;

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;

	//地面についていたら。
	if (m_characterController.IsOnGround())
	{
		//重力をなくす。
		m_moveSpeed.y = 0.0f;

		jumpState = 0;

		//Aボタンが押されたら。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ジャンプする・(7000f)
			m_moveSpeed.y = 700.0f;

			jumpState = 1;
		}

	}
	//地面についていなかったら。
	else
	{
		//重力を発生させる。(25.0f)
		m_moveSpeed.y -= 25.0f;
		//二段ジャンプ。
		if (jumpState == 1 && g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y = 700.0f;
			jumpState = 2;
		}
	}

	//m_positionに代入しても、下のcharacterControllerで上書きされてしまうから
	//characterControllerのpositionに代入する。

	/*if (g_pad[0]->IsTrigger(enButtonB))
	{
		Vector3 resetPos = { 0.0f, 25.0f, 0.0f };
		m_characterController.SetPosition(resetPos);
		m_position = resetPos;
	}*/

	/*if (g_pad[0]->IsTrigger(enButtonY))
	{
		Vector3 resetPos1 = { 0.0f, -820.0f,4090.0f };
		m_characterController.SetPosition(resetPos1);
		m_position = resetPos1;
	}*/

	//キャラクターコントローラーを使って座標を移動させる。
	m_position = m_characterController.Execute(m_moveSpeed,1.0f / 60.0f);

	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	//xかzの移動速度があったら（スティックの入力があったら。）
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える。
		m_modelRender.SetRotation(m_rotation);
	}
}

void Player::ManageState()
{
	//地面についていなかったら。
	if (m_characterController.IsOnGround() == false)
	{
		//ステートを１にする。(1=ジャンプ中)。
		m_playerState = 1;
		//ここでManageStateの処理を終わらせる。
		return;
	}
	
	

	//地面についていて、ｘかｚの移動速度があったら（スティックの入力があったら）
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//padのセレクト、キーボードのスペースキーが押されたら。
		if (g_pad[0]->IsPress(enButtonSelect))
		{
			//ステートを３にする。(3=走り)
			m_playerState = 3;
		}
		else
		{
			//ステートを２にする。(2=歩き)
			m_playerState = 2;
		}
	}
	//ｘとｚの移動速度がなかったら。(スティックの入力がなかったら。)
	else
	{
		//ステートを0にする。(0=待機).
		m_playerState = 0;
	}
	
}

void Player::PlayAnimation()
{
	switch (m_playerState)
	{
		//ステートが０だったら。
	case 0:	//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//ステートが１だったら。
	case 1: //ジャンプアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
		//ステートが２だったら。
	case 2:	//歩きアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
		//ステートが３だったら。
	case 3:	//走りアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

void Player::Render(RenderContext& renderContext)
{
	//モデルを表示する。
	m_modelRender.Draw(renderContext);
}