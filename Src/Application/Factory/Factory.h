#pragma once
#include "../Utility/Singleton/SingletonBase.h"
#include "../Utility/String/StringUtility.h"
#include "../Utility/Common/CommonStruct.h"

class GameObject;

struct StringHash
{
	// "C++14"以降で追加された"TransparentLookUp"を生かした設計手法
	using is_transparent = void;

	size_t operator()(const std::string& Key) const { return std::hash<std::string>     {}(Key); }
	size_t operator()(std::string_view   Key) const { return std::hash<std::string_view>{}(Key); }
	size_t operator()(const char*        Key) const { return std::hash<std::string_view>{}(Key); }
};

class Factory : public SingletonBase<Factory>
{

public:

	void Init();

	// "KdGameObject"の派生クラスの名前をキーとしてインスタンスを生成する
	// "std::derived_from"を使っているのは基底クラスに仮想関数があり基底クラスが
	// インスタンス化できないため"std::is_base_of"を使う必要性がないから
	template <class ComponentType>
		requires std::derived_from<ComponentType, Component::OwnedBase>
	void RegisterComponentFactoryMethod()
	{
		// コンポーネント名を取得
		std::string componentName_ = typeid(ComponentType).name();
		StringUtility::StripClassPrefix(componentName_);

		const auto factory_ = []() -> std::shared_ptr<ComponentType>
		{
			return std::make_shared<ComponentType>();
		};

		m_componentFactoryMethodList.try_emplace(componentName_, factory_);
	}

	void AttachComponent(std::weak_ptr<GameObject> GameObject , std::string_view WantAttachComponent);

	std::shared_ptr<GameObject> CreateGameObject() const;

	auto& GetComponentFactoryMethodList() { return m_componentFactoryMethodList; }

private:

	void RegisterComponentFactoryMethod();

	std::unordered_map <std::string, std::function<std::shared_ptr<Component::OwnedBase>()> , StringHash , std::equal_to<>> m_componentFactoryMethodList;

	// =============================
	// "Singleton"
	// =============================
	friend class SingletonBase<Factory>;

	Factory ()          = default;
	~Factory() override = default;

};