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

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

