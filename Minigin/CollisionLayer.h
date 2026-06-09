#pragma once

namespace dae
{
    enum class CollisionLayer
    {
        None = 0,
        Player,
        Enemy,
        Bubble,
        Platform,
        Wall,
        BubbledEnemy,
        Food
    };
}