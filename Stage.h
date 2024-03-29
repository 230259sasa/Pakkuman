#pragma once
#include "Engine\GameObject.h"
#include<vector>

//using namespace std;
enum STAGE_OBJ {
	FLOOR,
	WALL,
};
const int STAGE_FLOOR(0);
const int STAHE_WALL(1);

class Stage :
    public GameObject
{
	int hFloor_;
	int hWall_;

	//std::vector<std::vector<int>> mapArray;
	std::vector<std::vector<int>> stageData;
	int stageWidth_, stageHeight_;
public:
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
public:
	int GetStageWidth() { return stageWidth_; }
	int GetStageHeight() { return stageHeight_; }
	bool IsWall(int _x, int _y);
};

