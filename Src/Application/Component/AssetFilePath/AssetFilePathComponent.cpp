#include "AssetFilePathComponent.h"

#include ",,/../../../Utility/ImGui/ImGuiUtility.h"

void AssetFilePathComponent::Init()
{
	m_assetFilePath.clear();
	m_hasPathChanged = false;
}

void AssetFilePathComponent::ImGuiComponentViewer(const char* Label)
{
	// ファイルパスの変更を受け取る
	m_hasPathChanged = ImGuiUtility::SelectFolderPath(Label , m_assetFilePath);
}

void AssetFilePathComponent::LoadPrefabData(const nlohmann::json& Json)
{
	if (Json.is_null()) { return; }

	m_assetFilePath = Json.value("AssetFilePath" , "");
}
nlohmann::json AssetFilePathComponent::SavePrefabData()
{
	auto json_ = nlohmann::json();

	json_["AssetFilePath"] = m_assetFilePath;

	return json_;
}