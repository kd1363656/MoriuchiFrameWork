#pragma once

// カメラは固有の処理が多いので一つのコンポーネントにまとめる
// 再利用性の高い処理のみを書いてき、細かな処理は固有コンポーネントで書き込む
class CameraCommonComponent : public Component::OwnedBase
{
public:

	CameraCommonComponent ()          = default;
	~CameraCommonComponent() override = default;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<CameraCommonComponent>(); }

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