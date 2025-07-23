#include "BaseScene.h"

#include "../../GameObject/GameObject.h"

#include "../../Component/Render/3D/StaticModelComponent/StaticModelComponent.h"
#include "../../Component/Render/3D/AnimationModelComponent/AnimationModelComponent.h"

#include "../../Component/Render/3D/Render3DCommonBehaviorComponent.h"

void BaseScene::PreUpdate()
{
	auto itr_ = m_gameObjectList.begin();

	// 削除依頼のあるゲームオブジェクトを削除
	while (itr_ != m_gameObjectList.end())
	{
		if ((*itr_)->GetIsDeleteRequested())
		{
			itr_ = m_gameObjectList.erase(itr_);
		}
		else
		{
			++itr_;
		}
	}

	for (const auto& gameObject_ : m_gameObjectList)
	{
		gameObject_->PreUpdate();
	}
}

void BaseScene::Update()
{
	// シーン毎のイベント処理
	Event();

	// KdGameObjectを継承した全てのオブジェクトの更新 (ポリモーフィズム)
	for (const auto& gameObject_ : m_gameObjectList)
	{
		gameObject_->Update();
	}
}

void BaseScene::PostUpdate()
{
	for (const auto& gameObject_ : m_gameObjectList)
	{
		gameObject_->PostUpdate();
	}
}

// カメラを描画するために必要
void BaseScene::PreDraw()
{
	//for (const auto& gameObject_ : m_gameObjectList)
	//{
	//	gameObject_->PreUpdate();
	//}
}

void BaseScene::Draw()
{
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 光を遮るオブジェクト(不透明な物体や2Dキャラ)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_StandardShader.BeginGenerateDepthMapFromLight();
	{
		for (const auto& obj_ : m_gameObjectList)
		{
			if(auto render_ = obj_->GetComponent<StaticModelComponent>().lock())
			{
				render_->Draw(Render3DCommonBehaviorComponent::DrawType::GenerateDepthFromMapLight);
			}

			if(auto render_ = obj_->GetComponent<AnimationModelComponent>().lock())
			{
				render_->Draw(Render3DCommonBehaviorComponent::DrawType::GenerateDepthFromMapLight);
			}
		}
	}
	KdShaderManager::Instance().m_StandardShader.EndGenerateDepthMapFromLight();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影のないオブジェクト(背景など)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_StandardShader.BeginUnLit();
	{
		for (const auto& obj : m_gameObjectList)
		{
			if (auto render_ = obj->GetComponent<StaticModelComponent>().lock())
			{
				render_->Draw(Render3DCommonBehaviorComponent::DrawType::UnLit);
			}

			if (auto render_ = obj->GetComponent<AnimationModelComponent>().lock())
			{
				render_->Draw(Render3DCommonBehaviorComponent::DrawType::UnLit);
			}
		}
	}
	KdShaderManager::Instance().m_StandardShader.EndUnLit();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影のあるオブジェクト(不透明な物体や2Dキャラ)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_StandardShader.BeginLit();
	{
		for (const auto& obj : m_gameObjectList)
		{
			if (auto render_ = obj->GetComponent<StaticModelComponent>().lock())
			{
				render_->Draw(Render3DCommonBehaviorComponent::DrawType::Lit);
			}

			if (auto render_ = obj->GetComponent<AnimationModelComponent>().lock())
			{
				render_->Draw(Render3DCommonBehaviorComponent::DrawType::Lit);
			}
		}
	}
	KdShaderManager::Instance().m_StandardShader.EndLit();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影のないオブジェクト(エフェクトなど)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_StandardShader.BeginUnLit();
	{
		for (const auto& obj : m_gameObjectList)
		{
			if (auto render_ = obj->GetComponent<StaticModelComponent>().lock())
			{
				render_->Draw(Render3DCommonBehaviorComponent::DrawType::Effect);
			}

			if (auto render_ = obj->GetComponent<AnimationModelComponent>().lock())
			{
				render_->Draw(Render3DCommonBehaviorComponent::DrawType::Effect);
			}
		}
	}
	KdShaderManager::Instance().m_StandardShader.EndUnLit();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 光源オブジェクト(自ら光るオブジェクトやエフェクト)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_postProcessShader.BeginBright();
	{
		for (const auto& obj : m_gameObjectList)
		{
			if (auto render_ = obj->GetComponent<StaticModelComponent>().lock())
			{
				render_->Draw(Render3DCommonBehaviorComponent::DrawType::Bright);
			}

			if (auto render_ = obj->GetComponent<AnimationModelComponent>().lock())
			{
				render_->Draw(Render3DCommonBehaviorComponent::DrawType::Bright);
			}
		}
	}
	KdShaderManager::Instance().m_postProcessShader.EndBright();
}

void BaseScene::DrawSprite()
{
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 2Dの描画はこの間で行う
	KdShaderManager::Instance().m_spriteShader.Begin();
	{

	}
	KdShaderManager::Instance().m_spriteShader.End();
}

void BaseScene::DrawDebug()
{
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// デバッグ情報の描画はこの間で行う
	KdShaderManager::Instance().m_StandardShader.BeginUnLit();
	{
		for (auto& obj : m_gameObjectList)
		{
			//obj->DrawDebug();
		}
	}
	KdShaderManager::Instance().m_StandardShader.EndUnLit();
}

void BaseScene::Event()
{
	// 各シーンで必要な内容を実装(オーバーライド)する
}

void BaseScene::Init()
{
	// 各シーンで必要な内容を実装(オーバーライド)する
}
