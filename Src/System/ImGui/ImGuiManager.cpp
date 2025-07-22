#include "ImGuiManager.h"

#include "../../Application/GameObject/GameObject.h"

#include "../../Application/Scene/BaseScene/BaseScene.h"
#include "../../Application/Scene/SceneManager.h"

#include "../../Application/Factory/Factory.h"

void ImGuiManager::Init()
{
	m_popUpFlag = 0u;

}

void ImGuiManager::Update()
{
	UpdateHierarchyWindow();
}

void ImGuiManager::UpdateHierarchyWindow()
{
	auto scene_ = SceneManager::GetInstance().GetCurrentScene().lock();

	if (!scene_) { return; }

	// どうゆうオブジェクトが生成されたかを
	if (ImGui::Begin("Hierarchy"))
	{
		UpdateAddGameObjectButton();

		for (const auto& gameObject_ : scene_->GetGameObjectList())
		{
			ImGui::PushID(gameObject_.get());
			ImGui::Separator();

			std::string typeName_ = gameObject_->GetTypeName().data();
			
			const bool isSelected_ = gameObject_ == m_inspectorWindowTargetGameObject.lock();

			// もしクリックされたらクリックされたオブジェクト名を持つゲームオブジェクトの
			// インスペクターを表示する

			// カラム開始(2列
			ImGui::Columns(2, nullptr, false);
			ImGui::SetColumnWidth(0 , 180);	// ラベルの幅

			// 左列 : "Selectable"(名前クリック)
			if (ImGui::Selectable(typeName_.c_str() , isSelected_))
			{
				m_inspectorWindowTargetGameObject = gameObject_;
			}

			ImGui::NextColumn();	// 右列へ
			
			// 右列 : "Delete"ボタン
			if (ImGui::SmallButton("Delete"))
			{
				gameObject_->SetIsDeleteRequested(true);
			}

			// カラムの終了
			ImGui::Columns(1);

			ImGui::Separator();
			ImGui::PopID();
		}
	}
	ImGui::End();
}

void ImGuiManager::UpdateAddGameObjectButton() const
{
	auto  scene_ = SceneManager::GetInstance().GetCurrentScene().lock();

	if (!scene_) { return; }

	if (ImGui::Button("Add GameObject"))
	{
		auto gameObject_ = Factory::GetInstance().CreateGameObject();
		gameObject_->Init();

		if (!gameObject_) { return; }

		scene_->AddGameObject(gameObject_);
	}
}