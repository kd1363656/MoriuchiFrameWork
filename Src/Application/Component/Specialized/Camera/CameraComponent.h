#pragma once

// カメラは固有の処理が多いので一つのコンポーネントにまとめる
class CameraComponent : public ComponentBase
{
public:

	CameraComponent ()          = default;
	~CameraComponent() override = default;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<CameraComponent>(); }

	void Init() override;
	
	void PreUpdate() override;
	void PreDraw  () const;

private:

	void FixMatrix();

	std::shared_ptr<KdCamera> m_camera = nullptr;

	Math::Vector3    m_position = Math::Vector3::Zero;
	Math::Quaternion m_rotation = Math::Quaternion::Identity;

	Math::Matrix m_matrix;
};