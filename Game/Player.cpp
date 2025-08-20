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
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);


	//���f��������������B
	m_modelRender.Init("Assets/modelData/unityChan.tkm",m_animationClips,enAnimationClip_Num,enModelUpAxisY);

	//�L�����R��������������B
	m_characterController.Init(25.0f, 75.0f, m_position);

	return true;
}

void Player::Update()
{
	


	//�ړ������B
	Move();

	//��]�����B
	Rotation();

	//�X�e�[�g�Ǘ��B
	ManageState();

	//�A�j���[�V�����̍Đ��B
	PlayAnimation();
	
	//���f�����X�V����B
	m_modelRender.Update();
}

void Player::Move()
{
	//xz�̈ړ����x��0.0f�ɂ���B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	
	//y�������ɂ͈ړ������Ȃ��B
	forward.y = 0.0f;
	right.y = 0.0f;
	
	float speed = 1.0f;

	//����
	//pad�̃Z���N�g�܂��̓L�[�{�[�h�̃X�y�[�X�L�[�������ꂽ��B
	if (g_pad[0]->IsPress(enButtonSelect))
	{
		//�ړ����x��3�{�ɂȂ�B
		speed = 3.0f;
	}


	//���X�e�B�b�N�̓��͗ʂ�500.0f����Z�B
	right *= stickL.x * 500.0f* speed;
	forward *= stickL.y * 500.0f* speed;

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	m_moveSpeed += right + forward;

	//�n�ʂɂ��Ă�����B
	if (m_characterController.IsOnGround())
	{
		//�d�͂��Ȃ����B
		m_moveSpeed.y = 0.0f;

		jumpState = 0;

		//A�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//�W�����v����E(7000f)
			m_moveSpeed.y = 700.0f;

			jumpState = 1;
		}

	}
	//�n�ʂɂ��Ă��Ȃ�������B
	else
	{
		//�d�͂𔭐�������B(25.0f)
		m_moveSpeed.y -= 25.0f;
		//��i�W�����v�B
		if (jumpState == 1 && g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y = 700.0f;
			jumpState = 2;
		}
	}

	//m_position�ɑ�����Ă��A����characterController�ŏ㏑������Ă��܂�����
	//characterController��position�ɑ������B

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

	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	m_position = m_characterController.Execute(m_moveSpeed,1.0f / 60.0f);

	//�G�`������ɍ��W��������B
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	//x��z�̈ړ����x����������i�X�e�B�b�N�̓��͂���������B�j
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//�G�`������ɉ�]��������B
		m_modelRender.SetRotation(m_rotation);
	}
}

void Player::ManageState()
{
	//�n�ʂɂ��Ă��Ȃ�������B
	if (m_characterController.IsOnGround() == false)
	{
		//�X�e�[�g���P�ɂ���B(1=�W�����v��)�B
		m_playerState = 1;
		//������ManageState�̏������I��点��B
		return;
	}
	
	

	//�n�ʂɂ��Ă��āA�������̈ړ����x����������i�X�e�B�b�N�̓��͂���������j
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//pad�̃Z���N�g�A�L�[�{�[�h�̃X�y�[�X�L�[�������ꂽ��B
		if (g_pad[0]->IsPress(enButtonSelect))
		{
			//�X�e�[�g���R�ɂ���B(3=����)
			m_playerState = 3;
		}
		else
		{
			//�X�e�[�g���Q�ɂ���B(2=����)
			m_playerState = 2;
		}
	}
	//���Ƃ��̈ړ����x���Ȃ�������B(�X�e�B�b�N�̓��͂��Ȃ�������B)
	else
	{
		//�X�e�[�g��0�ɂ���B(0=�ҋ@).
		m_playerState = 0;
	}
	
}

void Player::PlayAnimation()
{
	switch (m_playerState)
	{
		//�X�e�[�g���O��������B
	case 0:	//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//�X�e�[�g���P��������B
	case 1: //�W�����v�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
		//�X�e�[�g���Q��������B
	case 2:	//�����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
		//�X�e�[�g���R��������B
	case 3:	//����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

void Player::Render(RenderContext& renderContext)
{
	//���f����\������B
	m_modelRender.Draw(renderContext);
}