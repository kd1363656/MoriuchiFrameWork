#pragma once

// どのように描画、シェーダーを適用するかを決めるコンポーネント
class Render3DCommonComponent : public Component::CommonBehaviorBase
{

public:

	enum class DrawType
	{
		Lit                       = 1 << 0 ,
		UnLit                     = 1 << 1 ,
		Effect                    = 1 << 2 ,
		Bright                    = 1 << 3 ,
		UI                        = 1 << 4 ,
		GenerateDepthFromMapLight = 1 << 5 ,
	};

	enum class ShaderType
	{
		AlphaDither = 1 << 0 ,
		Toon        = 1 << 1 ,
	};

	Render3DCommonComponent ()          = default;
	~Render3DCommonComponent() override = default;

	void Init() override;
	
	void ImGuiComponentViewer() override;

	void           LoadPrefabData(const nlohmann::json& Json) override;
	nlohmann::json SavePrefabData()                           override;

	const Math::Color& GetColor() const { return m_color; }

	uint32_t GetDrawType  () const { return m_drawType;   }
	uint32_t GetShaderType() const { return m_shaderType; }

private:

	Math::Color m_color = kWhiteColor;

	uint32_t m_drawType   = 0u;
	uint32_t m_shaderType = 0u;

};