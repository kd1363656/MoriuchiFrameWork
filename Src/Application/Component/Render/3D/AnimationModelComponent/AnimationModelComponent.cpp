#include "AnimationModelComponent.h"

#include "../../../Transform/3D/Transform3DComponent.h"

#include "../../../../Utility/Json/JsonUtility.h"
#include "../../../../Utility/ImGui/ImGuiUtility.h"
#include "../../../../Utility/BitShift/BitShiftUtility.h"

void AnimationModelComponent::PostLoadInit()
{
	m_renderComponent.PostLoadInit();

	// もし"Json"データを読み込んだ際にファイルパスが何も読み込まれていなければ"return"
	if (m_assetFilePath.empty())
	{
		return;
	}

	if(!m_modelData)
	{
		m_modelData = std::make_shared<KdModelWork>();
		m_modelData->SetModelData(m_assetFilePath);
	}
}

void AnimationModelComponent::Draw(const Render3DComponent::DrawType DrawType) const
{
	// 描画タイプが含まれていなければ何もしない
	if (!m_modelData || !BitShiftUtility::HasFlag(DrawType, m_renderComponent.GetDrawType()))
	{
		return;
	}

	if (auto transform3DComponent_ = m_renderComponent.GetTransform3DComponent().lock())
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

	if (auto transform3DComponent_ = m_renderComponent.GetTransform3DComponent().lock())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, transform3DComponent_->GetMatrix(), m_renderComponent.GetColor());
	}
}

void AnimationModelComponent::LoadPrefabData(const nlohmann::json& Json)
{
	if (Json.is_null()) { return; }

	m_assetFilePath = Json.value("AssetFilePath", "");

	if (Json.contains("Render3DComponent")) { m_renderComponent.LoadPrefabData(Json["Render3DComponent"]); }
}
nlohmann::json AnimationModelComponent::SavePrefabData()
{
	auto json_ = nlohmann::json();

	json_["AssetFilePath"    ] = m_assetFilePath;
	json_["Render3DComponent"] = m_renderComponent.SavePrefabData();

	return json_;
}

void AnimationModelComponent::ImGuiComponentViewer()
{
	if (ImGuiUtility::ImGuiSelectFolderPath(m_assetFilePath))
	{
		// フライトウェイトからモデルデータを取得
		if (!m_modelData)
		{
			m_modelData = std::make_shared<KdModelWork>();
		}

		m_modelData->SetModelData(m_assetFilePath);
	}

	m_renderComponent.ImGuiComponentViewer();
}