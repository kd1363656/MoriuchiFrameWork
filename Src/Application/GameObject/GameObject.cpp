#include "GameObject.h"

void GameObject::Init()
{
	for (const auto& [key_ , value_] : m_componentList)
	{
		value_->Init();
	}
}
void GameObject::PostLoadInit()
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
void GameObject::Update()
{
	for (const auto& [key_, value_] : m_componentList)
	{
		value_->Update();
	}
}
void GameObject::PostUpdate()
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