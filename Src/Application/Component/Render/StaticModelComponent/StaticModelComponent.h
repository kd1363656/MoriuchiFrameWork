#pragma once
#include "../RenderComponent.h"

class StaticModelComponent : public ComponentBase
{

public:

	StaticModelComponent ()          = default;
	~StaticModelComponent() override = default;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<StaticModelComponent>(); }

	void PostLoadInit() override;

	void Draw(const RenderComponent::DrawType   DrawType  ) const;
	void Draw(const RenderComponent::ShaderType ShaderType) const;

private:

	std::shared_ptr<KdModelData> m_modelData = nullptr;

	RenderComponent m_renderComponent;
};