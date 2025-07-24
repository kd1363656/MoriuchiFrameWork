#include "ImGuiManager.h"

#include "../../Application/GameObject/GameObject.h"

#include "../../Application/Scene/BaseScene/BaseScene.h"
#include "../../Application/Scene/SceneManager.h"

#include "../../Application/Factory/Factory.h"

void ImGuiManager::Init()
{
	m_selectedComponentName = "None";
}

void ImGuiManager::Update()
{
	UpdateHierarchyWindow();
	UpdateInspectorWindow();
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
			ImGui::PushID   (gameObject_.get());
			ImGui::Separator();

			std::string typeName_ = gameObject_->GetTypeName().data();
			
			const bool isSelected_ = gameObject_ == m_inspectorWindowTargetGameObject.lock();

			// カラム開始(2列
			ImGui::Columns(2, nullptr, false);
			ImGui::SetColumnWidth(0 , 180);	// ラベルの幅

			// 左列 : "Selectable"(名前クリック)
			// もしクリックされたらクリックされたオブジェクト名を持つゲームオブジェクトの
			// インスペクターを表示する
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
			ImGui::PopID    ();
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

// コンポーネントの中身を操作したり、コンポーネントを追加したりする関数
void ImGuiManager::UpdateInspectorWindow()
{
	auto scene_ = SceneManager::GetInstance().GetCurrentScene().lock();
	
	if (!scene_) { return; }

	if (ImGui::Begin("Inspector"))
	{
		if (auto gameObject_ = m_inspectorWindowTargetGameObject.lock())
		{
			UpdateAddComponentSelector(gameObject_);
			UpdateAddComponentButton  (gameObject_);
			UpdateComponentInspector  (gameObject_);
		}
	}
	ImGui::End();
}

void ImGuiManager::UpdateComponentInspector(std::shared_ptr<GameObject> GameObject) const
{
	if (!GameObject) { return; }

	for (const auto& [key_, value_] : GameObject->GetComponentList())
	{
		ImGui::PushID(value_.get());
		ImGui::Separator();

		// コンポーネント内にあるインスペクターを表示
		if (ImGui::TreeNodeEx(value_->GetTypeName().data(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::SameLine(212.0f , 0.0f);

			if (ImGui::SmallButton("Delete"))
			{
				value_->SetIsDeleteRequested(true);
			}

			value_->ImGuiSpawnInspector ();
			// あとでプレハブ用の関数を作る
			value_->ImGuiPrefabInspector();
			ImGui::TreePop();
		}
		
		ImGui::PopID();
		ImGui::Separator();
	}
}
void ImGuiManager::UpdateAddComponentSelector(std::shared_ptr<GameObject> GameObject)
{
	if (!GameObject) { return; }

	auto& factory_ = Factory::GetInstance();

	ImGui::PushID(&factory_.GetComponentFactoryMethodList());

	if (ImGui::BeginCombo("##ComponentType", m_selectedComponentName.c_str()))
	{
		for (const auto& [key_, value_] : factory_.GetComponentFactoryMethodList())
		{
			bool isSelected_ = (m_selectedComponentName == key_);

			if (ImGui::Selectable(key_.c_str(), &isSelected_))
			{
				m_selectedComponentName = key_;
			}

			// 選択されていたら反映
			if (isSelected_)
			{
				// コンボボックスを開いたとき、キーボード操作（↑↓）で選択を開始できるように、
				// 現在選択されている項目に初期フォーカスを設定する
				ImGui::SetItemDefaultFocus();
			}

		}

		ImGui::EndCombo();
	}

	ImGui::PopID();
}
void ImGuiManager::UpdateAddComponentButton(std::shared_ptr<GameObject> GameObject) const
{
	if (!GameObject) { return; }

	auto& factory_ = Factory::GetInstance();

	ImGui::SameLine(250.0f, 0.0f);

	if (ImGui::Button("Add Component"))
	{
		factory_.AttachComponent(GameObject , m_selectedComponentName);
	}
}