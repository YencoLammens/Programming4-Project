#include "Controller.h"

#ifndef __EMSCRIPTEN__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

namespace dae
{
	class Controller::ControllerImpl
	{
	public:
		explicit ControllerImpl(unsigned int controllerIndex)
			: m_controllerIndex(controllerIndex)
		{
			ZeroMemory(&m_previousState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
		}

		void Poll()
		{
			CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
			XInputGetState(m_controllerIndex, &m_currentState);

			const WORD buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
			m_buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
			m_buttonsReleasedThisFrame = buttonChanges & ~m_currentState.Gamepad.wButtons;
		}

		bool IsDownThisFrame(unsigned int button) const
		{
			return (m_buttonsPressedThisFrame & button) != 0;
		}
		bool IsUpThisFrame(unsigned int button) const
		{
			return (m_buttonsReleasedThisFrame & button) != 0;
		}
		bool IsPressed(unsigned int button) const
		{
			return (m_currentState.Gamepad.wButtons & button) != 0;
		}

	private:
		XINPUT_STATE m_previousState{};
		XINPUT_STATE m_currentState{};
		WORD m_buttonsPressedThisFrame{};
		WORD m_buttonsReleasedThisFrame{};
		unsigned int m_controllerIndex;
	};
}

#else
namespace dae
{
	class Controller::ControllerImpl
	{
	public:
		explicit ControllerImpl(unsigned int) {}
		void Poll() {}
		bool IsDownThisFrame(unsigned int) const { return false; }
		bool IsUpThisFrame(unsigned int) const { return false; }
		bool IsPressed(unsigned int) const { return false; }
	};
}
#endif

namespace dae
{
	Controller::Controller(unsigned int controllerIndex)
		: m_pImpl(std::make_unique<ControllerImpl>(controllerIndex))
	{
	}

	Controller::~Controller() = default;

	void Controller::Poll()
	{
		m_pImpl->Poll();
	}

	bool Controller::IsDownThisFrame(ControllerButton button) const
	{
		return m_pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
	}

	bool Controller::IsUpThisFrame(ControllerButton button) const
	{
		return m_pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
	}

	bool Controller::IsPressed(ControllerButton button) const
	{
		return m_pImpl->IsPressed(static_cast<unsigned int>(button));
	}
}