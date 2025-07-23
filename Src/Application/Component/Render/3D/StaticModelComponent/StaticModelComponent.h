#pragma once
#include "../Render3DCommonBehaviorComponent.h"
#include "../../../Linker/Transform/3D/Transform3DLinkerComponent.h"
#include "../../../AssetFilePath/AssetFilePathCommonBehaviorComponent.h"

class StaticModelComponent : public Component::OwnedBase
{

public:

	StaticModelComponent ()          = default;
	~StaticModelComponent() override = default;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<StaticModelComponent>(); }

	void Init        ()override;
	void PostLoadInit() override;

	void Draw(const Render3DCommonBehaviorComponent::DrawType   DrawType  ) const;
	void Draw(const Render3DCommonBehaviorComponent::ShaderType ShaderType) const;

	void           LoadPrefabData(const nlohmann::json& Json) override;
	nlohmann::json SavePrefabData()                           override;

	void ImGuiPrefabInspector() override;

private:

	std::shared_ptr<KdModelData> m_modelData = nullptr;

	Render3DCommonBehaviorComponent      m_render3DCommonBehaviorComponent;
	AssetFilePathCommonBehaviorComponent m_assetFilePathCommonBehaviorComponent;
	Transform3DLinkerComponent			 m_transform3DLinkerComponent;
};