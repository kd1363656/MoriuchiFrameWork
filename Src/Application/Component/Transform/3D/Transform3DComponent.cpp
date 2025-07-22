#include "Transform3DComponent.h"

#include "../../../Utility/Common/CommonConstant.h"

#include "../../../../System/Calculation/Calculation.h"
#include "../../../Utility/Json/JsonUtility.h"

void Transform3DComponent::Init()
{
	m_position = Math::Vector3::Zero;
	m_rotation = Math::Quaternion::Identity;
	m_scale    = Math::Vector3::Zero;

	m_matrix = Math::Matrix::Identity;
}

void Transform3DComponent::PreUpdate()
{
	// 座標の確定は"Update,PostUpdate"で座標、回転の更新が行われてから
	// 更新するため"PreUpdate"で更新
	const Math::Matrix transMat_    = Math::Matrix::CreateTranslation   (m_position);
	const Math::Matrix rotationMat_ = Math::Matrix::CreateFromQuaternion(m_rotation);
	const Math::Matrix scaleMat_    = Math::Matrix::CreateScale         (m_scale   );

	m_matrix = scaleMat_ * rotationMat_ * transMat_;
}

void Transform3DComponent::ImGuiComponentViewer()
{
	Math::Vector3 radian_ = Math::Vector3::Zero;

	// クオータニオンをオイラー角に変換
	Calculation::QuaternionToEuler(m_rotation, radian_);

	ImGui::DragFloat3("Position", &m_position.x, 0.1f															  );
	ImGui::DragFloat3("Rotation", &radian_.x   , 1.0f, -CommonConstant::HALF_DEGREE , CommonConstant::HALF_DEGREE );
	ImGui::DragFloat3("Scale"   , &m_scale.x   , 0.1f														      );

	// 変換したオイラー角の結果をクオータニオンに変換
	Calculation::EulerToQuaternion(radian_ , m_rotation);
}

void Transform3DComponent::Deserialize(const nlohmann::json& Json)
{
	if(Json.is_null()) { return; }

	if (Json.contains("Position")) { m_position = JsonUtility::JsonToVec3      (Json["Position"]); }
	if (Json.contains("Rotation")) { m_rotation = JsonUtility::JsonToQuaternion(Json["Rotation"]); }
	if (Json.contains("Scale"   )) { m_scale    = JsonUtility::JsonToVec3      (Json["Scale"   ]); }
}
nlohmann::json Transform3DComponent::Serialize()
{
	auto json_ = nlohmann::json();
	
	json_["Position"] = JsonUtility::Vec3ToJson      (m_position);
	json_["Rotation"] = JsonUtility::QuaternionToJson(m_rotation);
	json_["Scale"   ] = JsonUtility::Vec3ToJson      (m_scale   );
	
	return json_;
}