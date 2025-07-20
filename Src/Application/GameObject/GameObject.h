#pragma once

class GameObject
{
public:

	GameObject () = default;
	~GameObject() = default;

	void Init        ();
	void PostLoadInit();

	void PreUpdate ();
	void Update    ();
	void PostUpdate();

	void DeleteRequestedComponent();

	// 存在しないコンポーネントのみを追加
	template <class ComponentType>
		requires std::is_base_of_v<ComponentBase, ComponentType>
	void AddComponent(std::shared_ptr<ComponentBase> WantAdd)
	{
		const uint32_t id_ = ComponentID::GetTypeID<ComponentType>();

		m_componentList.try_emplace(id_ , WantAdd);
	}

	// コンポーネントを取得
	template <class ComponentType>
		requires std::is_base_of_v<ComponentBase , ComponentType>
	std::weak_ptr<ComponentType> GetComponent()
	{
		const uint32_t id_ = ComponentID::GetTypeID<ComponentType>();
	
		if(auto itr_  = m_componentList.find(id_);
		        itr_ != m_componentList.end()   )
		{
			return std::static_pointer_cast<ComponentType>(itr_->second);
		}

		return std::weak_ptr<ComponentType>();
	}

private:

	std::unordered_map<uint32_t, std::shared_ptr<ComponentBase>> m_componentList;
};