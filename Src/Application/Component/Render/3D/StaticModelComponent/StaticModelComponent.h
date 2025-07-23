#pragma once
#include "../Render3DCommonComponent.h"
#include "../../../AssetFilePath/AssetFilePathComponent.h"
#include "../../../Linker/Transform/3D/Transform3DLinkerComponent.h"

class StaticModelComponent : public Component::OwnedBase
{

public:

	StaticModelComponent ()          = default;
	~StaticModelComponent() override = default;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<StaticModelComponent>(); }

	void Init        ()override;
	void PostLoadInit() override;

	void Draw(const Render3DCommonComponent::DrawType   DrawType  ) const;
	void Draw(const Render3DCommonComponent::ShaderType ShaderType) const;

	void           LoadPrefabData(const nlohmann::json& Json) override;
	nlohmann::json SavePrefabData()                           override;

	void ImGuiComponentViewer() override;

private:

	std::shared_ptr<KdModelData> m_modelData = nullptr;

	Render3DCommonComponent    m_render3DCommonComponent;
	AssetFilePathComponent     m_assetFilePathComponent;
	Transform3DLinkerComponent m_transform3DLinkerComponent;
};