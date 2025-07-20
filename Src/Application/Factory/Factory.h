#pragma once
#include "../Utility/SingletonBase.h"
#include "../Utility/String/StringUtility.h"
#include "../Utility/Common/CommonStruct.h"

class Factory : public SingletonBase<Factory>
{

public:

	void Init();

	// "KdGameObject"の派生クラスの名前をキーとしてインスタンスを生成する
	template <class ComponentType>
		requires std::is_base_of_v<ComponentBase , ComponentType>
	void RegisterGameObjectFactoryMethod()
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

private:

	void RegisterGameObjectFactoryMethod();

	std::unordered_map<std::string , std::function<std::shared_ptr<ComponentBase>()>> m_componentFactoryMethodList;

private:

	friend class SingletonBase<Factory>;

	Factory ()          = default;
	~Factory() override = default;

};