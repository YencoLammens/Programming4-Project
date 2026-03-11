#pragma once
#include "GameObject.h"
#include <memory>
#include <glm/glm.hpp>

namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		Command(const Command&) = delete;
		Command& operator=(const Command&) = delete;
		Command(Command&&) = delete;
		Command& operator=(Command&&) = delete;

		virtual void Execute(float deltaTime) = 0;

	protected:
		Command() = default;
	};

	class GameObjectCommand : public Command
	{
	public:
		explicit GameObjectCommand(GameObject* gameObject);
		virtual ~GameObjectCommand() = default;
		GameObjectCommand(const GameObjectCommand&) = delete;
		GameObjectCommand& operator=(const GameObjectCommand&) = delete;
		GameObjectCommand(GameObjectCommand&&) = delete;
		GameObjectCommand& operator=(GameObjectCommand&&) = delete;

	protected:
		GameObject* GetGameObject() const { return m_gameObject; }

	private:
		GameObject* m_gameObject;
	};
}