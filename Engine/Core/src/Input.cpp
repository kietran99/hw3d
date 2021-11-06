#include "Input.h"

#include <utility>

RR::Input *RR::Input::s_instance = new RR::Input();

RR::Input::Input() noexcept
	: m_keyCode(KeyCode::Invalid)
	, m_keyBtnState(ButtonState::Invalid)
	, m_isBtnHold(false)
	, m_mouseX(0)
	, m_mouseY(0)
	, m_mouseBtn(0)
	, m_mouseBtnState(ButtonState::Invalid)
{}

bool RR::Input::GetKeyDown(KeyCode keyCode) noexcept
{
	return !s_instance->m_isBtnHold && s_instance->m_keyCode == keyCode && s_instance->m_keyBtnState == ButtonState::Press;
}

bool RR::Input::GetKeyUp(KeyCode keyCode) noexcept
{
	return s_instance->m_keyCode == keyCode && s_instance->m_keyBtnState == ButtonState::Release;
}

bool RR::Input::GetKey(KeyCode keyCode) noexcept
{
	return s_instance->m_isBtnHold && s_instance->m_keyCode == keyCode && s_instance->m_keyBtnState == ButtonState::Press;
}

void RR::Input::OnKeyPressed(unsigned __int64 keyCode) noexcept
{
	m_isBtnHold = false;
	m_keyCode = static_cast<KeyCode>(keyCode);
	m_keyBtnState = ButtonState::Press;
}

void RR::Input::OnKeyReleased(unsigned __int64 keyCode) noexcept
{
	m_isBtnHold = false;
	m_keyCode = static_cast<KeyCode>(keyCode);
	m_keyBtnState = ButtonState::Release;
}

void RR::Input::OnKeyHold(unsigned __int64 keyCode) noexcept
{
	m_isBtnHold = true;
	m_keyCode = static_cast<KeyCode>(keyCode);
	m_keyBtnState = ButtonState::Press;
}

std::pair<int, int> RR::Input::GetMousePosition() noexcept
{
	return { s_instance->m_mouseX, s_instance->m_mouseY };
}

bool RR::Input::GetMouseButtonDown(int button) noexcept
{
	return s_instance->m_mouseBtn == button && s_instance->m_mouseBtnState == ButtonState::Press;
}

bool RR::Input::GetMouseButtonUp(int button) noexcept
{
	return s_instance->m_mouseBtn == button && s_instance->m_mouseBtnState == ButtonState::Release;
}

void RR::Input::OnMouseMove(int x, int y) noexcept
{
	m_mouseX = x;
	m_mouseY = y;
}

void RR::Input::OnMouseButtonDown(int button) noexcept
{
	m_mouseBtn = button;
	m_mouseBtnState = ButtonState::Press;
}

void RR::Input::OnMouseButtonUp(int button) noexcept
{
	m_mouseBtn = button;
	m_mouseBtnState = ButtonState::Release;
}

void RR::Input::Reset() noexcept
{
	m_keyCode = KeyCode::Invalid;
	m_keyBtnState = ButtonState::Invalid;
	m_mouseBtnState = ButtonState::Invalid;
}
