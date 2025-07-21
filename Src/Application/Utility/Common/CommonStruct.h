#pragma once

namespace CommonStruct
{
	struct StringHash
	{
		using IsTransparent = void;

		size_t operator()(const std::string& Key) const { return std::hash<std::string>     {}(Key); }
		size_t operator()(std::string_view   Key) const { return std::hash<std::string_view>{}(Key); }
		size_t operator()(const char*        Key) const { return std::hash<std::string_view>{}(Key); }
	};

	struct BitShiftList
	{
		const char* label;
		uint32_t    type;
	};
}