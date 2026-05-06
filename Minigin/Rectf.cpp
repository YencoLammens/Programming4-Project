#include "Rectf.h"

dae::Rectf::Rectf()
	:Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

dae::Rectf::Rectf(float x, float y, float width, float height)
	: x{ x }, y{ y }, width{ width }, height{ height }
{
}