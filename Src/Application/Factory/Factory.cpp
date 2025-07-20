#include "Factory.h"

#include "../GameObject/Camera/TPSCamera/TPSCamera.h"

#include "../Component/Transform/3D/Transform3DComponent.h"

void Factory::Init()
{
	RegisterGameObjectFactoryMethod();
}

void Factory::RegisterGameObjectFactoryMethod()
{
#ifdef _DEBUG
	KdDebugGUI::Instance().AddLog("============ Start register gameObject factory ============\n\n");
#endif // _DEBUG

	RegisterGameObjectFactoryMethod<Transform3DComponent>();

#ifdef _DEBUG
	KdDebugGUI::Instance().AddLog("\n============ End register gameObject factory ==============\n\n\n\n");
#endif // _DEBUG
}