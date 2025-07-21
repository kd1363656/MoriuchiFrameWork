#include "StaticModelComponent.h"

#include "../../Transform/3D/Transform3DComponent.h"

#include "../../../Utility/BitShift/BitShiftUtility.h"

void StaticModelComponent::PostLoadInit()
{
	m_renderComponent.PostLoadInit();

	// もし"Json"データを読み込んだ際にファイルパスが何も読み込まれていなければ"return"
	if (m_renderComponent.GetAssetFilePath().empty())
	{
		return;
	}

	// フライトウェイトからモデルデータを取得
	m_modelData = KdAssets::Instance().m_modeldatas.GetData(m_renderComponent.GetAssetFilePath());
}

void StaticModelComponent::Draw(const RenderComponent::DrawType DrawType) const
{
	// 描画タイプが含まれていなければ何もしない
	if (!m_modelData || BitShiftUtility::HasFlag(DrawType, m_renderComponent.GetDrawType()))
	{
		return;
	}

	if(auto transform3DComponent_ = m_renderComponent.GetTransform3DComponent().lock())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData , transform3DComponent_->GetMatrix(), m_renderComponent.GetColor());
	}
}
void StaticModelComponent::Draw(const RenderComponent::ShaderType ShaderType) const
{
	if (!m_modelData || BitShiftUtility::HasFlag(ShaderType, m_renderComponent.GetShaderType()))
	{
		return;
	}

	if (auto transform3DComponent_ = m_renderComponent.GetTransform3DComponent().lock())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, transform3DComponent_->GetMatrix(), m_renderComponent.GetColor());
	}
}