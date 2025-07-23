#pragma once
#include "Component.h"

class Component::CommonBehaviorBase : public std::enable_shared_from_this<Component::CommonBehaviorBase>
{
public:

	CommonBehaviorBase         () = default;
	virtual ~CommonBehaviorBase() = default;

	// "PostLoadInit"は"Json"で読み込んだデータを読み込んだあとにする
	virtual void Init        () { /*　必要に応じてオーバーライドしてください */ };
	virtual void PostLoadInit() { /*　必要に応じてオーバーライドしてください */ };
	
	virtual void PreUpdate () { /*　必要に応じてオーバーライドしてください */ }
	virtual void Update    () { /*　必要に応じてオーバーライドしてください */ }
	virtual void PostUpdate() { /*　必要に応じてオーバーライドしてください */ }

	virtual void ImGuiComponentViewer() { /*　必要に応じてオーバーライドしてください */ }

	virtual void           Deserialize(const nlohmann::json& Json) { /*　必要に応じてオーバーライドしてください */ }
	virtual nlohmann::json Serialize  ()                           { return nlohmann::json();					   }
	
	virtual void           LoadPrefabData(const nlohmann::json& Json) { /*　必要に応じてオーバーライドしてください */ }
	virtual nlohmann::json SavePrefabData()                           { return nlohmann::json();                      }

	std::string_view GetTypeName() const { return m_typeName; }

	void SetTypeName(const std::string& TypeName) { m_typeName = TypeName; }

private:
	
	std::string m_typeName = "";
	
};