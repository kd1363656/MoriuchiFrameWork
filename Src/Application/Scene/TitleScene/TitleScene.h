﻿#pragma once

#include"../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:

	TitleScene ()          = default;
	~TitleScene() override = default;

	void Init()  override;

private:

	void Event() override;
};
