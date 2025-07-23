#include "StaticModelComponent.h"

#include "../../../Transform/3D/Transform3DComponent.h"

#include "../../../../GameObject/GameObject.h"

#include "../../../../Utility/Json/JsonUtility.h"
#include "../../../../Utility/ImGui/ImGuiUtility.h"
#include "../../../../Utility/Common/CommonConstant.h"
#include "../../../../Utility/BitShift/BitShiftUtility.h"

void StaticModelComponent::Init()
{
	m_modelData = nullptr;
	
	m_render3DCommonBehaviorComponent.Init      ();
	m_assetFilePathCommonBehaviorComponent.Init ();
}
void StaticModelComponent::PostLoadInit()
{
	// 所有者のポインタをセット
	if(auto owner_ = GetOwner())
	{
		m_transform3DLinkerComponent.SetTransform3DComponent(owner_->GetComponent<Transform3DComponent>());
	}

	// "Json"が読み込まれた際にアセットのファイルパスが設定されていれば実行
	if (!m_modelData && !m_assetFilePathCommonBehaviorComponent.GetAssetFilePath().empty())
	{
		m_modelData = KdAssets::Instance().m_modeldatas.GetData(m_assetFilePathCommonBehaviorComponent.GetAssetFilePath());
	}
}

void StaticModelComponent::Draw(const Render3DCommonBehaviorComponent::DrawType DrawType) const
{
	// 描画タイプが含まれていなければ何もしない
	if (!m_modelData || !BitShiftUtility::HasFlag(DrawType, m_render3DCommonBehaviorComponent.GetDrawType()))
	{
		return;
	}

	if(auto transform3DComponent_ = m_transform3DLinkerComponent.GetTransform3DComponent())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData , transform3DComponent_->GetMatrix(), m_render3DCommonBehaviorComponent.GetColor());
	}
}
void StaticModelComponent::Draw(const Render3DCommonBehaviorComponent::ShaderType ShaderType) const
{
	if (!m_modelData || !BitShiftUtility::HasFlag(ShaderType, m_render3DCommonBehaviorComponent.GetShaderType()))
	{
		return;
	}

	if (auto transform3DComponent_ = m_transform3DLinkerComponent.GetTransform3DComponent())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, transform3DComponent_->GetMatrix(), m_render3DCommonBehaviorComponent.GetColor());
	}
}

void StaticModelComponent::LoadPrefabData(const nlohmann::json& Json)
{
	if (Json.is_null()) { return; }

	if (Json.contains("Render3DComponent"     )) { m_render3DCommonBehaviorComponent.LoadPrefabData(Json["Render3DComponent"     ]); }
	if (Json.contains("AssetFilePathComponent")) { m_assetFilePathCommonBehaviorComponent.LoadPrefabData (Json["AssetFilePathComponent"]); }
}
nlohmann::json StaticModelComponent::SavePrefabData()
{
	auto json_ = nlohmann::json();

	json_["Render3DComponent"     ] = m_render3DCommonBehaviorComponent.SavePrefabData();
	json_["AssetFilePathComponent"] = m_assetFilePathCommonBehaviorComponent.SavePrefabData ();

	return json_;
}

void StaticModelComponent::ImGuiPrefabInspector()
{
	m_render3DCommonBehaviorComponent.ImGuiPrefabInspector();
	m_assetFilePathCommonBehaviorComponent.ImGuiPrefabInspector ("StaticModelFilePath");

	// パスが変更されたら変更を適用
	if (m_assetFilePathCommonBehaviorComponent.GetHasPathChanged())
	{
		// フライトウェイトからモデルデータを取得
		m_modelData = KdAssets::Instance().m_modeldatas.GetData(m_assetFilePathCommonBehaviorComponent.GetAssetFilePath());
	}
}