#pragma once
#include "../ImGuiWindowBase.h"

class ImGuiHierarchyWindow : public ImGuiWindowBase
{
public:

	ImGuiHierarchyWindow ()          = default;
	~ImGuiHierarchyWindow() override = default;

	void Update() override;

private:

};