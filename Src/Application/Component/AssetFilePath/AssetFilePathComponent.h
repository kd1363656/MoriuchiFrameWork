#pragma once

// アセットへのファイルパスを選択するためのコンポーネント
class AssetFilePathComponent : public Component::CommonBehaviorBase
{
public:

	AssetFilePathComponent ()          = default;
	~AssetFilePathComponent() override = default;

	void Init() override;

	void ImGuiComponentViewer() override {};
	void ImGuiComponentViewer(const char* Label);
	
	void           LoadPrefabData(const nlohmann::json& Json) override;
	nlohmann::json SavePrefabData()                           override;
	
	std::string_view GetAssetFilePath() const { return m_assetFilePath; }

	bool GetHasPathChanged() const { return m_hasPathChanged; }

private:

	std::string m_assetFilePath = "";

	bool m_hasPathChanged = false;
};