#pragma once

namespace Calculation
{

	// クオータニオンからオイラー角(度)に戻す
	inline void          QuaternionToEuler(const Math::Quaternion& Quaternion , Math::Vector3& ConvertedValue)
	{
		Math::Vector3 radian_ = Quaternion.ToEuler();

		ConvertedValue = Math::Vector3
		(
			DirectX::XMConvertToDegrees(radian_.x),
			DirectX::XMConvertToDegrees(radian_.y),
			DirectX::XMConvertToDegrees(radian_.z)
		);
	}
	
	// オイラー角(度)からクオータニオンに変換
	inline void EulerToQuaternion(const Math::Vector3& Euler , Math::Quaternion& Quaternion)
	{
		Quaternion = Math::Quaternion::CreateFromYawPitchRoll
		(
			DirectX::XMConvertToRadians(Euler.y) ,
			DirectX::XMConvertToRadians(Euler.x) ,
			DirectX::XMConvertToRadians(Euler.z) 
		);
	}

}