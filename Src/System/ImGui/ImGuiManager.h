#pragma once
#include "../../Application/Utility/Singleton/SingletonBase.h"

class ImGuiManager : public SingletonBase<ImGuiManager>
{

public:

	enum class PopUpFlag
	{
		Save = 1 << 0 ,
	};

	void Init();
	
	void Update();

private:

	// ========================
	// Singleton
	// ========================
	friend class SingletonBase<ImGuiManager>;

	ImGuiManager ()          = default;
	~ImGuiManager() override = default;

	uint32_t m_popUpFlag = 0u;
};