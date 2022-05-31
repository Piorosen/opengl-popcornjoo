#pragma once
#include <functional>
#include "rect.h"
#include "vector2d.h"

namespace phy {
	enum class collisiontype {
		circle,
		rectangle
	};

	class object {
	private:
		collisiontype type = collisiontype::circle;
		// type : rectangle needs
		grc::rect rect = grc::rect(0,0,100, 100);
		
	public:
		// circle mode
		void setType(double radius) {
			this->rect = grc::rect(-radius / 2.0, -radius / 2.0, 
								    radius / 2.0,  radius / 2.0);
			type = collisiontype::circle;
		}
		// circle mode
		void setType(grc::rect rect) {
			this->rect = rect;
			type = collisiontype::rectangle;
		}

		collisiontype getType(double& radius, grc::rect& rect) {
			radius = this->rect.size.width + this->rect.location.x;
			rect = this->rect;
			return type;
		}

		double mesh = 1;
		double gravity = 0;
		vector2d transform;
		vector2d velocity;
		
		std::function<void(vector2d)> transformchanged;
		std::function<void(std::weak_ptr<object>, std::weak_ptr<object>)> collisionevent;

		virtual void update(long long tick) {
			double downSpeed = gravity * (1.0 / mesh) * (tick / 1000.0);
			velocity.y -= downSpeed;
			transform.x += velocity.x * (tick / 1000.0);
			transform.y += velocity.y * (tick / 1000.0);
			if (transformchanged) {
				transformchanged(transform);
			}
		}
	};
}