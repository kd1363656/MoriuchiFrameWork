#pragma once

class Transform3DComponent;

class RenderComponent : public ComponentBase
{

public:

	enum class DrawType
	{
		Lit                       = 1 << 0 ,
		UnLit                     = 1 << 1 ,
		Effect                    = 1 << 2 ,
		Bright                    = 1 << 3 ,
		UI                        = 1 << 4 ,
		Sprite                    = 1 << 5 ,
		GenerateDepthFromMapLight = 1 << 6 ,
	};

	enum class ShaderType
	{
		AlphaDither = 1 << 0 ,
		Toon        = 1 << 1,
	};

	RenderComponent ()          = default;
	~RenderComponent() override = default;

	void PostLoadInit()override;

	void ImGuiComponentViewer() override;

	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<RenderComponent>(); }

	uint32_t GetDrawType  () const { return m_drawType;   }
	uint32_t GetShaderType() const { return m_shaderType; }

	std::weak_ptr<Transform3DComponent> GetTransform3DComponent() const { return m_transform3DComponent; }

	std::string_view GetAssetFilePath() const { return m_assetFilePath; }

	const Math::Color& GetColor() const { return m_color; }

private:

	std::string m_assetFilePath;

	Math::Color m_color = kWhiteColor;

	uint32_t m_drawType   = 0u;
	uint32_t m_shaderType = 0u;

	std::weak_ptr<Transform3DComponent> m_transform3DComponent;

};