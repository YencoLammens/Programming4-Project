#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"
#include <algorithm>

namespace dae
{
	bool InputManager::ProcessInput(float deltaTime)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_EVENT_QUIT)
				return false;

			ImGui_ImplSDL3_ProcessEvent(&e);
		}

		const bool* currentKeys = SDL_GetKeyboardState(nullptr);

		if (m_previousKeyboardState.empty())
			m_previousKeyboardState.assign(currentKeys, currentKeys + SDL_SCANCODE_COUNT);

		for (auto& binding : m_keyboardBindings)
		{
			const bool wasDown = m_previousKeyboardState[binding.key];
			const bool isDown = currentKeys[binding.key];

			bool fire = false;
			switch (binding.state)
			{
			case KeyState::Down: 
				fire = (isDown && !wasDown); 
				break;
			case KeyState::Up: 
				fire = (!isDown && wasDown); 
				break;
			case KeyState::Pressed: 
				fire = isDown; 
				break;
			}

			if (fire)
				binding.command->Execute(deltaTime);
		}

		std::copy(currentKeys, currentKeys + SDL_SCANCODE_COUNT, m_previousKeyboardState.begin());

		for (auto& controller : m_controllers)
			controller->Poll();

		for (auto& binding : m_controllerBindings)
		{
			if (binding.controllerIdx >= m_controllers.size())
				continue;

			auto* ctrl = m_controllers[binding.controllerIdx].get();

			bool fire = false;
			switch (binding.state)
			{
			case KeyState::Down:
				fire = ctrl->IsDownThisFrame(binding.button); 
				break;
			case KeyState::Up:
				fire = ctrl->IsUpThisFrame(binding.button); 
				break;
			case KeyState::Pressed: 
				fire = ctrl->IsPressed(binding.button); 
				break;
			}

			if (fire)
				binding.command->Execute(deltaTime);
		}

		return true;
	}

	void InputManager::BindCommand(SDL_Scancode key, KeyState state, std::unique_ptr<Command> command)
	{
		if (m_previousKeyboardState.empty())
		{
			const bool* keys = SDL_GetKeyboardState(nullptr);
			m_previousKeyboardState.assign(keys, keys + SDL_SCANCODE_COUNT);
		}
		m_keyboardBindings.push_back({ key, state, std::move(command) });
	}

	void InputManager::UnbindCommand(SDL_Scancode key, KeyState state)
	{
		auto it = std::find_if(m_keyboardBindings.begin(), m_keyboardBindings.end(),
			[key, state](const KeyboardBinding& b) { return b.key == key && b.state == state; });

		if (it != m_keyboardBindings.end())
			m_keyboardBindings.erase(it);
	}

	Controller* InputManager::GetOrCreateController(unsigned int index)
	{
		while (m_controllers.size() <= index)
			m_controllers.emplace_back(std::make_unique<Controller>(static_cast<unsigned int>(m_controllers.size())));
		return m_controllers[index].get();
	}

	void InputManager::BindCommand(unsigned int controllerIdx, Controller::ControllerButton button, KeyState state, std::unique_ptr<Command> command)
	{
		GetOrCreateController(controllerIdx);
		m_controllerBindings.push_back({ controllerIdx, button, state, std::move(command) });
	}

	void InputManager::UnbindCommand(unsigned int controllerIdx, Controller::ControllerButton button, KeyState state)
	{
		auto it = std::find_if(m_controllerBindings.begin(), m_controllerBindings.end(),
			[controllerIdx, button, state](const ControllerBinding& b)
			{
				return b.controllerIdx == controllerIdx
					&& b.button == button
					&& b.state == state;
			});

		if (it != m_controllerBindings.end())
			m_controllerBindings.erase(it);
	}
}