#pragma once

// アセットへのファイルパスを選択するためのコンポーネント
class AssetFilePathCommonBehaviorComponent : public Component::CommonBehaviorBase
{
public:

	AssetFilePathCommonBehaviorComponent()          = default;
	~AssetFilePathCommonBehaviorComponent() override = default;

	void Init() override;

	void ImGuiPrefabInspector(const char* Label);
	
	void           LoadPrefabData(const nlohmann::json& Json) override;
	nlohmann::json SavePrefabData()                           override;
	
	std::string_view GetAssetFilePath() const { return m_assetFilePath; }

	bool GetHasPathChanged() const { return m_hasPathChanged; }

private:

	std::string m_assetFilePath = "";

	bool m_hasPathChanged = false;
};