#pragma once

class Transform3DComponent;

class Transform3DLinkerComponent : public Component::CommonBehaviorBase
{
public:

	Transform3DLinkerComponent ()          = default;
	~Transform3DLinkerComponent() override = default;

	std::shared_ptr<Transform3DComponent> GetTransform3DComponent() const { return m_transform3DComponent.lock(); }

	void SetTransform3DComponent(std::weak_ptr<Transform3DComponent> Set) { m_transform3DComponent = Set; }

private:

	std::weak_ptr<Transform3DComponent> m_transform3DComponent;

};