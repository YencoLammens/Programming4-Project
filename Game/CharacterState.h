#pragma once
#include <memory>

namespace dae
{
    class GameObject;

    class CharacterState
    {
    public:
        virtual ~CharacterState() = default;
        CharacterState(const CharacterState&) = delete;
        CharacterState& operator=(const CharacterState&) = delete;
        CharacterState(CharacterState&&) = delete;
        CharacterState& operator=(CharacterState&&) = delete;

        virtual void OnEnter(GameObject* owner) = 0;
        virtual std::unique_ptr<CharacterState> HandleInput(GameObject* owner) = 0;
        virtual void Update(GameObject* owner, float deltaTime) = 0;
        virtual void OnExit(GameObject* owner) = 0;

    protected:
        CharacterState() = default;
    };
}