#include "RenderComponent.h"

#include "../Transform/3D/Transform3DComponent.h"

#include "../../GameObject/GameObject.h"

void RenderComponent::PostLoadInit()
{
	auto owner_ = GetOwner().lock();

	if (owner_)
	{
		m_transform3DComponent = owner_->GetComponent<Transform3DComponent>();	
	}
}

void RenderComponent::ImGuiComponentViewer()
{

}