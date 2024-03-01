#pragma once
#include "Engine/GameObject.h"
class Energy :
    public GameObject
{
	int hModel_;
public:
	Energy(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetPos(float _x, float _z);

	void OnCollision(GameObject* pTarget);
};

