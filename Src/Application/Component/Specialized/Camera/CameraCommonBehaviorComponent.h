#pragma once

// カメラは固有の処理が多いので一つのコンポーネントにまとめる
// 再利用性の高い処理のみを書いてき、細かな処理は固有コンポーネントで書き込む
class CameraCommonBehaviorComponent : public Component::CommonBehaviorBase
{
public:

	CameraCommonBehaviorComponent ()          = default;
	~CameraCommonBehaviorComponent() override = default;

	void Init() override;
	
	void PreDraw  () const;

	void PreUpdate() override;
	
	void ImGuiSpawnInspector () override;
	void ImGuiPrefabInspector() override;

private:

	void FixMatrix();

	std::shared_ptr<KdCamera> m_camera = nullptr;

	Math::Matrix m_matrix;

	Math::Quaternion m_rotation = Math::Quaternion::Identity;
	Math::Vector3    m_position = Math::Vector3::Zero;

	float m_fov = 0.0f;
};