#pragma once
namespace dae
{
    struct Rectf
    {
        Rectf();
        Rectf(float x, float y, float width, float height);
        float x, y;
        float width, height;
    };
}