#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <spdlog/spdlog.h>

#include "circle.h"
#include "rectangle.h"
#include "object.h"
#include "collision.h"


namespace phy {
	class physicsEngine final {
	private:
		std::vector<std::shared_ptr<object>> target;
		std::vector<std::shared_ptr<object>> wall;
		//std::vector<std::shared_ptr<object>> object;

	public:
		static std::unique_ptr<phy::physicsEngine> shared;

		std::function<void(std::weak_ptr<phy::object>, std::weak_ptr<phy::object>)> collisionObject;
		
		void AddTarget(std::shared_ptr<phy::object> data) {
			target.push_back(data);
		}

		void AddWall(std::shared_ptr<phy::object> data) {
			wall.push_back(data);
		}

		/*void AddObject(std::shared_ptr<phy::object> data) {
			object.push_back(data);
		}*/

		void ClearObject() {
			target.clear();
			wall.clear();
			//object.clear();
		}

		bool checkCollision(std::weak_ptr<phy::object> left, std::weak_ptr<phy::object> right) {
			auto ls = left.lock();
			auto rs = right.lock();
			if (!(ls && rs)) {
				return false;
			}
			double leftRadius = 0;
			grc::rect leftRect;
			double rightRadius = 0;
			grc::rect rightRect;
			
			auto leftType = ls->getType(leftRadius, leftRect);
			auto rightType = rs->getType(leftRadius, rightRect);

			if (leftType == phy::collisiontype::circle &&
				rightType == phy::collisiontype::circle) {
				auto length = (ls->transform - rs->transform).magnitude();
				if (length < leftRadius + rightRadius) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				//if (leftRect)
				leftRect.location.x += ls->transform.x;
				leftRect.location.y += ls->transform.y;

				rightRect.location.x += rs->transform.x;
				rightRect.location.y += rs->transform.y;

				if (leftRect.location.x + leftRect.size.width >= rightRect.location.x &&
					leftRect.location.x <= rightRect.location.x + rightRect.size.width &&
					leftRect.location.y + leftRect.size.height >= rightRect.location.y &&
					leftRect.location.y <= rightRect.location.y + rightRect.size.height) {
					return true;
				}
				else {
					return false;
				}
				/*if (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2)
				{
					return true;
				}*/
			}

			spdlog::info("固备泅等 面倒 贸府");
			return false;

		}

		void update(long long tick) {
			for (auto& t : target) {
				t->update(tick);
			}

			for (auto& w : wall) {
				w->update(tick);
			}

			for (auto& t : target) {
				for (auto& w : wall) {
					bool data = checkCollision(t, w);
					if (data) {
						if (t->collisionevent) {
							t->collisionevent(t, w);
						}
						if (w->collisionevent) {
							w->collisionevent(w, t);
						}
					}
				}
			}
		}

	protected:

	};
}
