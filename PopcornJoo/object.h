#pragma once
#include "vector2d.h"

namespace phy {
	class object {
	private:
		
	public:
		double mesh = 1;
		double gravity = 9.8;
		vector2d transform;
		vector2d velocity;
		
		virtual void update(long long tick);
	};
}