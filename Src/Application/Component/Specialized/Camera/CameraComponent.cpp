#include "CameraComponent.h"

#include "../../../GameObject/GameObject.h"

#include "../../ParentComponent/ParentComponent.h"
#include "../../Transform/3D/Transform3DComponent.h"

void CameraComponent::Init()
{
	if(!m_camera)
	{
		m_camera = std::make_shared<KdCamera>();
	}
}

void CameraComponent::PreUpdate()
{
	m_camera->SetCameraMatrix(m_matrix);
}

void CameraComponent::PreDraw() const
{
	if (!m_camera) { return; }

	m_camera->SetToShader();
}

void CameraComponent::FixMatrix()
{
	// 座標の確定は"Update,PostUpdate"で座標、回転の更新が行われてから更新
	const Math::Matrix transMat_    = Math::Matrix::CreateTranslation   (m_position);
	const Math::Matrix rotationMat_ = Math::Matrix::CreateFromQuaternion(m_rotation);

	m_matrix = transMat_ * rotationMat_;

	// もし親行列がいるなら合成する
	if (auto owner_ = GetOwner())
	{
		if (auto parentComponent_ = owner_->GetComponent<ParentComponent>().lock())
		{
			if(auto parent_ = parentComponent_->GetParent().lock())
			{
				m_matrix *= parent_->GetMatrix();
			}
		}
	}
}