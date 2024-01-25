#pragma once
#include "Engine\GameObject.h"
#include<vector>

class Stage :
    public GameObject
{
	int hFloor_;
	int hWall_;

	std::vector<std::vector<int>> mapArray;
public:
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

