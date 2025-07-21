#include "Render3DComponent.h"

#include "../../Transform/3D/Transform3DComponent.h"

#include "../../../GameObject/GameObject.h"

#include "../../../Utility/Common/CommonStruct.h"
#include "../../../Utility/ImGui/ImGuiUtility.h"
#include "../../../Utility/Json/JsonUtility.h"

void Render3DComponent::PostLoadInit()
{
	auto owner_ = GetOwner().lock();

	if (owner_)
	{
		m_transform3DComponent = owner_->GetComponent<Transform3DComponent>();	
	}
}

void Render3DComponent::ImGuiComponentViewer()
{
	// "ImGui"用のリストのため"static"変数を定義
	static const std::vector<CommonStruct::BitShiftList> drawTypeList_ = 
	{
		{ "Lit"                       , static_cast<uint32_t>(DrawType::Lit)					   },
		{ "UnLit"                     , static_cast<uint32_t>(DrawType::UnLit)                     },
		{ "Effect"                    , static_cast<uint32_t>(DrawType::Effect)                    },
		{ "Bright"                    , static_cast<uint32_t>(DrawType::Bright)                    },
		{ "UI"                        , static_cast<uint32_t>(DrawType::UI)						   },
		{ "GenerateDepthFromMapLight" , static_cast<uint32_t>(DrawType::GenerateDepthFromMapLight) }
	};

	static const std::vector<CommonStruct::BitShiftList> shaderTypeList_ =
	{
		{ "AlphaDither" , static_cast<uint32_t>(ShaderType::AlphaDither) },
		{ "Toon"        , static_cast<uint32_t>(ShaderType::Toon)        }
	};

	ImGuiUtility::ImGuiBitShiftSelector("DrawType"   , m_drawType   , drawTypeList_  );
	ImGuiUtility::ImGuiBitShiftSelector("ShaderType" , m_shaderType , shaderTypeList_);
}

void Render3DComponent::LoadPrefabData(const nlohmann::json& Json)
{
	if (Json.is_null()) { return; }

	if (Json.contains("Color")) { m_color = JsonUtility::JsonToColor(Json["Color"]); }

	m_drawType   = Json.value("DrawType"   , 0u);
	m_shaderType = Json.value("ShaderType" , 0u);
}
nlohmann::json Render3DComponent::SavePrefabData()
{
	auto json_ = nlohmann::json();

	json_["Color"] = JsonUtility::ColorToJson(m_color);

	json_["DrawType"  ] = m_drawType;
	json_["ShaderType"] = m_shaderType;

	return json_;
}