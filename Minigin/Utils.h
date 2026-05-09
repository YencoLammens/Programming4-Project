#pragma once
#include "Rectf.h"
namespace dae
{
	//ODR violation if no inline
	inline bool IsOverlapping(const dae::Rectf& r1, const dae::Rectf& r2)
	{
		// If one rectangle is on left side of the other
		if ((r1.x + r1.width) < r2.x || (r2.x + r2.width) < r1.x)
		{
			return false;
		}

		// If one rectangle is under the other
		if (r1.y > (r2.y + r2.height) || r2.y > (r1.y + r1.height))
		{
			return false;
		}

		return true;
	};
}