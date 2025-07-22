#include "GameObject.h"

#include "../Utility/String/StringUtility.h"

void GameObject::Init()
{
	for (const auto& [key_ , value_] : m_componentList)
	{
		value_->Init();
		value_->SetOwner(shared_from_this());
	}

	m_typeName = typeid(*this).name();
	StringUtility::StripClassPrefix(m_typeName);

	m_deleteRequested = false;
}
void GameObject::PostLoadInit() const
{
	for (const auto& [key_, value_] : m_componentList)
	{
		value_->PostLoadInit();
	}
}

void GameObject::PreUpdate()
{
	// 必要のないコンポーネントを削除
	DeleteRequestedComponent();

	for (const auto& [key_, value_] : m_componentList)
	{
		value_->PreUpdate();
	}
}
void GameObject::Update() const
{
	for (const auto& [key_, value_] : m_componentList)
	{
		value_->Update();
	}
}
void GameObject::PostUpdate() const
{
	for (const auto& [key_, value_] : m_componentList)
	{
		value_->PostUpdate();
	}
}

void GameObject::DeleteRequestedComponent()
{
	auto itr_ = m_componentList.begin();

	while(itr_ != m_componentList.end())
	{
		if(itr_->second)
		{
			if(itr_->second->GetIsDeleteRequested())
			{
				itr_ = m_componentList.erase(itr_);
			}
			else
			{
				itr_++;
			}
		}
		else
		{
			itr_++;
		}
	}
}