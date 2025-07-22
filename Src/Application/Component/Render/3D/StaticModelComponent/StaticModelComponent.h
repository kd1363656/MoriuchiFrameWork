#pragma once
#include "../Render3DComponent.h"
#include "../../../AssetFilePath/AssetFilePathComponent.h"

class StaticModelComponent : public ComponentBase
{

public:

	StaticModelComponent ()          = default;
	~StaticModelComponent() override = default;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<StaticModelComponent>(); }

	void Init        ()override;
	void PostLoadInit() override;

	void Draw(const Render3DComponent::DrawType   DrawType  ) const;
	void Draw(const Render3DComponent::ShaderType ShaderType) const;

	void           LoadPrefabData(const nlohmann::json& Json) override;
	nlohmann::json SavePrefabData()                           override;

	void ImGuiComponentViewer() override;

private:

	std::shared_ptr<KdModelData> m_modelData = nullptr;

	Render3DComponent      m_renderComponent;
	AssetFilePathComponent m_assetFilePathComponent;
};