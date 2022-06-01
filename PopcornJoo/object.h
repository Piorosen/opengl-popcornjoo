#pragma once
#include <functional>
#include "rect.h"
#include "vector2d.h"
#include "collisioninfo.h"
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
		vector2d prevTrasform;
		vector2d transform;

		bool hidden = false;

	public:
		void setHidden(bool hidden) {
			this->hidden = hidden;
		}

		bool getHidden() const {
			return hidden;
		}

		// circle mode
		void setType(double radius) {
			this->rect = grc::rect(-radius, -radius, 
								    radius,  radius);
			type = collisiontype::circle;
		}
		// circle mode
		void setType(grc::rect rect) {
			this->rect = rect;
			type = collisiontype::rectangle;
		}

		collisiontype getType(double& radius, grc::rect& rect) {
			radius = -this->rect.location.x;
			rect = this->rect;
			return type;
		}

		void setTransform(vector2d data) {
			prevTrasform = transform;
			transform = data;
			if (transformchanged) {
				transformchanged(data);
			}
		}

		vector2d getTransform() const {
			return transform;
		}

		vector2d getOldTransform() const {
			return prevTrasform;
		}
		
		std::function<void(vector2d)> transformchanged;
		std::function<void(std::weak_ptr<object>, std::weak_ptr<object>, phy::collisioninfo, long long)> collisionevent;

		double mesh = 1;
		double gravity = 0;
		vector2d velocity;

		virtual void update(long long tick) {
			if (!hidden) {
				double downSpeed = gravity * mesh * (tick / 1000.0);
				velocity.y -= downSpeed;
				transform.x += velocity.x * (tick / 1000.0);
				transform.y += velocity.y * (tick / 1000.0);
				if (transformchanged) {
					transformchanged(transform);
				}
			}
		}
	};
}