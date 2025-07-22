#include "Factory.h"

#include "../GameObject/GameObject.h"

#include "../Component/Render/3D/AnimationModelComponent/AnimationModelComponent.h"
#include "../Component/Render/3D/StaticModelComponent/StaticModelComponent.h"
#include "../Component/Transform/3D/Transform3DComponent.h"
#include "../Component/ParentComponent/ParentComponent.h"

#include "../Scene/SceneManager.h"

void Factory::Init()
{
	RegisterComponentFactoryMethod();
}

void Factory::AttachComponent(std::weak_ptr<GameObject> GameObject, std::string_view WantAttachComponent)
{
	auto itr_ = m_componentFactoryMethodList.find(WantAttachComponent);

	if (itr_ == m_componentFactoryMethodList.end())
	{
		KdDebugGUI::Instance().AddLog("Component factory method not found: %s\n", WantAttachComponent.data());
		return;
	}

	auto component_ = itr_->second();
	// コンポーネントの所持者、名前を設定
	component_->SetOwner   (GameObject);
	component_->SetTypeName(itr_->first);

	if (auto gameObject_ = GameObject.lock())
	{
		gameObject_->AddComponent(component_);
	}
	else
	{
		KdDebugGUI::Instance().AddLog("GameObject is expired when attaching component: %s\n", WantAttachComponent.data());
	}
}

std::shared_ptr<GameObject> Factory::CreateGameObject() const
{
	return std::make_shared<GameObject>();
}

void Factory::RegisterComponentFactoryMethod()
{
#ifdef _DEBUG
	KdDebugGUI::Instance().AddLog("============ Start register gameObject factory ============\n\n");
#endif // _DEBUG

	RegisterComponentFactoryMethod<AnimationModelComponent>();
	RegisterComponentFactoryMethod<StaticModelComponent>   ();
	RegisterComponentFactoryMethod<Transform3DComponent>   ();
	RegisterComponentFactoryMethod<ParentComponent>        ();

#ifdef _DEBUG
	KdDebugGUI::Instance().AddLog("\n============ End register gameObject factory ==============\n\n\n\n");
#endif // _DEBUG
}