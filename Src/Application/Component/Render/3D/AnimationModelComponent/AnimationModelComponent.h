#pragma once
#include "../Render3DComponent.h"

class AnimationModelComponent : public ComponentBase
{

public:

	AnimationModelComponent ()          = default;
	~AnimationModelComponent() override = default;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<AnimationModelComponent>(); }

	void PostLoadInit() override;

	void Draw(const Render3DComponent::DrawType   DrawType  ) const;
	void Draw(const Render3DComponent::ShaderType ShaderType) const;

	void           LoadPrefabData(const nlohmann::json& Json) override;
	nlohmann::json SavePrefabData()                           override;

	void ImGuiComponentViewer() override;

private:

	std::shared_ptr<KdModelWork> m_modelData = nullptr;

	std::string m_assetFilePath = "";

	Render3DComponent m_renderComponent;

};