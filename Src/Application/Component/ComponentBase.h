#pragma once

class GameObject;

class ComponentBase : public std::enable_shared_from_this<ComponentBase>
{

public:

	ComponentBase         () = default;
	virtual ~ComponentBase() = default;

	virtual uint32_t GetTypeID() const = 0;

	// "PostLoadInit"は"Json"で読み込んだデータを読み込んだあとにする
	virtual void Init        () { /*　必要に応じてオーバーライドしてください */ };
	virtual void PostLoadInit() { /*　必要に応じてオーバーライドしてください */ };
	
	virtual void PreUpdate () { /*　必要に応じてオーバーライドしてください */ }
	virtual void Update    () { /*　必要に応じてオーバーライドしてください */ }
	virtual void PostUpdate() { /*　必要に応じてオーバーライドしてください */ }

	virtual void ImGuiComponentViewer() = 0;

	virtual void           Deserialize(const nlohmann::json& Json) { /*　必要に応じてオーバーライドしてください */ }
	virtual nlohmann::json Serialize  ()                           { return nlohmann::json();					   }
	
	std::string_view GetTypeName() const { return m_typeName; }

	bool GetIsDeleteRequested()const { return m_isDeleteRequested; }

	void SetOwner(std::weak_ptr<GameObject> Set) { m_owner = Set; }

	void SetTypeName(const std::string_view Set) { m_typeName = Set; }

protected:

	std::weak_ptr<GameObject> GetOwner()const { return m_owner; }

private:

	std::weak_ptr<GameObject> m_owner;

	std::string m_typeName = "";

	bool m_isDeleteRequested = false;
};

class ComponentID
{

public:

	template <class ComponentType>
	static inline uint32_t GetTypeID()
	{
		static uint32_t id_ = GenerateTypeID();
		return id_;
	}

private:

	static inline uint32_t GenerateTypeID()
	{
		static uint32_t id_ = 0u;
		return id_++;
	}

};