#pragma once
#include "../Render3DCommonBehaviorComponent.h"
#include "../../../AssetFilePath/AssetFilePathCommonBehaviorComponent.h"
#include "../../../Linker/Transform/3D/Transform3DLinkerComponent.h"

class AnimationModelComponent : public Component::OwnedBase
{

public:

	AnimationModelComponent ()          = default;
	~AnimationModelComponent() override = default;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<AnimationModelComponent>(); }

	void Init        () override;
	void PostLoadInit() override;

	void Draw(const Render3DCommonBehaviorComponent::DrawType   DrawType  ) const;
	void Draw(const Render3DCommonBehaviorComponent::ShaderType ShaderType) const;

	void           LoadPrefabData(const nlohmann::json& Json) override;
	nlohmann::json SavePrefabData()                           override;

	void ImGuiPrefabInspector() override;

private:

	std::shared_ptr<KdModelWork> m_modelData = nullptr;

	AssetFilePathCommonBehaviorComponent m_assetFilePathCommonBehaviorComponent;
	Render3DCommonBehaviorComponent      m_render3DCommonBehaviorComponent;
	Transform3DLinkerComponent           m_transform3DLinkerComponent;
};