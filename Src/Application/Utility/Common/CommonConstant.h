#pragma once

namespace CommonConstant
{
	static const char* const ASSET_FOLDER_PATH = "Asset/";

	static constexpr float LERP_EPSILON = 0.0001f;

	static constexpr float DOT_PRODUCT_MIN = -1.0f;
	static constexpr float DOT_PRODUCT_MAX =  1.0f;

	static constexpr float EASING_MAX_TIME = 1.0f;

	static constexpr float ALL_DEGREE  = 360.0f;
	static constexpr float HALF_DEGREE = 180.0f;

	static constexpr float MAX_SCREEN_WIDTH   = 1280.0f;
	static constexpr float MAX_SCREEN_HEIGHT  = 720.0f;
	static constexpr float HALF_SCREEN_WIDTH  = MAX_SCREEN_WIDTH  / 2.0f;
	static constexpr float HALF_SCREEN_HEIGHT = MAX_SCREEN_HEIGHT / 2.0f;

	static constexpr float GRAVITATIONAL_ACCELERATION = 9.8f;
}