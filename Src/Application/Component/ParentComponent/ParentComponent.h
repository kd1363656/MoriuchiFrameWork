#pragma once

class Transform3DComponent;

class ParentComponent : public ComponentBase
{
public:

	ParentComponent ()          = default;
	~ParentComponent() override = default;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<ParentComponent>(); }

	void PostLoadInit() override;

	void ImGuiComponentViewer() override;

	std::weak_ptr<Transform3DComponent> GetParent() const { return m_transform3DComponent; }
	
private:

	std::weak_ptr<Transform3DComponent> m_transform3DComponent;

};