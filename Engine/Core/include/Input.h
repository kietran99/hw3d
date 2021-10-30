#pragma once

namespace RR
{
	enum class KeyCode
	{
		Back = 0x08,
		Tab = 0x09,
		Enter = 0x0D,
		Capital = 0x14,
		Escape = 0x1B,
		Space = 0x20, 
		PageUp, PageDown, 
		End, Home,
		Left, Up, Right, Down,
		Insert = 0x2D, 
		Delete,
		Alpha0 = 0x30, Alpha1, Alpha2, Alpha3, Alpha4, Alpha5, Alpha6, Alpha7, Alpha8, Alpha9,
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		Keypad0 = 0x60, Keypad1, Keypad2, Keypad3, Keypad4, Keypad5, Keypad6, Keypad7, Keypad8, Keypad9,
		KeypadMultiply, KeypadAdd, KeypadSubtract = 0x6D, KeypadDivide = 0x6f,
		F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
		LeftShift = 0xA0, RightShift, LeftControl, RightControl, LeftAlt, RightAlt,
		Invalid = 256
	};

	class Input
	{
		friend class Window;

		enum class ButtonState
		{
			Press,
			Release,
			Invalid
		};

		Input() noexcept;

	public:
		static bool GetKeyDown(KeyCode keyCode) noexcept;
		static bool GetKeyUp(KeyCode keyCode) noexcept;
		static bool GetKey(KeyCode keyCode) noexcept;

	private:
		void OnKeyPressed(unsigned __int64 keyCode) noexcept;
		void OnKeyReleased(unsigned __int64 keyCode) noexcept;
		void OnKeyHold(unsigned __int64 keyCode) noexcept;
		void Reset() noexcept;

	private:
		static Input* s_instance;

		KeyCode m_keyCode;
		ButtonState m_btnState;
		bool m_isBtnHold;
	};
}