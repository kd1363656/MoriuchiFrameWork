#include "AnimationModelComponent.h"

#include "../../../Transform/3D/Transform3DComponent.h"

#include "../../../../Utility/Json/JsonUtility.h"
#include "../../../../Utility/ImGui/ImGuiUtility.h"
#include "../../../../Utility/BitShift/BitShiftUtility.h"

void AnimationModelComponent::Init()
{
	m_modelData = nullptr;

	m_renderComponent.Init       ();
	m_assetFilePathComponent.Init();
}
void AnimationModelComponent::PostLoadInit()
{
	// "Json"が読み込まれた際にアセットのファイルパスが設定されていれば実行
	if(!m_modelData && !m_assetFilePathComponent.GetAssetFilePath().empty())
	{
		m_modelData = std::make_shared<KdModelWork>();
		m_modelData->SetModelData(m_assetFilePathComponent.GetAssetFilePath());
	}

	m_renderComponent.PostLoadInit();
}

void AnimationModelComponent::Draw(const Render3DComponent::DrawType DrawType) const
{
	// 描画タイプが含まれていなければ何もしない
	if (!m_modelData || !BitShiftUtility::HasFlag(DrawType, m_renderComponent.GetDrawType()))
	{
		return;
	}

	if (auto transform3DComponent_ = m_renderComponent.GetTransform3DComponent())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, transform3DComponent_->GetMatrix(), m_renderComponent.GetColor());
	}
}
void AnimationModelComponent::Draw(const Render3DComponent::ShaderType ShaderType) const
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

void AnimationModelComponent::LoadPrefabData(const nlohmann::json& Json)
{
	if (Json.is_null()) { return; }

	if (Json.contains("Render3DComponent"     )) { m_renderComponent.LoadPrefabData       (Json["Render3DComponent"     ]); }
	if (Json.contains("AssetFilePathComponent")) { m_assetFilePathComponent.LoadPrefabData(Json["AssetFilePathComponent"]); }
}
nlohmann::json AnimationModelComponent::SavePrefabData()
{
	auto json_ = nlohmann::json();

	json_["Render3DComponent"     ] = m_renderComponent.SavePrefabData       ();
	json_["AssetFilePathComponent"] = m_assetFilePathComponent.SavePrefabData();

	return json_;
}

void AnimationModelComponent::ImGuiComponentViewer()
{
	m_renderComponent.ImGuiComponentViewer       ();
	m_assetFilePathComponent.ImGuiComponentViewer("AnimationModelFilePath");

	if(m_assetFilePathComponent.GetHasPathChanged())
	{
		if (!m_modelData)
		{
			m_modelData = std::make_shared<KdModelWork>();
		}

		m_modelData->SetModelData(m_assetFilePathComponent.GetAssetFilePath());
	}
}