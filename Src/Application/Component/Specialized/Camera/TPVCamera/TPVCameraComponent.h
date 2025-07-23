#pragma once
#include "../CameraCommonBehaviorComponent.h"

class TPVCameraComponent : public Component::OwnedBase
{
public:

	TPVCameraComponent ()          = default;
	~TPVCameraComponent() override = default;

	void Init     () override;

	void PreDraw();

	void PreUpdate() override;

private:

	CameraCommonBehaviorComponent m_cameraCommonBehaviorComponent;

};