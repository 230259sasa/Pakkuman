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
	int hpMax_;
	int hpCrr_;
	int vecx;
	int vecy;
public:
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	int GetVectorX() { return int(transform_.position_.x); }
	int GetVectorZ() { return int(transform_.position_.z); }
	float GetFloatPosX() { return transform_.position_.x; }
	float GetFloatPosZ() { return transform_.position_.z; }

	void OnCollision(GameObject* pTarget);
};