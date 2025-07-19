﻿#include "RawInputManager.h"

#include "../Src/Application/Scene/SceneManager.h"

#include "../Src/Application/main.h"

void RawInputManager::ResetKeyStates()
{
	std::lock_guard<std::mutex> lock_(m_inputMutex);
	for(auto& key_ : m_nowKeyStateList)
	{
		key_.second = false;
	}
}

void RawInputManager::RegisterDevice()
{
	// m_hWndがしっかりセットされていれば実行
	assert(m_hWnd != NULL);

	RAWINPUTDEVICE rid_[3];

	// デバイスの登録を行っていく
	// キーボード
	rid_[0].usUsagePage = 0x01;		//標準デバイス
	rid_[0].usUsage		= 0x06;		//キーボード
	rid_[0].dwFlags		= RIDEV_INPUTSINK;	
	rid_[0].hwndTarget  = m_hWnd;		

	// マウス
	rid_[1].usUsagePage = 0x01;
	rid_[1].usUsage		= 0x02;
	rid_[1].dwFlags     =RIDEV_INPUTSINK;
	rid_[1].hwndTarget  = m_hWnd;

	// ゲームパッド
	rid_[2].usUsagePage = 0x01;
	rid_[2].usUsage		= 0x05;
	rid_[2].dwFlags		= RIDEV_INPUTSINK;
	rid_[2].hwndTarget  = m_hWnd;

	if(!RegisterRawInputDevices(rid_ , 3 , sizeof(RAWINPUTDEVICE)))
	{
		// std::cerr << "周辺機器の登録に失敗" << std::endl;
	}
}

void RawInputManager::ProcessInput(LPARAM LParam)
{
	UINT dwSize_ = 0;
	GetRawInputData((HRAWINPUT)LParam , RID_INPUT , nullptr , &dwSize_ , sizeof(RAWINPUTHEADER));

	BYTE buffer_[1024];	//最大1024バイトまでの固定バッファにする

	if (dwSize_ == 0             )return;	//何もデータがないときはスキップ
	if (dwSize_ > sizeof(buffer_))return;

	if (GetRawInputData((HRAWINPUT)LParam, RID_INPUT, buffer_, &dwSize_, sizeof(RAWINPUTHEADER)) != dwSize_) { return; }
	
	RAWINPUT* raw_ = reinterpret_cast<RAWINPUT*>(buffer_);

	// キーボード
	if(raw_->header.dwType == RIM_TYPEKEYBOARD)
	{
		int  key_     = raw_->data.keyboard.VKey;
		bool pressed_ = !(raw_->data.keyboard.Flags & RI_KEY_BREAK);

		// キーの入力状態を格納
		// "insert_or_assign"はキーがなければキーと値を格納
		// 存在すればそのキーに対応する値を格納
		m_nowKeyStateList.insert_or_assign(key_ , pressed_);		

		if(m_keyboardCallback)
		{	
			std::lock_guard<std::mutex>lock_(m_inputMutex);
			m_keyboardCallback(key_ , pressed_);
		}
	}
	// マウス
	if(raw_->header.dwType == RIM_TYPEMOUSE)
	{
		POINT mousePos_;

		// マウスの座標(デスクトップ全体を対象)を取得
		if (GetCursorPos(&mousePos_))
		{
			// ScreenToClientでマウス座標(デスクトップ全体を対象)を
			// 今のゲームウィンドウ用に変換
			// 左上のを基準に座標を取るので調整する
			ScreenToClient(m_hWnd, &mousePos_);
			//m_nowMouseData.location.x =  static_cast<float>(mousePos_.x) - 640.0f;
			//m_nowMouseData.location.y = (static_cast<float>(mousePos_.y) - 360.0f) * -1.0f;
		}

		WORD flags_ = raw_->data.mouse.usButtonFlags;

		// ボタンの状態を明示的に管理（押下/解放で変更）
		// "RawInput"の仕様上効かない時があるから
		if      (flags_ & RI_MOUSE_MIDDLE_BUTTON_DOWN) m_nowMouseData.isClickMiddle = true;
		else if (flags_ & RI_MOUSE_MIDDLE_BUTTON_UP  ) m_nowMouseData.isClickMiddle = false;

		if      (flags_ & RI_MOUSE_LEFT_BUTTON_DOWN) m_nowMouseData.isClickLeft = true;
		else if (flags_ & RI_MOUSE_LEFT_BUTTON_UP  ) m_nowMouseData.isClickLeft = false;

		if      (flags_ & RI_MOUSE_RIGHT_BUTTON_DOWN) m_nowMouseData.isClickRight = true;
		else if (flags_ & RI_MOUSE_RIGHT_BUTTON_UP  ) m_nowMouseData.isClickRight = false;

		// ホイール
		if(flags_ & RI_MOUSE_WHEEL)
		{
			m_nowMouseData.wheelDelta = static_cast<SHORT>(raw_->data.mouse.usButtonData) / WHEEL_DELTA;
		}
		else
		{
			// 回転がない場合は0
			m_nowMouseData.wheelDelta = 0;
		}

		if(m_mouseCallback)
		{
			std::lock_guard<std::mutex> lock_(m_inputMutex);
			m_mouseCallback(m_nowMouseData);
		}
	}

	// ゲームパッド
	if(raw_->header.dwType == RIM_TYPEHID)
	{
		if(raw_->data.hid.dwSizeHid > 0)
		{
			BYTE* data_ = raw_->data.hid.bRawData;

			// ここでゲームパッドのボタン情報を読み取る
			bool buttonA_ = (data_[0] & 0x10) != 0;	//Aボタン仮判定

			if(m_gamepadCallback)
			{
				std::lock_guard<std::mutex> lock_(m_inputMutex);
				m_gamepadCallback(1, buttonA_);	//ボタンA(仮)

				// スティックX軸
				float x_ = (data_[1] - 128.0f) / 128.0f;	// -1.0f~1.0fに変換
				float y_ = (data_[2] - 128.0f) / 128.0f;	// スティックY軸

				// デッドゾーン(小さな揺れを無視する)
				const float deadZone_ = 0.1f;

				if (fabs(x_) < deadZone_) x_ = 0.0f;
				if (fabs(y_) < deadZone_) y_ = 0.0f;

				if(m_gamepadStickCallback) m_gamepadStickCallback(x_ , y_);
				
			}
		}
	}
}

void RawInputManager::Vibrate(float LeftMotor, float RightMotor, int Duration)
{
	XINPUT_VIBRATION vibration_ = {};
	vibration_.wLeftMotorSpeed  = static_cast<WORD>(LeftMotor  * 65535);
	vibration_.wRightMotorSpeed = static_cast<WORD>(RightMotor * 65535);

	// パッド0番(基本は1p)

	// 推定時間後に振動を停止
	Sleep(Duration);

	vibration_.wLeftMotorSpeed  = 0;
	vibration_.wRightMotorSpeed = 0;

	XInputSetState(0 , &vibration_);
}

void RawInputManager::BackUpInputState()
{
	// 現在のフレームでのキー情報を格納する
	for (const auto& [key_, value_] : m_nowKeyStateList)
	{
		m_oldKeyStateList.insert_or_assign(key_, value_);
	}

	m_oldMouseData = m_nowMouseData;
}