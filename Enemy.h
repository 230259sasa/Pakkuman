#pragma once
#include "Engine\GameObject.h"
#include<vector>

class Stage;

const int STAGE_SIZE(15);

class Enemy :
    public GameObject
{
	struct Vec {
		int x;
		int y;
	};
	int hModel_;
	float speed_;
	Stage* pStage;
	int table[STAGE_SIZE][STAGE_SIZE];
	int nowPursue;
	std::vector<Vec> PursueArr;
	int Frame;
public:
	Enemy(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void Pursue();
};

