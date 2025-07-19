#pragma once

#include"../BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public:

	GameScene ()          = default;
	~GameScene() override = default;

	void Init()  override;

private:

	void Event() override;
};
