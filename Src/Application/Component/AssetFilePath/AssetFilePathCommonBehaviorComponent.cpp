#include "AssetFilePathCommonBehaviorComponent.h"

#include ",,/../../../Utility/ImGui/ImGuiUtility.h"

void AssetFilePathCommonBehaviorComponent::Init()
{
	m_assetFilePath.clear();
	m_hasPathChanged = false;
}

void AssetFilePathCommonBehaviorComponent::ImGuiPrefabInspector(const char* Label)
{
	// ファイルパスの変更を受け取る
	m_hasPathChanged = ImGuiUtility::SelectFolderPath(Label , m_assetFilePath);
}

void AssetFilePathCommonBehaviorComponent::LoadPrefabData(const nlohmann::json& Json)
{
	if (Json.is_null()) { return; }

	m_assetFilePath = Json.value("AssetFilePath" , "");
}
nlohmann::json AssetFilePathCommonBehaviorComponent::SavePrefabData()
{
	auto json_ = nlohmann::json();

	json_["AssetFilePath"] = m_assetFilePath;

	return json_;
}