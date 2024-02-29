#include "Enemy.h"
#include "Engine\Model.h"
#include "Stage.h"
#include "Player.h"
#include "Engine\Input.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), speed_(0), pStage(nullptr)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model\\Bullet.fbx");
	assert(hModel_ >= 0);
	pStage = (Stage*)FindObject("Stage");
	speed_ = 0.1f;
	transform_.position_ = { 13,0.3,-13 };
	SphereCollider* collision = new SphereCollider(XMFLOAT3(-0.5, 0, 0.4), 0.3f);
	AddCollider(collision);
}

void Enemy::Update()
{
	if (Frame <= 0) {
		Pursue();
		Frame = 100;
	}
	else
		Frame--;

	//��̊֐��ł������v���C���[�̈ʒu�܂ł̓��̂��H��
	//�܂�PursueArr�̂ǂ̈ʒu�ɂ��邩�𒲂ׂ�
	// �������玟�Ɍ��������W�����߂�
	// �ړ�
	//
	//XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	//XMVECTOR move{ 0,0,0,0 };
	/*int nowpos = 0;
	
	int myx = (int)(XMVectorGetX(pos) - 0.5);
	int myy = (int)(XMVectorGetZ(pos) * -1 + 0.4);
	for (int i = 0; i < PursueArr.size(); i++) {
		if (myx == PursueArr[i].x && myy == PursueArr[i].y) {
			nowpos = i;
			break;
		}
	}
	
	if (nowpos + 1 < PursueArr.size())
		if (nowpos < PursueArr.size()) {
			if (myx != PursueArr[nowpos + 1].x) {
				if (myx - PursueArr[nowpos + 1].x <= 0) {
					move = XMVECTOR{ 1,0,0,0 };
				}
				else {
					move = XMVECTOR{ -1,0,0,0 };
				}
			}
			else if (myy != PursueArr[nowpos + 1].y) {
				if (myy - PursueArr[nowpos + 1].y >= 0) {
					move = XMVECTOR{ 0,0,1,0 };
				}
				else {
					move = XMVECTOR{ 0,0,-1,0 };
				}
			}
		}*/
	/*pos = pos + speed_ * move;
	XMStoreFloat3(&(transform_.position_), pos);*/

	// Pursue�𓮂�������nowarr��������
	// nowarr�̐������Q�Ƃ��Ĕz�񂩂���W�����o��
	// ���W�Ɍ������Ĉړ�
	// �ړI�n�ɒ�������nowarr��+1(PursueArr�̑傫���𒴂�����ړ������Ȃ�)
	//
	

	//PursueArr�̑傫����nowarr����������ړ������Ȃ�
	if (PursueArr.size() > nowarrpos) {
		float x, z;//�����̈ʒu����ړI�n�܂ł̋���
		x = PursueArr[nowarrpos].x - startX;
		z = PursueArr[nowarrpos].y - startZ;
		//rate��1�t���[���Ɉړ����銄��
		// �����͈ړ���/����  
		// ������1�𒴂���ꍇ��rate=1.0�ɂ���
		//
		rateX += speed_ / x;
		rateZ += speed_ / z;
		if (rateX > 1.0f) {
			rateX = 1.0f;
		}
		if (rateZ > 1.0f) {
			rateZ = 1.0f;
		}
		//����*���[�g+�����ʒu�ňړ�
		transform_.position_.x = x * rateX + startX;
		transform_.position_.z = z * rateZ + startZ;
		//�ڕW�n�_�ɒ�������nowarr��+�P
		if (rateX >= 1.0f && rateZ >= 1.0f) {
			nowarrpos++;
		}
	}
}

void Enemy::Draw()
{
	Transform t = transform_;
	t.position_.x = transform_.position_.x - 0.5;
	t.position_.z = transform_.position_.z + 0.4;
	Model::SetTransform(hModel_, t);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::Pursue()
{
	//
	// ����
	// �G�l�~�[�̈ʒu�ƃv���C���[�̈ʒu���擾
	// ��}�X�ړ������}�X���擾
	// ��̃}�X����1�}�X�ړ������}�X���擾
	// �v���C���[�̃}�X�ɂ���܂ŌJ��Ԃ�
	// 
	// �擾�����v���C���[�܂ł̃}�X�̍��W��z��ɓ����
	// 
	// 
	// ����
	// int�^�ɕϊ����邹���Ŏ��ۂ̈ʒu�ƍs�������ꏊ�Ō덷�������Ă���
	// �l���̍��W�ł����Ȃ��Ă��Ȃ��̂ŕǂƂ̓����蔻�肪�@�\���Ă��Ȃ�
	//
	nowarrpos = 0;
	startX = transform_.position_.x;
	startZ = transform_.position_.z;
	Player* pPlayer;
	pPlayer = (Player*)FindObject("Player");
	int px = pPlayer->GetVectorX();
	int py = pPlayer->GetVectorY();
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	int myx = (int)(XMVectorGetX(pos) + 0.5);
	int myy = (int)(XMVectorGetZ(pos) * -1 + 0.4);
	Transform m;
	int tx, ty, rx, ry;
	
	PursueArr.clear();

	for (int i = 0; i < STAGE_SIZE; i++) {
		for (int j = 0; j < STAGE_SIZE; j++) {
			table[i][j] = -1;
		}
	}

	//�����̈ʒu���O�Ƃ���
	table[myy][myx] = 0;

	int num = 0;
	//�v���C���[�̍��W�ɐ��������蓖�Ă��Ă��Ȃ����
	//�ǂɈ͂܂ꂽ�疳�����[�v�Ƃ��G���[������
	//num > 100�͓��؂�������Ȃ�������Ƃ��������̂���
	//���������蓖�Ă��Ȃ�������̂ق����X�}�[�g�H
	while (table[py][px] < 0 && num < 100) {
		//table����num�̒l��T��
		for (int y = 0; y < STAGE_SIZE; y++) {
			for (int x = 0; x < STAGE_SIZE; x++) {
				if (table[y][x] == num) {
					//num�̒l����c���̍��W�����������ǂ���Ȃ�������num+1�̒l������
					if (y + 1 >= 0 && y + 1 < STAGE_SIZE) {//�z��̒l����
						if (table[y + 1][x] < 0 && !pStage->IsWall(x,y + 1))
							table[y + 1][x] = num + 1;
					}
					if (y - 1 >= 0 && y - 1 < STAGE_SIZE) {
						if (table[y - 1][x] < 0 && !pStage->IsWall(x, y - 1))
							table[y - 1][x] = num + 1;
					}
					if (x + 1 >= 0 && x + 1 < STAGE_SIZE) {
						if (table[y][x + 1] < 0 && !pStage->IsWall(x + 1, y))
							table[y][x + 1] = num + 1;
					}
					if (x - 1 >= 0 && x - 1 < STAGE_SIZE) {
						if (table[y][x - 1] < 0 && !pStage->IsWall(x - 1, y))
							table[y][x - 1] = num + 1;
					}
				}
			}
		}
		num++;
	}

	//��ɓ��ꂽ���؂����W�ɂ��Ĕz��ɂ����
	//�v���C���[�̈ʒu���炳���̂ڂ��Ă���
	int nownum = table[py][px];
	Vec nowvec;
	nowvec.x = px;
	nowvec.y = py;
	std::vector<Vec> Arr;
	while (nownum > 0 && num < 99) {
		if (nowvec.y + 1 >= 0 && nowvec.y + 1 < STAGE_SIZE)
			if (table[nowvec.y + 1][nowvec.x] == nownum - 1)
				nowvec.y += 1;
		if (nowvec.y - 1 >= 0 && nowvec.y - 1 < STAGE_SIZE)
			if (table[nowvec.y - 1][nowvec.x] == nownum - 1)
				nowvec.y -= 1;
		if (nowvec.x + 1 >= 0 && nowvec.x + 1 < STAGE_SIZE)
			if (table[nowvec.y][nowvec.x + 1] == nownum - 1)
				nowvec.x += 1;
		if (nowvec.x - 1 >= 0 && nowvec.x - 1 < STAGE_SIZE)
			if (table[nowvec.y][nowvec.x - 1] == nownum - 1)
				nowvec.x -= 1;

		Arr.push_back(nowvec);

		nownum--;
	}

	for (int i = Arr.size(); i > 0; i--) {
		PursueArr.push_back(Arr[i - 1]);
	}
	nowPursue = 0;

	Arr.clear();

	//float x, z;//�����̈ʒu����ړI�n�܂ł̋���
	//x = PursueArr[0].x - startX;
	//z = PursueArr[0].y - startZ;
	//rateX = speed_ / x;
	//rateZ = speed_ / z;
}