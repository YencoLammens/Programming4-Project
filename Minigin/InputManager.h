#pragma once
#include "Singleton.h"
#include "Command.h"
#include "Controller.h"
#include <memory>
#include <vector>
#include <SDL3/SDL.h>

namespace dae
{
	enum class KeyState
	{
		Down,
		Up,
		Pressed
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput(float deltaTime);

		void BindCommand(SDL_Scancode key, KeyState state, std::unique_ptr<Command> command);
		void UnbindCommand(SDL_Scancode key, KeyState state);

		void BindCommand(unsigned int controllerIdx, Controller::ControllerButton button, KeyState state, std::unique_ptr<Command> command);
		void UnbindCommand(unsigned int controllerIdx, Controller::ControllerButton button, KeyState state);

	private:
		Controller* GetOrCreateController(unsigned int index);

		struct KeyboardBinding
		{
			SDL_Scancode key;
			KeyState state;
			std::unique_ptr<Command> command;
		};

		struct ControllerBinding
		{
			unsigned int controllerIdx;
			Controller::ControllerButton button;
			KeyState state;
			std::unique_ptr<Command> command;
		};

		std::vector<std::unique_ptr<Controller>> m_controllers;
		std::vector<KeyboardBinding> m_keyboardBindings;
		std::vector<ControllerBinding> m_controllerBindings;
		std::vector<bool> m_previousKeyboardState;
	};
}