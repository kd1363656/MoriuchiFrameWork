#include "CameraCommonComponent.h"

#include "../../../GameObject/GameObject.h"

#include "../../Transform/3D/Transform3DComponent.h"

void CameraCommonComponent::Init()
{
	if(!m_camera)
	{
		m_camera = std::make_shared<KdCamera>();
	}
}

void CameraCommonComponent::PreUpdate()
{
	m_camera->SetCameraMatrix(m_matrix);
}

void CameraCommonComponent::PreDraw() const
{
	if (!m_camera) { return; }

	m_camera->SetToShader();
}

void CameraCommonComponent::FixMatrix()
{
	// 座標の確定は"Update,PostUpdate"で座標、回転の更新が行われてから更新
	const Math::Matrix transMat_    = Math::Matrix::CreateTranslation   (m_position);
	const Math::Matrix rotationMat_ = Math::Matrix::CreateFromQuaternion(m_rotation);

	m_matrix = transMat_ * rotationMat_;
}