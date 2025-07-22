#include "StaticModelComponent.h"

#include "../../../Transform/3D/Transform3DComponent.h"

#include "../../../../Utility/Json/JsonUtility.h"
#include "../../../../Utility/ImGui/ImGuiUtility.h"
#include "../../../../Utility/Common/CommonConstant.h"
#include "../../../../Utility/BitShift/BitShiftUtility.h"

void StaticModelComponent::Init()
{
	m_modelData     = nullptr;
	
	m_renderComponent.Init       ();
	m_assetFilePathComponent.Init();
}
void StaticModelComponent::PostLoadInit()
{
	// "Json"が読み込まれた際にアセットのファイルパスが設定されていれば実行
	if (!m_modelData && !m_assetFilePathComponent.GetAssetFilePath().empty())
	{
		m_modelData = KdAssets::Instance().m_modeldatas.GetData(m_assetFilePathComponent.GetAssetFilePath());
	}

	m_renderComponent.PostLoadInit();
}

void StaticModelComponent::Draw(const Render3DComponent::DrawType DrawType) const
{
	// 描画タイプが含まれていなければ何もしない
	if (!m_modelData || !BitShiftUtility::HasFlag(DrawType, m_renderComponent.GetDrawType()))
	{
		return;
	}

	if(auto transform3DComponent_ = m_renderComponent.GetTransform3DComponent())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData , transform3DComponent_->GetMatrix(), m_renderComponent.GetColor());
	}
}
void StaticModelComponent::Draw(const Render3DComponent::ShaderType ShaderType) const
{
	if (!m_modelData || !BitShiftUtility::HasFlag(ShaderType, m_renderComponent.GetShaderType()))
	{
		return;
	}

	if (auto transform3DComponent_ = m_renderComponent.GetTransform3DComponent())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, transform3DComponent_->GetMatrix(), m_renderComponent.GetColor());
	}
}

void StaticModelComponent::LoadPrefabData(const nlohmann::json& Json)
{
	if (Json.is_null()) { return; }

	if (Json.contains("Render3DComponent"     )) { m_renderComponent.LoadPrefabData       (Json["Render3DComponent"     ]); }
	if (Json.contains("AssetFilePathComponent")) { m_assetFilePathComponent.LoadPrefabData(Json["AssetFilePathComponent"]); }
}
nlohmann::json StaticModelComponent::SavePrefabData()
{
	auto json_ = nlohmann::json();

	json_["Render3DComponent"     ] = m_renderComponent.SavePrefabData       ();
	json_["AssetFilePathComponent"] = m_assetFilePathComponent.SavePrefabData();

	return json_;
}

void StaticModelComponent::ImGuiComponentViewer()
{
	m_renderComponent.ImGuiComponentViewer       ();
	m_assetFilePathComponent.ImGuiComponentViewer("StaticModelFilePath");

	// パスが変更されたら変更を適用
	if (m_assetFilePathComponent.GetHasPathChanged())
	{
		// フライトウェイトからモデルデータを取得
		m_modelData = KdAssets::Instance().m_modeldatas.GetData(m_assetFilePathComponent.GetAssetFilePath());
	}
}