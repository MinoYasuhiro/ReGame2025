#pragma once
class Player :public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	//�X�V�����B
	void Update() override;
	//�`�揈��
	void Render(RenderContext& rc) override;
	//�ړ������B
	void Move();
	//��]�����B
	void Rotation();
	//�X�e�[�g�Ǘ��B
	void ManageState();
	//�A�j���[�V�����̍Đ��B
	void PlayAnimation();
	////���W���擾����B
	Vector3 GetPosition() const
	{
		return m_position;
	}


	//�R�R���烁���o�ϐ�

	//�`��B
	ModelRender m_modelRender;					//���f���̕\��


	//�ʒu�A�����B
	Vector3 m_position;							//�v���C���[�̍��W
	CharacterController m_characterController;	//�L�����N�^�[�R���g���[���[
	Vector3 m_moveSpeed;						//�ړ����x
	float speed = 0;							//�ړ����x�̔{��
	Quaternion m_rotation;						//��]���
	int jumpState = 0;							//�W�����v���


	//�A�j���[�V�����̍Đ��B
	enum EnAnimationClip {						//�A�j���[�V�����B
		enAnimationClip_Idle,	//0				//����
		enAnimationClip_Jump,					//�W�����v
		enAnimationClip_Walk,					//����
		enAnimationClip_Run,					//����
		enAnimationClip_Num,	//4				//�����B
	};
	AnimationClip m_animationClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v�̑����̔z��

	
	//��ԊǗ�
	int m_playerState = 0;						//�X�e�[�g�Ǘ��p�̕ϐ�
	int m_itemCount = 0;						//�A�C�e���̃J�E���g
};

