#pragma once

namespace dae
{
    enum class CollisionLayer
    {
        None = 0,
        Player,
        Enemy,
        Bubble,
        Boulder,
        Platform,
        Wall,
        BubbledEnemy,
        Food
    };
}