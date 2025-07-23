#pragma once
#include "../Render3DCommonComponent.h"
#include "../../../AssetFilePath/AssetFilePathComponent.h"
#include "../../../Linker/Transform/3D/Transform3DLinkerComponent.h"

class AnimationModelComponent : public Component::OwnedBase
{

public:

	AnimationModelComponent ()          = default;
	~AnimationModelComponent() override = default;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<AnimationModelComponent>(); }

	void Init        () override;
	void PostLoadInit() override;

	void Draw(const Render3DCommonComponent::DrawType   DrawType  ) const;
	void Draw(const Render3DCommonComponent::ShaderType ShaderType) const;

	void           LoadPrefabData(const nlohmann::json& Json) override;
	nlohmann::json SavePrefabData()                           override;

	void ImGuiComponentViewer() override;

private:

	std::shared_ptr<KdModelWork> m_modelData = nullptr;

	AssetFilePathComponent     m_assetFilePathComponent;
	Render3DCommonComponent    m_render3DCommonComponent;
	Transform3DLinkerComponent m_transform3DLinkerComponent;
};