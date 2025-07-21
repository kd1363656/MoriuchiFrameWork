#pragma once

enum class TPSCameraStateFlag;

namespace BitShiftUtility
{
	// "std::is_enum_v<EnumType>"は"Enum"型かどうかを評価する
	template <typename EnumType>
	constexpr bool IsValidEnumFlag = std::is_enum_v<EnumType>;

	// コピー渡しのほうが速度が早いが式を
	// 間違って使うリスクを減らすため参照で"uint32_t"を取得
	template <typename EnumType>
	void EnableFlag(EnumType FlagToEnable, uint32_t& Flags)
	{
		static_assert(IsValidEnumFlag<EnumType>, "BitShiftUtilityでエラーが出ました、必ずEnum型にしてください");
		const uint32_t flag_ = static_cast<uint32_t>(FlagToEnable);

		Flags |= flag_;
	}

	template <typename EnumType>
	void DisableFlag(EnumType FlagToDisable , uint32_t& Flags)
	{
		static_assert(IsValidEnumFlag<EnumType>, "BitShiftUtilityでエラーが出ました、必ずEnum型にしてください");
		const uint32_t flag_ = static_cast<uint32_t>(FlagToDisable);

		Flags &= ~flag_;
	}

	template <typename EnumType>
	bool HasFlag(EnumType FlagToCheck , uint32_t Flags)
	{
		static_assert(IsValidEnumFlag<EnumType>, "BitShiftUtilityでエラーが出ました、必ずEnum型にしてください");
		const uint32_t flag_ = static_cast<uint32_t>(FlagToCheck);

		// フラグが立っていたら"true"を返す
		return (Flags & flag_) != 0;
	}
}