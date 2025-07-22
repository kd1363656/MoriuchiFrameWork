#pragma once

class Transform3DComponent;

// どのように描画、シェーダーを適用するかを決めるコンポーネント
class Render3DComponent : public ComponentBase
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

	Render3DComponent ()          = default;
	~Render3DComponent() override = default;

	void Init        () override;
	void PostLoadInit() override;

	void ImGuiComponentViewer() override;

	void           LoadPrefabData(const nlohmann::json& Json) override;
	nlohmann::json SavePrefabData()                           override;
	
	uint32_t GetTypeID() const override { return ComponentID::GetTypeID<Render3DComponent>(); }

	std::shared_ptr<Transform3DComponent> GetTransform3DComponent() const { return m_transform3DComponent.lock(); }

	const Math::Color& GetColor() const { return m_color; }

	uint32_t GetDrawType  () const { return m_drawType;   }
	uint32_t GetShaderType() const { return m_shaderType; }

private:

	std::weak_ptr<Transform3DComponent> m_transform3DComponent;

	Math::Color m_color = kWhiteColor;

	uint32_t m_drawType   = 0u;
	uint32_t m_shaderType = 0u;

};