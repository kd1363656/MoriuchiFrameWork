#pragma once
#include "../../Application/Utility/Singleton/SingletonBase.h"

class GameObject;

class ImGuiManager : public SingletonBase<ImGuiManager>
{

public:

	void Init();
	
	void Update();

private:

	void UpdateHierarchyWindow    ();
	void UpdateAddGameObjectButton() const;

	void UpdateInspectorWindow     ();
	void UpdateComponentInspector  (std::shared_ptr<GameObject> GameObject) const;
	void UpdateAddComponentSelector(std::shared_ptr<GameObject> GameObject);
	void UpdateAddComponentButton  (std::shared_ptr<GameObject> GameObject) const;

	std::weak_ptr<GameObject> m_inspectorWindowTargetGameObject;

	std::string m_selectedComponentName = "";

	// ========================
	// Singleton
	// ========================
	friend class SingletonBase<ImGuiManager>;

	ImGuiManager ()          = default;
	~ImGuiManager() override = default;

};