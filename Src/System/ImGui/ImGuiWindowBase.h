#pragma once

class ImGuiWindowBase
{
public:

	ImGuiWindowBase         () = default;
	virtual ~ImGuiWindowBase() = default;

	virtual void Init  () { /*　必要に応じてオーバーライドしてください */ }
	virtual void Update() { /*　必要に応じてオーバーライドしてください */ }
	
};