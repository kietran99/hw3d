#include "Input.h"

RR::Input *RR::Input::s_instance = new RR::Input();

RR::Input::Input() noexcept
	: m_keyCode(KeyCode::Invalid)
	, m_btnState(ButtonState::Invalid)
	, m_isBtnHold(false)
{}

bool RR::Input::GetKeyDown(KeyCode keyCode) noexcept
{
	return !s_instance->m_isBtnHold && s_instance->m_keyCode == keyCode && s_instance->m_btnState == ButtonState::Press;
}

bool RR::Input::GetKeyUp(KeyCode keyCode) noexcept
{
	return s_instance->m_keyCode == keyCode && s_instance->m_btnState == ButtonState::Release;
}

bool RR::Input::GetKey(KeyCode keyCode) noexcept
{
	return s_instance->m_isBtnHold && s_instance->m_keyCode == keyCode && s_instance->m_btnState == ButtonState::Press;
}

void RR::Input::OnKeyPressed(unsigned __int64 keyCode) noexcept
{
	m_isBtnHold = false;
	m_keyCode = static_cast<KeyCode>(keyCode);
	m_btnState = ButtonState::Press;
}

void RR::Input::OnKeyReleased(unsigned __int64 keyCode) noexcept
{
	m_isBtnHold = false;
	m_keyCode = static_cast<KeyCode>(keyCode);
	m_btnState = ButtonState::Release;
}

void RR::Input::OnKeyHold(unsigned __int64 keyCode) noexcept
{
	m_isBtnHold = true;
	m_keyCode = static_cast<KeyCode>(keyCode);
	m_btnState = ButtonState::Press;
}

void RR::Input::Reset() noexcept
{
	m_keyCode = KeyCode::Invalid;
	m_btnState = ButtonState::Invalid;
}