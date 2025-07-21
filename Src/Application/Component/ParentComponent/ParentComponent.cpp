#include "ParentComponent.h"

#include "../Transform/3D/Transform3DComponent.h"

#include "../../GameObject/GameObject.h"

void ParentComponent::PostLoadInit()
{
	auto owner_ = GetOwner().lock();

	if (owner_)
	{
		m_transform3DComponent = owner_->GetComponent<Transform3DComponent>();
	}
}

void ParentComponent::ImGuiComponentViewer()
{
	std::string label_ = "ParentComponent is";

	auto transform3DComponent_ = m_transform3DComponent.lock();

	label_ += transform3DComponent_ ? "active" : "not active";

	ImGui::Text(label_.c_str());
}