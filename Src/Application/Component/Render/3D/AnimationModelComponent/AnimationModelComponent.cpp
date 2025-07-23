#include "AnimationModelComponent.h"

#include "../../../Transform/3D/Transform3DComponent.h"

#include "../../../../GameObject/GameObject.h"

#include "../../../../Utility/Json/JsonUtility.h"
#include "../../../../Utility/ImGui/ImGuiUtility.h"
#include "../../../../Utility/BitShift/BitShiftUtility.h"

void AnimationModelComponent::Init()
{
	m_modelData = nullptr;

	m_assetFilePathCommonBehaviorComponent.Init ();
	m_render3DCommonBehaviorComponent.Init      ();
}
void AnimationModelComponent::PostLoadInit()
{  
	if(auto owner_ = GetOwner())
	{
		m_transform3DLinkerComponent.SetTransform3DComponent(owner_->GetComponent<Transform3DComponent>());
	}

	// "Json"が読み込まれた際にアセットのファイルパスが設定されていれば実行
	if(!m_modelData && !m_assetFilePathCommonBehaviorComponent.GetAssetFilePath().empty())
	{
		m_modelData = std::make_shared<KdModelWork>();
		m_modelData->SetModelData(m_assetFilePathCommonBehaviorComponent.GetAssetFilePath());
	}
}

void AnimationModelComponent::Draw(const Render3DCommonBehaviorComponent::DrawType DrawType) const
{
	// 描画タイプが含まれていなければ何もしない
	if (!m_modelData || !BitShiftUtility::HasFlag(DrawType, m_render3DCommonBehaviorComponent.GetDrawType()))
	{
		return;
	}

	if (auto transform3DComponent_ = m_transform3DLinkerComponent.GetTransform3DComponent())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, transform3DComponent_->GetMatrix(), m_render3DCommonBehaviorComponent.GetColor());
	}
}
void AnimationModelComponent::Draw(const Render3DCommonBehaviorComponent::ShaderType ShaderType) const
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

void AnimationModelComponent::LoadPrefabData(const nlohmann::json& Json)
{
	if (Json.is_null()) { return; }

	if (Json.contains("AssetFilePathComponent" )) { m_assetFilePathCommonBehaviorComponent.LoadPrefabData (Json["AssetFilePathComponent" ]); }
	if (Json.contains("Render3DCommonComponent")) { m_render3DCommonBehaviorComponent.LoadPrefabData(Json["Render3DCommonComponent"]); }
}
nlohmann::json AnimationModelComponent::SavePrefabData()
{
	auto json_ = nlohmann::json();

	json_["AssetFilePathComponent" ] = m_assetFilePathCommonBehaviorComponent.SavePrefabData ();
	json_["Render3DCommonComponent"] = m_render3DCommonBehaviorComponent.SavePrefabData();

	return json_;
}

void AnimationModelComponent::ImGuiPrefabInspector()
{
	m_render3DCommonBehaviorComponent.ImGuiPrefabInspector();
	m_assetFilePathCommonBehaviorComponent.ImGuiPrefabInspector ("AnimationModelFilePath");

	if(m_assetFilePathCommonBehaviorComponent.GetHasPathChanged())
	{
		if (!m_modelData)
		{
			m_modelData = std::make_shared<KdModelWork>();
		}

		m_modelData->SetModelData(m_assetFilePathCommonBehaviorComponent.GetAssetFilePath());
	}
}