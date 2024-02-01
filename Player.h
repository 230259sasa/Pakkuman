#pragma once
#include "Engine\GameObject.h"

class Stage;

enum Dir {
	UP, RIGHT, DOWN, LEFT, NONE
};

class Player :
    public GameObject
{
	int hModel_;
	float speed_;
	Stage* pStage;
public:
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
