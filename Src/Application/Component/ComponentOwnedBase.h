#pragma once
#include "Component.h"

// ゲームオブジェクトに持たせることを想定したコンポーネントの基底クラス
// ゲームオブジェクト直下のコンポーネントにのみゲームオブジェクトへのアクセスを許すことで
// 共通する処理を持つコンポーネントへの必要なコンポーネントのセットを"PrimaryBase"のみで行うことができ保守性が高くなる
class Component::OwnedBase
{
public:

	OwnedBase         () = default;
	virtual ~OwnedBase() = default;

	virtual uint32_t GetTypeID() const = 0;

	// "PostLoadInit"は"Json"で読み込んだデータを読み込んだあとにする
	virtual void Init        () { /*　必要に応じてオーバーライドしてください */ };
	virtual void PostLoadInit() { /*　必要に応じてオーバーライドしてください */ };
	
	virtual void PreUpdate () { /*　必要に応じてオーバーライドしてください */ }
	virtual void Update    () { /*　必要に応じてオーバーライドしてください */ }
	virtual void PostUpdate() { /*　必要に応じてオーバーライドしてください */ }

	virtual void ImGuiSpawnInspector () { /*　必要に応じてオーバーライドしてください */ }
	virtual void ImGuiPrefabInspector() { /*　必要に応じてオーバーライドしてください */ }

	virtual void           Deserialize(const nlohmann::json& Json) { /*　必要に応じてオーバーライドしてください */ }
	virtual nlohmann::json Serialize  ()                           { return nlohmann::json();					   }
	
	virtual void           LoadPrefabData(const nlohmann::json& Json) { /*　必要に応じてオーバーライドしてください */ }
	virtual nlohmann::json SavePrefabData()                           { return nlohmann::json();                      }

	std::string_view GetTypeName() const { return m_typeName; }

	bool GetIsDeleteRequested()const { return m_isDeleteRequested; }

	void SetOwner(std::weak_ptr<GameObject> Set) { m_owner = Set; }

	void SetTypeName(const std::string& TypeName) { m_typeName = TypeName; }

	void SetIsDeleteRequested(bool Set) { m_isDeleteRequested = Set; }


protected:
	
	std::shared_ptr<GameObject> GetOwner()const { return m_owner.lock(); }
	
private:
	
	std::weak_ptr<GameObject> m_owner;
	
	std::string m_typeName = "";
	
	bool m_isDeleteRequested = false;

};

class ComponentID
{

public:

	template <class ComponentType>
		requires std::derived_from<ComponentType, Component::OwnedBase>
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