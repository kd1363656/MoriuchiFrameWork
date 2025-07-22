#pragma once
#include "../../Application/Utility/Singleton/SingletonBase.h"

class GameObject;

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

	void UpdateHierarchyWindow    ();
	void UpdateAddGameObjectButton() const;

	std::weak_ptr<GameObject> m_inspectorWindowTargetGameObject;

	uint32_t m_popUpFlag = 0u;

	// ========================
	// Singleton
	// ========================
	friend class SingletonBase<ImGuiManager>;

	ImGuiManager ()          = default;
	~ImGuiManager() override = default;

};