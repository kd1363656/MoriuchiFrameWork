#include "AnimationModelComponent.h"

#include "../../../Transform/3D/Transform3DComponent.h"

#include "../../../../GameObject/GameObject.h"

#include "../../../../Utility/Json/JsonUtility.h"
#include "../../../../Utility/ImGui/ImGuiUtility.h"
#include "../../../../Utility/BitShift/BitShiftUtility.h"

void AnimationModelComponent::Init()
{
	m_modelData = nullptr;

	m_assetFilePathComponent.Init ();
	m_render3DCommonComponent.Init();
}
void AnimationModelComponent::PostLoadInit()
{  
	if(auto owner_ = GetOwner())
	{
		m_transform3DLinkerComponent.SetTransform3DComponent(owner_->GetComponent<Transform3DComponent>());
	}

	// "Json"が読み込まれた際にアセットのファイルパスが設定されていれば実行
	if(!m_modelData && !m_assetFilePathComponent.GetAssetFilePath().empty())
	{
		m_modelData = std::make_shared<KdModelWork>();
		m_modelData->SetModelData(m_assetFilePathComponent.GetAssetFilePath());
	}
}

void AnimationModelComponent::Draw(const Render3DCommonComponent::DrawType DrawType) const
{
	// 描画タイプが含まれていなければ何もしない
	if (!m_modelData || !BitShiftUtility::HasFlag(DrawType, m_render3DCommonComponent.GetDrawType()))
	{
		return;
	}

	if (auto transform3DComponent_ = m_transform3DLinkerComponent.GetTransform3DComponent())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, transform3DComponent_->GetMatrix(), m_render3DCommonComponent.GetColor());
	}
}
void AnimationModelComponent::Draw(const Render3DCommonComponent::ShaderType ShaderType) const
{
	if (!m_modelData || !BitShiftUtility::HasFlag(ShaderType, m_render3DCommonComponent.GetShaderType()))
	{
		return;
	}

	if (auto transform3DComponent_ = m_transform3DLinkerComponent.GetTransform3DComponent())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, transform3DComponent_->GetMatrix(), m_render3DCommonComponent.GetColor());
	}
}

void AnimationModelComponent::LoadPrefabData(const nlohmann::json& Json)
{
	if (Json.is_null()) { return; }

	if (Json.contains("AssetFilePathComponent" )) { m_assetFilePathComponent.LoadPrefabData (Json["AssetFilePathComponent" ]); }
	if (Json.contains("Render3DCommonComponent")) { m_render3DCommonComponent.LoadPrefabData(Json["Render3DCommonComponent"]); }
}
nlohmann::json AnimationModelComponent::SavePrefabData()
{
	auto json_ = nlohmann::json();

	json_["AssetFilePathComponent" ] = m_assetFilePathComponent.SavePrefabData ();
	json_["Render3DCommonComponent"] = m_render3DCommonComponent.SavePrefabData();

	return json_;
}

void AnimationModelComponent::ImGuiComponentViewer()
{
	m_render3DCommonComponent.ImGuiComponentViewer();
	m_assetFilePathComponent.ImGuiComponentViewer ("AnimationModelFilePath");

	if(m_assetFilePathComponent.GetHasPathChanged())
	{
		if (!m_modelData)
		{
			m_modelData = std::make_shared<KdModelWork>();
		}

		m_modelData->SetModelData(m_assetFilePathComponent.GetAssetFilePath());
	}
}