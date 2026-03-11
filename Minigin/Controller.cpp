#include "Controller.h"

#ifndef __EMSCRIPTEN__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib") //Better oversight to keep it here than in the CMake, can change later if needed ofc

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
#include <SDL3/SDL.h>

namespace dae
{
    class Controller::ControllerImpl
    {
    public:
        explicit ControllerImpl(unsigned int controllerIndex)
            : m_controllerIndex(controllerIndex)
        {
            TryOpen();
        }

        ~ControllerImpl()
        {
            if (m_gamepad)
                SDL_CloseGamepad(m_gamepad);
        }

        void Poll()
        {
            if (!m_gamepad)
                TryOpen();
            if (!m_gamepad)
                return;

            m_previousButtons = m_currentButtons;
            m_currentButtons = 0;

            for (const auto& [xinputMask, sdlButton] : s_buttonMap)
            {
                if (SDL_GetGamepadButton(m_gamepad, sdlButton))
                    m_currentButtons |= xinputMask;
            }

            const unsigned int changed = m_currentButtons ^ m_previousButtons;
            m_buttonsPressedThisFrame = changed & m_currentButtons;
            m_buttonsReleasedThisFrame = changed & ~m_currentButtons;
        }

        bool IsDownThisFrame(unsigned int button) const { return (m_buttonsPressedThisFrame & button) != 0; }
        bool IsUpThisFrame(unsigned int button) const { return (m_buttonsReleasedThisFrame & button) != 0; }
        bool IsPressed(unsigned int button) const { return (m_currentButtons & button) != 0; }

    private:
        void TryOpen()
        {
            int count{};
            SDL_JoystickID* ids = SDL_GetGamepads(&count);
            if (ids && m_controllerIndex < static_cast<unsigned int>(count))
                m_gamepad = SDL_OpenGamepad(ids[m_controllerIndex]);
            SDL_free(ids);
        }

        struct ButtonMapping { unsigned int xinputMask; SDL_GamepadButton sdlButton; };
        static constexpr ButtonMapping s_buttonMap[] =
        {
            { 0x0001, SDL_GAMEPAD_BUTTON_DPAD_UP},
            { 0x0002, SDL_GAMEPAD_BUTTON_DPAD_DOWN},
            { 0x0004, SDL_GAMEPAD_BUTTON_DPAD_LEFT},
            { 0x0008, SDL_GAMEPAD_BUTTON_DPAD_RIGHT},
            { 0x0010, SDL_GAMEPAD_BUTTON_START},
            { 0x0020, SDL_GAMEPAD_BUTTON_BACK},
            { 0x0040, SDL_GAMEPAD_BUTTON_LEFT_STICK},
            { 0x0080, SDL_GAMEPAD_BUTTON_RIGHT_STICK},
            { 0x0100, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER},
            { 0x0200, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER},
            { 0x1000, SDL_GAMEPAD_BUTTON_SOUTH}, // A
            { 0x2000, SDL_GAMEPAD_BUTTON_EAST}, // B
            { 0x4000, SDL_GAMEPAD_BUTTON_WEST}, // X
            { 0x8000, SDL_GAMEPAD_BUTTON_NORTH}, // Y
        };

        SDL_Gamepad* m_gamepad{ nullptr };
        unsigned int  m_controllerIndex;
        unsigned int  m_currentButtons{};
        unsigned int  m_previousButtons{};
        unsigned int  m_buttonsPressedThisFrame{};
        unsigned int  m_buttonsReleasedThisFrame{};
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