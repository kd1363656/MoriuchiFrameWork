#pragma once

class GameObject;

class Component
{

public:

	Component         () = default;
	virtual ~Component() = default;

	class OwnedBase;
	class CommonBehaviorBase;
	
};