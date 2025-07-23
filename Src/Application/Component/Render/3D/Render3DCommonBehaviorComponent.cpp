#include "Render3DCommonBehaviorComponent.h"

#include "../../Transform/3D/Transform3DComponent.h"

#include "../../../GameObject/GameObject.h"

#include "../../../Utility/Common/CommonStruct.h"
#include "../../../Utility/ImGui/ImGuiUtility.h"
#include "../../../Utility/Json/JsonUtility.h"

void Render3DCommonBehaviorComponent::Init()
{
	m_color = kWhiteColor;

	m_drawType   = 0u;
	m_shaderType = 0u;
}

void Render3DCommonBehaviorComponent::ImGuiPrefabInspector()
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

	ImGuiUtility::BitShiftSelector("DrawType"   , m_drawType   , drawTypeList_  );
	ImGuiUtility::BitShiftSelector("ShaderType" , m_shaderType , shaderTypeList_);
}

void Render3DCommonBehaviorComponent::LoadPrefabData(const nlohmann::json& Json)
{
	if (Json.is_null()) { return; }

	if (Json.contains("Color")) { m_color = JsonUtility::JsonToColor(Json["Color"]); }

	m_drawType   = Json.value("DrawType"   , 0u);
	m_shaderType = Json.value("ShaderType" , 0u);
}
nlohmann::json Render3DCommonBehaviorComponent::SavePrefabData()
{
	auto json_ = nlohmann::json();

	json_["Color"] = JsonUtility::ColorToJson(m_color);

	json_["DrawType"  ] = m_drawType;
	json_["ShaderType"] = m_shaderType;

	return json_;
}