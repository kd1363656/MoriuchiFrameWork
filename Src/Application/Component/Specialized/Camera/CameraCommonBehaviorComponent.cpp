#include "CameraCommonBehaviorComponent.h"

#include "../../../GameObject/GameObject.h"

#include "../../Transform/3D/Transform3DComponent.h"

#include "../../../Utility/Common/CommonConstant.h"

#include "../../../../System/Calculation/Calculation.h"

void CameraCommonBehaviorComponent::Init()
{
	if(!m_camera)
	{
		m_camera = std::make_shared<KdCamera>();
		m_camera->SetProjectionMatrix(0.0f);
	}
}

void CameraCommonBehaviorComponent::PreDraw() const
{
	if (!m_camera) { return; }

	m_camera->SetToShader();
}

void CameraCommonBehaviorComponent::PreUpdate()
{
	const Math::Matrix transMat_    = Math::Matrix::CreateTranslation   (m_position);
	const Math::Matrix rotationMat_ = Math::Matrix::CreateFromQuaternion(m_rotation);

	m_matrix = transMat_ * rotationMat_;

	m_camera->SetCameraMatrix(m_matrix);
}

void CameraCommonBehaviorComponent::ImGuiSpawnInspector()
{
	Math::Vector3 radian_ = Math::Vector3::Zero;

	// クオータニオンをオイラー角に変換
	Calculation::QuaternionToEuler(m_rotation, radian_);

	ImGui::DragFloat3("Position", &m_position.x, 0.1f															  );
	ImGui::DragFloat3("Rotation", &radian_.x   , 1.0f, -CommonConstant::HALF_DEGREE , CommonConstant::HALF_DEGREE );
	
	// 変換したオイラー角の結果をクオータニオンに変換
	Calculation::EulerToQuaternion(radian_ , m_rotation);
}
void CameraCommonBehaviorComponent::ImGuiPrefabInspector()
{
	ImGui::DragFloat("Fov" , &m_fov , 1.0f);

}

void CameraCommonBehaviorComponent::FixMatrix()
{
	// 座標の確定は"Update,PostUpdate"で座標、回転の更新が行われてから更新
	const Math::Matrix transMat_    = Math::Matrix::CreateTranslation   (m_position);
	const Math::Matrix rotationMat_ = Math::Matrix::CreateFromQuaternion(m_rotation);

	m_matrix = transMat_ * rotationMat_;
}