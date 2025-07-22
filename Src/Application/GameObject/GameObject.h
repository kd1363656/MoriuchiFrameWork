#pragma once

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:

	GameObject () = default;
	~GameObject() = default;

	void Init        ();
	void PostLoadInit() const;

	void PreUpdate ();
	void Update    () const;
	void PostUpdate() const;

	void DeleteRequestedComponent();

	// 存在しないコンポーネントのみを追加
	void AddComponent(std::shared_ptr<ComponentBase> WantAdd)
	{
		const uint32_t id_ = ComponentID::GetTypeID<ComponentBase>();

		WantAdd->Init();

		m_componentList.try_emplace(id_ , WantAdd);
	}

	// コンポーネントを取得
	template <class ComponentType>
		requires std::derived_from<ComponentType , ComponentBase>
	std::weak_ptr<ComponentType> GetComponent() const
	{
		const uint32_t id_ = ComponentID::GetTypeID<ComponentType>();
	
		if(auto itr_  = m_componentList.find(id_);
		        itr_ != m_componentList.end()   )
		{
			return std::static_pointer_cast<ComponentType>(itr_->second);
		}

		return std::weak_ptr<ComponentType>();
	}

	const std::unordered_map<uint32_t, std::shared_ptr<ComponentBase>>& GetComponentList() const { return m_componentList; }

	std::string_view GetTypeName() const { return m_typeName; };

	bool GetIsDeleteRequested() const { return m_deleteRequested; }

	void SetIsDeleteRequested(bool Set) { m_deleteRequested = Set; }

private:

	std::unordered_map<uint32_t, std::shared_ptr<ComponentBase>> m_componentList;

	std::string m_typeName = "";

	bool m_deleteRequested = false;
};