#pragma once

class Transform3DComponent : public ComponentBase
{
public:

	Transform3DComponent ()          = default;
	~Transform3DComponent() override = default;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<Transform3DComponent>(); }

	void Init() override;

	void PreUpdate() override;

	void ImGuiComponentViewer() override;
	
	void           Deserialize(const nlohmann::json& Json) override; 
	nlohmann::json Serialize  ()                           override;
	
	const Math::Matrix& GetMatrix() const { return m_matrix; }

private:

	Math::Vector3    m_position = Math::Vector3::Zero;
	Math::Quaternion m_rotation = Math::Quaternion::Identity;
	Math::Vector3    m_scale    = Math::Vector3::Zero;

	Math::Matrix m_matrix = Math::Matrix::Identity;
};